#include "GalagaScene.h"
#include "SDL.h"
#include "Core/Math/Vector2D.h"
#include "GalagaApplication.h"
#include "Ships/PlayerShip.h"
#include "Ships/EnemyShip.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/TransformComponent.h"

#include <iostream>

GalagaScene::GalagaScene()
{
	SpawnPlayerShip();

	// Spawn enemies.
	Vector2D windowCenter = GalagaApplication::Get()->GetWindowSize() / 2;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			SpawnEnemyShip(Vector2D(float(j * 32), windowCenter.y - float(i * 32)));
		}
	}
}

GalagaScene::~GalagaScene()
{
	for (auto& go : gameObjects)
		delete go;
}

void GalagaScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GalagaScene::SpawnPlayerShip()
{
	playerShip = new PlayerShip(Vector2D(0, 0), Vector2D(0, -20), 500.f, 1.f);

	Vector2D windowSize = GalagaApplication::Get()->GetWindowSize();
	Vector2D spriteSize = playerShip->GetComponent<SpriteComponent>()->GetSize();
	playerShip->GetTranform()->SetPosition(Vector2D(windowSize.x / 2, windowSize.y - spriteSize.y));

	gameObjects.push_back(playerShip);
}

void GalagaScene::SpawnEnemyShip(const Vector2D& pos)
{
	EnemyShip* enemyShip = new EnemyShip(pos, Vector2D(0, 0));
	// Vector2D windowSize = GalagaApplication::Get()->GetWindowSize();
	// enemyShip->GetTranform()->SetPosition(Vector2D(windowSize.x / 2, windowSize.y / 2));

	gameObjects.push_back(enemyShip);
}
