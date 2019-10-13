#ifndef PHYSICS_H
#define PHYSICS_H
#include <vector>
#include <map>

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

	void RegisterCollider(ColliderComponent* collider);
	void UnregisterCollider(ColliderComponent* collider);

private:
	static Physics* instance;

	// The collision system stores all collidables along with their layer.
	std::map<CollisionLayer, std::vector<ColliderComponent*>> colliders;
};

#endif // !PHYSICS_H
