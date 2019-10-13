#include "GalagaScene.h"
#include "SDL.h"
#include "Core/Math/Vector2D.h"
#include "GalagaApplication.h"
#include "Ships/PlayerShip.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/TransformComponent.h"

#include <iostream>

GalagaScene::GalagaScene()
{
	SpawnPlayerShip();
}

GalagaScene::~GalagaScene()
{
	for (auto& go : gameObjects)
		delete go;
}

void GalagaScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	for (auto& go : gameObjects)
	{
		if (go->IsActive())
			go->Update(deltaTime);
	}
}

void GalagaScene::SpawnPlayerShip()
{
	playerShip = new PlayerShip(Vector2D(0, 0), 500.f, 1.f);

	Vector2D windowSize = GalagaApplication::Get()->GetWindowSize();
	Vector2D spriteSize = playerShip->GetComponent<SpriteComponent>()->GetSize();
	playerShip->GetTranform()->SetPosition(Vector2D(windowSize.x / 2, windowSize.y - spriteSize.y));

	gameObjects.push_back(playerShip);
}
