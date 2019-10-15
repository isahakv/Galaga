#include "Bullet.h"
#include "Core/TypeDefs.h"
#include "Physics/Physics.h"
#include "Core/AssetManagement/AssetManager.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/ColliderComponent.h"
#include "Core/Components/VelocityComponent.h"
#include "../Game/Ships/Ship.h"

Bullet::Bullet(const Vector2D& pos, float angle, float speed)
{
	// Setup SpriteComponent.
	spriteComponent = AddComponent<SpriteComponent>();
	SDL_Texture* texture = AssetManager::LoadTexture("galaga_bullet.png");
	spriteComponent->SetTexture(texture);
	// Setup TransformComponent.
	transform->SetPosition(pos - spriteComponent->GetOrigin(Space::Relative));
	transform->SetRotation(angle);
	// Setup ColliderComponent.
	Vector2D size = spriteComponent->GetSize();
	colliderComponent = AddComponent<ColliderComponent>();
	colliderComponent->SetBounds(SDL_Rect{ 0, 0, (int)size.x, (int)size.y });
	colliderComponent->SetLayer(CollisionLayer::Player);
	std::function<void(ColliderComponent*)> func = std::bind(&Bullet::OnCollisionEnter, this, std::placeholders::_1);
	colliderComponent->BindCollisionEnter(func);
	;
	// Setup VelocityComponent.
	velocityComponent = AddComponent<VelocityComponent>();
	velocityComponent->SetSpeed(speed);
}

void Bullet::OnCollisionEnter(ColliderComponent* other)
{
	// std::cout << "kpav" << std::endl;
	if (Ship* ship = dynamic_cast<Ship*>(other->GetOwner()))
		ship->Destroy();

	Destroy();
}
