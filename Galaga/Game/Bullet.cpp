#include "Bullet.h"
#include "Core/TypeDefs.h"
#include "Physics/Physics.h"
#include "Core/AssetManagement/AssetManager.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/ColliderComponent.h"
#include "Core/Components/VelocityComponent.h"
#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "GalagaScene.h"
#include "Core/GameObjects/ParticleObject.h"
#include "../Game/Ships/Ship.h"

Bullet::Bullet(const Vector2D& pos, float angle, float speed, CollisionLayer collisionLayer, float lifeSpan)
	: lifeSpan(lifeSpan)
{
	// Setup SpriteComponent.
	spriteComponent = AddComponent<SpriteComponent>();
	SDL_Texture* texture = AssetManager::Get()->LoadTexture("Game/Assets/Images/galaga_bullet.png");
	spriteComponent->SetTexture(texture);
	spriteComponent->SetSortOrder(5);
	// Setup TransformComponent.
	transform->SetPosition(pos - spriteComponent->GetOrigin(Space::Relative));
	transform->SetRotation(angle);
	// Setup ColliderComponent.
	Vector2D size = spriteComponent->GetScaledSize();
	colliderComponent = AddComponent<ColliderComponent>();
	colliderComponent->SetBounds(SDL_Rect{ 0, 0, (int)size.x, (int)size.y });
	colliderComponent->SetLayer(collisionLayer);
	std::function<void(ColliderComponent*)> func = std::bind(&Bullet::OnCollisionEnter, this, std::placeholders::_1);
	colliderComponent->BindCollisionEnter(func);
	
	// Setup VelocityComponent.
	velocityComponent = AddComponent<VelocityComponent>();
	velocityComponent->SetVelocity(Vector2D::Up * -speed);
}

void Bullet::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	lifeSpanCounter += deltaTime;
	if (lifeSpanCounter >= lifeSpan)
		Destroy();
}

void Bullet::OnCollisionEnter(ColliderComponent* other)
{
	// TODO: Add "OnHitted" function to "GameObject".
	if (Ship* ship = dynamic_cast<Ship*>(other->GetOwner()))
		static_cast<GalagaScene*>(SceneManager::GetActiveScene())->OnShipHitted(ship);
	else if (Bullet* bullet = dynamic_cast<Bullet*>(other->GetOwner()))
		bullet->OnHitted();
	Destroy();
}

void Bullet::OnHitted()
{
	Vector2D& pos = transform->GetPosition();
	std::shared_ptr<ParticleObject> particle = std::make_shared<ParticleObject>(pos,
		"Game/Assets/Images/explosion.png", 32, 32, 4, 1, 0.1f, false);
	SceneManager::GetActiveScene()->AddToScene(particle);
	Destroy();
}
