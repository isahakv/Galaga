#include "PlayerShip.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/AssetManagement/AssetManager.h"
#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include "Core/Input/Input.h"
#include "Bullet.h"
#include <iostream>

PlayerShip::PlayerShip(const Vector2D& pos, float _moveSpeed, float _fireRate)
	: Ship(pos), moveSpeed(_moveSpeed), fireRate(_fireRate)
{
	SDL_Texture* texture = AssetManager::LoadTexture("galaga.png");
	spriteComponent->SetTexture(texture);
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
		transform->Translate(Vector2D((int)(moveSpeed * deltaTime), 0));
	}
	else if (Input::IsKeyDown(SDLK_a))
	{
		// std::cout << "a pressed" << std::endl;
		transform->Translate(Vector2D((int)(-moveSpeed * deltaTime), 0));
	}
	// Fire Bullet.
	if (Input::IsKeyDown(SDLK_SPACE))
	{
		// std::cout << "SPACE pressed" << std::endl;
		static int idx;
		if (idx++ == 0)
			Fire();
	}
}

void PlayerShip::Fire()
{
	Scene* scene = SceneManager::GetActiveScene();
	scene->AddToScene(new Bullet());
}
