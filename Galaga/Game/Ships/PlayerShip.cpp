#include "PlayerShip.h"
#include "../Game/GalagaApplication.h"
#include "Physics/Physics.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/AnimatedSpriteComponent.h"
#include "Core/Components/ColliderComponent.h"
#include "Core/AssetManagement/AssetManager.h"
#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "Core/Input/Input.h"
#include "Bullet.h"
#include <iostream>

PlayerShip::PlayerShip(const Vector2D& pos, const Vector2D& _bulletOffset, float _moveSpeed, float _fireRate)
	: Ship(pos, _bulletOffset), moveSpeed(_moveSpeed), fireRate(_fireRate)
{
	SDL_Texture* texture = AssetManager::Get()->LoadTexture("Game/Assets/Images/galaga.png");
	spriteComponent->SetTexture(texture);
	SpriteAnimation animation(Vector2D::Zero, Vector2D(32.f, 32.f), 1, 1, 0.f);
	int idx = spriteComponent->AddAnimation(animation);
	spriteComponent->Start(idx);
	// Setup ColliderComponent.
	Vector2D size = spriteComponent->GetScaledSize();
	colliderComponent->SetLayer(CollisionLayer::Player);
	colliderComponent->SetBounds(SDL_Rect{ 0, 0, (int)size.x, (int)size.y });

	Vector2D windowSize = GalagaApplication::Get()->GetWindowSize();
	xBound = windowSize.x - 32;
}

void PlayerShip::Update(float deltaTime)
{
	Ship::Update(deltaTime);

	HandleInput(deltaTime);
}

void PlayerShip::HandleInput(float deltaTime)
{
	if (Input::IsKeyDown(SDL_SCANCODE_D))
	{
		// std::cout << "d pressed" << std::endl;
		if (transform->GetPosition().x < xBound)
			transform->Translate(Vector2D(moveSpeed * deltaTime, 0));
	}
	else if (Input::IsKeyDown(SDL_SCANCODE_A))
	{
		// std::cout << "a pressed" << std::endl;
		if (transform->GetPosition().x > 0.f)
			transform->Translate(Vector2D(-moveSpeed * deltaTime, 0));
	}
	static int idx;
	// Fire Bullet.
	if (Input::IsKeyDown(SDL_SCANCODE_SPACE))
	{
		// std::cout << "SPACE pressed" << std::endl;
		if (idx++ == 0)
			Fire();
	}
	else if (Input::IsKeyUp(SDL_SCANCODE_SPACE))
	{
		idx = 0;
	}
}

void PlayerShip::Fire()
{
	Scene* scene = SceneManager::GetActiveScene();
	scene->AddToScene(std::make_shared<Bullet>(GetBulletSpawnPos(), 0.f, 200.f, CollisionLayer::Player));
}
