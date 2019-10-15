#ifndef QUADTREE_H
#define QUADTREE_H
// STD
#include <vector>
#include <memory>
#include <SDL_rect.h>

class ColliderComponent;
struct SDL_Rect;

class QuadTree
{
public:
	QuadTree();
	QuadTree(int maxObjects, int maxLevels, int level, const SDL_Rect& bounds, QuadTree* parent);

	// Inserts collider into our quadtree.
	void Insert(ColliderComponent* collider);

	// Removes collider from our quadtree when we no longer need it to collide.
	void Remove(ColliderComponent* collider);

	// Removes all objects from tree.
	void Clear();

	// Returns vector of colliders that intersect with the search area.
	std::vector<ColliderComponent*> Search(const SDL_Rect& area);

	// Returns the bounds of this node.
	inline const SDL_Rect& GetBounds() const { return bounds; }

	// DEBUG.
	void DrawDebug();

private:
	void Search(const SDL_Rect& area, std::vector<ColliderComponent*>& overlappingColliders);

	int GetChildIndexForCollider(const SDL_Rect& colliderBounds) const;

	// Creates the child nodes.
	void Split();

	// We’ll use these as indices in our array of children.
	static const int thisTree = -1;
	static const int childNE = 0;
	static const int childNW = 1;
	static const int childSW = 2;
	static const int childSE = 3;

	int maxObjects;
	int maxLevels;

	// nulptr if this is the base node.
	QuadTree* parent;
	std::shared_ptr<QuadTree> children[4];

	// Stores colliders in this node.
	std::vector<ColliderComponent*> colliders;

	// How deep the current node is from the base node. 
	// The first node starts at 0 and then its child node 	
	// is at level 1 and so on.
	int level;

	// The bounds of this node.
	SDL_Rect bounds;
};

#endif // !QUADTREE_H
