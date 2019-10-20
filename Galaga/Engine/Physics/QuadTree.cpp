#include "QuadTree.h"
#include "Core/Components/ColliderComponent.h"
#include "Core/GameObjects/GameObject.h"
#include "Render/Renderer.h"

QuadTree::QuadTree() : QuadTree(5, 5, 0, SDL_Rect{ 0, 0, 800, 600 }, nullptr) {}

QuadTree::QuadTree(int maxObjects, int maxLevels, int level, const SDL_Rect& bounds, QuadTree* parent)
	: maxObjects(maxObjects), maxLevels(maxLevels), level(level), bounds(bounds), parent(parent) {}

void QuadTree::Insert(ColliderComponent* collider)
{
	// If there are children, then try to insert in them.
	if (children[0] != nullptr)
	{
		int index = GetChildIndexForCollider(collider->GetBounds());
		if (index != thisTree)
		{
			children[index]->Insert(collider);
			return;
		}
	}
	// Else push in this node.
	colliders.push_back(collider);
	// If we reach the "maxObjects" limits,
	// And not in "maxLevels" already,
	// And havn't children. 
	if (colliders.size() > maxObjects && level < maxLevels && children[0] == nullptr)
	{
		Split();

		auto itr = colliders.begin();
		while (itr != colliders.end())
		{
			auto col = *itr;
			int index = GetChildIndexForCollider(col->GetBounds());
			if (index != thisTree)
			{
				children[index]->Insert(col);
				itr = colliders.erase(itr);
			}
			else
				++itr;
		}
	}
}

void QuadTree::Remove(ColliderComponent* collider)
{
	int index = GetChildIndexForCollider(collider->GetBounds());
	if (index == thisTree || children[0] == nullptr)
	{
		auto itr = colliders.begin();
		while (itr != colliders.end())
		{
			if ((*itr)->GetOwner()->GetInstanceID() == collider->GetOwner()->GetInstanceID())
			{
				colliders.erase(itr);
				return;
			}
			++itr;
		}
	}
	else
		return children[index]->Remove(collider);
}

void QuadTree::Clear()
{
	colliders.clear();
	for (auto& child : children)
	{
		if (child != nullptr)
		{
			child->Clear();
			child = nullptr;
		}
	}
}

void QuadTree::DrawDebug()
{
	// If there are children.
	if (children[0] != nullptr)
	{
		for (auto child : children)
			child->DrawDebug();
	}
	else
		Renderer::Get()->DrawDebugRect(&bounds);
}

std::vector<ColliderComponent*> QuadTree::Search(const SDL_Rect& area)
{
	std::vector<ColliderComponent*> possibleOverlaps;
	Search(area, possibleOverlaps);

	std::vector<ColliderComponent*> result;
	for (auto collider : possibleOverlaps)
	{
		if (SDL_HasIntersection(&area, &collider->GetBounds()))
			result.push_back(collider);
	}

	return result;
}

void QuadTree::Search(const SDL_Rect& area, std::vector<ColliderComponent*>& overlappingColliders)
{
	overlappingColliders.insert(overlappingColliders.end(), colliders.begin(), colliders.end());

	// If there are children, then check for them.
	if (children[0] != nullptr)
	{
		int index = GetChildIndexForCollider(area);
		if (index == thisTree)
		{
			for (auto& child : children)
			{
				if (SDL_HasIntersection(&area, &child->GetBounds()))
					child->Search(area, overlappingColliders);
			}
		}
		else
			children[index]->Search(area, overlappingColliders);
	}
}

int QuadTree::GetChildIndexForCollider(const SDL_Rect& colliderBounds) const
{
	int index = -1;

	float verticalSplitter = bounds.x + bounds.w * 0.5f;
	float horizontalSplitter = bounds.y + bounds.h * 0.5f;

	bool east = colliderBounds.x > verticalSplitter;
	bool west = colliderBounds.x + colliderBounds.w < verticalSplitter;
	bool north = colliderBounds.y + colliderBounds.h < horizontalSplitter;
	bool south = colliderBounds.y > horizontalSplitter;

	if (east)
	{
		if (north)
			index = childNE;
		else if (south)
			index = childSE;
	}
	else if (west)
	{
		if (north)
			index = childNW;
		else if (south)
			index = childSW;
	}

	return index;
}

void QuadTree::Split()
{
	const int childWidth = bounds.w / 2;
	const int childHeight = bounds.h / 2;

	children[childNE] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1,
		SDL_Rect{ bounds.x + childWidth, bounds.y, childWidth, childHeight }, this);
	children[childNW] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1,
		SDL_Rect{ bounds.x, bounds.y, childWidth, childHeight }, this);
	children[childSE] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1,
		SDL_Rect{ bounds.x + childWidth, bounds.y + childHeight, childWidth, childHeight }, this);
	children[childSW] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1,
		SDL_Rect{ bounds.x, bounds.y + childHeight, childWidth, childHeight }, this);
}
