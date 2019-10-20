#include "Physics.h"
#include "Core/Components/ColliderComponent.h"
#include "Core/GameObjects/GameObject.h"

Physics* Physics::instance = nullptr;

Physics* Physics::Get()
{
	if (instance == nullptr)
		instance = new Physics();
	return instance;
}

void Physics::Update()
{
	quadTree.Clear();
	for (auto maps = colliders.begin(); maps != colliders.end(); maps++)
	{
		for (auto collider : maps->second)
			quadTree.Insert(collider);
	}
	// quadTree.DrawDebug();
	Resolve();
}

void Physics::Resolve()
{
	for (auto maps = colliders.begin(); maps != colliders.end(); maps++)
	{
		for (auto collider : maps->second)
		{
			if (collider->GetOwner()->IsPendingToDestroy())
				continue;

			auto others = quadTree.Search(collider->GetBounds());
			for (auto other : others)
			{
				if (other->GetOwner()->IsPendingToDestroy())
					continue;

				// Make sure we do not resolve collisions between the same object.
				if (collider->GetOwner()->GetInstanceID() ==
					other->GetOwner()->GetInstanceID())
					continue;

				// TODO: Make this to use BitMask.
				bool layersCollide = collider->GetLayer() != other->GetLayer();
				if (!layersCollide)
					continue;

				// Checking collision one more time,
				// because as we resolve collisions and move objects around
				// we may no longer be colliding with some objects in the vector.
				if (SDL_HasIntersection(&collider->GetBounds(), &other->GetBounds()))
				{
					collider->OnCollisionEnter(other);
				}
			}
		}
	}
}

void Physics::RegisterCollider(ColliderComponent* collider)
{
	CollisionLayer layer = collider->GetLayer();
	auto itr = colliders.find(layer);
	if (itr != colliders.end())
		colliders[layer].push_back(collider);
	else
	{
		std::vector<ColliderComponent*> col;
		col.push_back(collider);
		colliders.insert(std::make_pair(layer, col));
	}
}

void Physics::UnregisterCollider(ColliderComponent* collider)
{
	CollisionLayer layer = collider->GetLayer();
	auto itr = colliders.find(layer);
	if (itr != colliders.end())
	{
		std::vector<ColliderComponent*>& cols = itr->second;
		auto it = std::find(cols.begin(), cols.end(), collider);
		if (it != cols.end())
			cols.erase(it);
	}
}
