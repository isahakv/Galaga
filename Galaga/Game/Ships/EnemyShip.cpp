#include "EnemyShip.h"
#include "Physics/Physics.h"
#include "Core/Math/Math.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/AnimatedSpriteComponent.h"
#include "Core/Components/ColliderComponent.h"
#include "Core/Components/VelocityComponent.h"
#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "Bullet.h"

EnemyShip::EnemyShip(const Vector2D& pos, const Vector2D& _bulletOffset, float _moveSpeed, float _minFireRate, float _maxFireRate)
	: Ship(pos, _bulletOffset), bulletOffset(_bulletOffset), minfireRate(_minFireRate), maxfireRate(_maxFireRate), fireRateCounter(0)
{
	transform->SetRotation(180.f);
	// Setup SpriteComponent.
	SDL_Texture* texture = AssetManager::Get()->LoadTexture("Game/Assets/Images/enemies.png");
	spriteComponent->SetTexture(texture);
	SpriteAnimation animation(Vector2D(0.f, Math::RandomBool() * 24.f), Vector2D(30.f, 24.f), 2, 1, 1.f);
	int idx = spriteComponent->AddAnimation(animation);
	spriteComponent->Start(idx);
	// Setup ColliderComponent.
	Vector2D size = spriteComponent->GetScaledSize();
	colliderComponent->SetLayer(CollisionLayer::AI);
	colliderComponent->SetBounds(SDL_Rect{ 0, 0, (int)size.x, (int)size.y });
	// Setup VelocityComponent.
	velocityComponent->SetVelocity(Vector2D::Right * _moveSpeed);
	// Get Random Fire Rate.
	fireRate = Math::Random(minfireRate, maxfireRate);
}

void EnemyShip::Update(float deltaTime)
{
	Ship::Update(deltaTime);
	fireRateCounter += deltaTime;
	if (fireRateCounter >= fireRate)
	{
		Fire();
		fireRateCounter = 0.f;
		fireRate = Math::Random(minfireRate, maxfireRate);
	}
}

void EnemyShip::Fire()
{
	Scene* scene = SceneManager::GetActiveScene();
	scene->AddToScene(std::make_shared<Bullet>(GetBulletSpawnPos(), 180.f, 200.f, CollisionLayer::AI));
}
