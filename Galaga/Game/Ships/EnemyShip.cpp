#include "EnemyShip.h"
#include "Physics/Physics.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/ColliderComponent.h"

EnemyShip::EnemyShip(const Vector2D& pos, const Vector2D& _bulletOffset)
	: Ship(pos), bulletOffset(_bulletOffset)
{
	transform->SetRotation(180.f);
	SDL_Texture* texture = AssetManager::LoadTexture("enemy1.png");
	spriteComponent->SetTexture(texture);
	// Setup ColliderComponent.
	Vector2D size = spriteComponent->GetSize();
	colliderComponent->SetLayer(CollisionLayer::AI);
	colliderComponent->SetBounds(SDL_Rect{ 0, 0, (int)size.x, (int)size.y });
}

void EnemyShip::Update(float deltaTime)
{
	Ship::Update(deltaTime);
}

void EnemyShip::Fire()
{

}
