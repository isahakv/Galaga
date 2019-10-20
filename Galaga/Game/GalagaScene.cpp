#include "GalagaScene.h"
#include "SDL.h"
#include "Core/TypeDefs.h"
#include "Core/Math/Vector2D.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/VelocityComponent.h"
#include "GalagaApplication.h"
#include "Ships/PlayerShip.h"
#include "Ships/EnemyShip.h"
#include "Bullet.h"
#include "VFX/BackgroundParticle.h"
#include "UI/HUDCanvas.h"

#include <iostream>

GalagaScene::GalagaScene()
{
	windowSize = GalagaApplication::Get()->GetWindowSize();
	hudCanvas = std::make_shared<HUDCanvas>();
	hudCanvas->SetScoreText(gameStats.score);
	hudCanvas->SetHealthText(gameStats.playerLife);
	AddToScene(hudCanvas);

	SpawnBackgroundParticle();
	SpawnPlayerShip();
	StartStage(1);
}

void GalagaScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	int direction;
	if (IsEnemyShipOutOfBounds(direction))
		SetEnemyShipsDirection(direction);
}

void GalagaScene::OnShipHitted(Ship* ship)
{
	// If player ship.
	if (dynamic_cast<PlayerShip*>(ship))
	{
		gameStats.playerLife--;
		hudCanvas->SetHealthText(gameStats.playerLife);
		DestroyAllBullets();
		SpawnPlayerShip();
		if (gameStats.playerLife == 0)
		{
			// Game Over.
			DestroyAllEnemies();
			hudCanvas->ShowGameOverText();
		}
	}
	// If enemy ship.
	else
	{
		gameStats.score += 50;
		hudCanvas->SetScoreText(gameStats.score);
		// Remove from enemyShips vector.
		auto iter = std::find(enemyShips.begin(), enemyShips.end(), ship);
		if (iter != enemyShips.end())
			enemyShips.erase(iter);
		// Check if enemyShips vector is empty.
		if (enemyShips.empty())
			StartStage(gameStats.stage + 1);
	}
	ship->OnHitted();
}

void GalagaScene::StartStage(int stage)
{
	DestroyAllBullets();

	// Check if this was last stage.
	if (gameStats.stage == gameStats.maxStage)
	{
		hudCanvas->ShowYouWinText();
		return;
	}

	gameStats.stage = stage;
	hudCanvas->SetStageText(stage, gameStats.maxStage);
	SpawnEnemyShips();
}

void GalagaScene::SpawnBackgroundParticle()
{
	backgroundParticle = std::make_shared<BackgroundParticle>(SDL_Rect{ 0, 0, (int)windowSize.x, (int)windowSize.y },
		"Game/Assets/Images/star.png", 30, 3.f, 5.f, 0.3f, 0.6f);
	AddToScene(backgroundParticle);
}

void GalagaScene::SpawnPlayerShip()
{
	playerShip = std::make_shared<PlayerShip>(Vector2D(0, 0), Vector2D(0, -20), 500.f, 1.f);
	Vector2D spriteSize = playerShip->GetComponent<SpriteComponent>()->GetScaledSize();
	playerShip->GetTranform()->SetPosition(Vector2D(windowSize.x / 2.f, windowSize.y - spriteSize.y));
	AddToScene(playerShip);
}

void GalagaScene::SpawnEnemyShips()
{
	Vector2D windowCenter = windowSize / 2;
	float scaleFactor = GalagaApplication::GetScaleFactor();
	for (int i = 0; i < gameStats.stage; i++)
	{
		int m = 10 + (i * 2);
		for (int j = 0; j < m; j++)
		{
			int mid = m / 2;
			SpawnEnemyShip(Vector2D(windowCenter.x - float((j - mid) * 64 * scaleFactor), 160 - float(i * 32 * scaleFactor)));
		}
	}
	enemyShipsDirection = 1;
}

void GalagaScene::SpawnEnemyShip(const Vector2D& pos)
{
	std::shared_ptr<EnemyShip> enemyShip = std::make_shared<EnemyShip>(pos, Vector2D(0, 0), 50.f, 3.f, 10.f);
	enemyShips.push_back(enemyShip.get());
	AddToScene(enemyShip);
}

bool GalagaScene::IsEnemyShipOutOfBounds(int& direction)
{
	for (auto& enemyShip : enemyShips)
	{
		Vector2D& pos = enemyShip->GetTranform()->GetPosition();
		if (pos.x < 10.f)
		{
			direction = -1;
			return true;
		}
		else if (pos.x > (windowSize.x - 50.f))
		{
			direction = 1;
			return true;
		}
	}
	direction = 0;
	return false;
}

void GalagaScene::SetEnemyShipsDirection(int direction)
{
	if (enemyShipsDirection != direction)
	{
		for (auto& enemyShip : enemyShips)
		{
			VelocityComponent* vel = enemyShip->GetComponent<VelocityComponent>();
			vel->SetVelocity(vel->GetVelocity() * -1, Space::World);
			enemyShipsDirection = direction;
		}
	}
}

void GalagaScene::DestroyAllEnemies()
{
	auto iter = gameObjects.begin();
	while (iter != gameObjects.end())
	{
		if (EnemyShip* enemy = dynamic_cast<EnemyShip*>((*iter).get()))
			enemy->Destroy();
		iter++;
	}
	enemyShips.clear();
}

void GalagaScene::DestroyAllBullets()
{
	auto iter = gameObjects.begin();
	while (iter != gameObjects.end())
	{
		if (Bullet* bullet = dynamic_cast<Bullet*>((*iter).get()))
			bullet->Destroy();
		iter++;
	}
}
