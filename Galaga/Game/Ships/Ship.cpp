#include "Ship.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/TransformComponent.h"

Ship::Ship(const Vector2D& pos)
{
	transform->SetPosition(pos);
	spriteComponent = new SpriteComponent(this, NULL, 0);
	components.push_back(spriteComponent);
}
