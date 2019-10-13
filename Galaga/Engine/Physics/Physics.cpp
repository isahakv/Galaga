#include "Physics.h"
#include "Core/Components/ColliderComponent.h"

Physics* Physics::instance = nullptr;

Physics* Physics::Get()
{
	if (instance == nullptr)
		instance = new Physics();
	return instance;
}

void Physics::Update()
{

}

void Physics::RegisterCollider(ColliderComponent* collider)
{

}

void Physics::UnregisterCollider(ColliderComponent* collider)
{

}
