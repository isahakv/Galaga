#ifndef PHYSICS_H
#define PHYSICS_H
#include <vector>
#include <map>
#include "QuadTree.h"

class ColliderComponent;

enum class CollisionLayer
{
	None,
	Player,
	AI
};

class Physics
{
public:
	static Physics* Get();
	void Update();
	void Resolve();

	void RegisterCollider(ColliderComponent* collider);
	void UnregisterCollider(ColliderComponent* collider);

private:
	static Physics* instance;

	// This is used to store collision layer data i.e. which layers can collide.
	// std::map<CollisionLayer, Bitmask> collisionLayers;

	// The collision system stores all collidables along with their layer.
	std::map<CollisionLayer, std::vector<ColliderComponent*>> colliders;

	// The quadtree stores the colliders in a spatial aware structure.
	QuadTree quadTree;
};

#endif // !PHYSICS_H
