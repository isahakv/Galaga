#include "PlayerShip.h"
#include "Physics/Physics.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/ColliderComponent.h"
#include "Core/AssetManagement/AssetManager.h"
#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "Core/Input/Input.h"
#include "Bullet.h"
#include <iostream>

PlayerShip::PlayerShip(const Vector2D& pos, const Vector2D& _bulletOffset, float _moveSpeed, float _fireRate)
	: Ship(pos), bulletOffset(_bulletOffset), moveSpeed(_moveSpeed), fireRate(_fireRate)
{
	SDL_Texture* texture = AssetManager::LoadTexture("galaga.png");
	spriteComponent->SetTexture(texture);
	// Setup ColliderComponent.
	Vector2D size = spriteComponent->GetSize();
	colliderComponent->SetLayer(CollisionLayer::Player);
	colliderComponent->SetBounds(SDL_Rect{ 0, 0, (int)size.x, (int)size.y });
}

void PlayerShip::Update(float deltaTime)
{
	Ship::Update(deltaTime);

	HandleInput(deltaTime);
}

void PlayerShip::HandleInput(float deltaTime)
{
	if (Input::IsKeyDown(SDLK_d))
	{
		// std::cout << "d pressed" << std::endl;
		transform->Translate(Vector2D(moveSpeed * deltaTime, 0));
	}
	else if (Input::IsKeyDown(SDLK_a))
	{
		// std::cout << "a pressed" << std::endl;
		transform->Translate(Vector2D(-moveSpeed * deltaTime, 0));
	}
	static int idx;
	// Fire Bullet.
	if (Input::IsKeyDown(SDLK_SPACE))
	{
		// std::cout << "SPACE pressed" << std::endl;
		if (idx++ == 0)
			Fire();
	}
	else if (Input::IsKeyUp(SDLK_SPACE))
	{
		idx = 0;
	}
}

Vector2D PlayerShip::GetBulletSpawnPos() const
{
	Vector2D shipOrigin = spriteComponent->GetOrigin(Space::World);
	return Vector2D(shipOrigin + bulletOffset);
}

void PlayerShip::Fire()
{
	Scene* scene = SceneManager::GetActiveScene();
	scene->AddToScene(new Bullet(GetBulletSpawnPos(), 0, 100));
}
