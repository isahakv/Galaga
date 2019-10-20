#include "Ship.h"
#include "Physics/Physics.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/AnimatedSpriteComponent.h"
#include "Core/Components/ColliderComponent.h"
#include "Core/Components/VelocityComponent.h"
#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "Core/GameObjects/ParticleObject.h"
#include "Bullet.h"

Ship::Ship(const Vector2D& pos, const Vector2D& _bulletOffset)
	: bulletOffset(_bulletOffset)
{
	transform->SetPosition(pos);
	// Setup SpriteComponent.
	spriteComponent = AddComponent<AnimatedSpriteComponent>();
	// Setup ColliderComponent.
	colliderComponent = AddComponent<ColliderComponent>();
	// Setup VelocityComponent.
	velocityComponent = AddComponent<VelocityComponent>();
}

Vector2D Ship::GetBulletSpawnPos() const
{
	Vector2D shipOrigin = spriteComponent->GetOrigin(Space::World);
	return Vector2D(shipOrigin + bulletOffset);
}

void Ship::OnHitted()
{
	Vector2D pos = GetComponent<SpriteComponent>()->GetOrigin(Space::World);
	std::shared_ptr<ParticleObject> particle = std::make_shared<ParticleObject>(pos,
		"Game/Assets/Images/explosion.png", 32, 32, 4, 1, 0.1f, false);
	SceneManager::GetActiveScene()->AddToScene(particle);
	Destroy();
}
