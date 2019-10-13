#include "Ship.h"
#include "Physics/Physics.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/ColliderComponent.h"

Ship::Ship(const Vector2D& pos)
{
	transform->SetPosition(pos);
	spriteComponent = AddComponent<SpriteComponent>();
	// Setup ColliderComponent.	
	colliderComponent = AddComponent<ColliderComponent>();
}
