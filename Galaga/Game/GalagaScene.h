#pragma once
#include "Core/SceneManagement/Scene.h"
#include "Core/Math/Vector2D.h"

class Ship;
class PlayerShip;
class EnemyShip;
class BackgroundParticle;
class HUDCanvas;

struct GameStats
{
	int playerLife = 3;
	int score = 0;
	int stage = 1;
	int maxStage = 5;
};

class GalagaScene : public Scene
{
public:
	GalagaScene();

	virtual void Update(float deltaTime) override;

	void OnShipHitted(Ship* ship);

private:
	std::shared_ptr<PlayerShip> playerShip;
	std::vector<EnemyShip*> enemyShips;
	std::shared_ptr<BackgroundParticle> backgroundParticle;
	std::shared_ptr<HUDCanvas> hudCanvas;

	GameStats gameStats;
	int enemyShipsDirection;
	Vector2D windowSize;

	void StartStage(int stage);
	void SpawnBackgroundParticle();
	void SpawnPlayerShip();
	void SpawnEnemyShips();
	void SpawnEnemyShip(const Vector2D& pos);

	bool IsEnemyShipOutOfBounds(int& direction);
	void SetEnemyShipsDirection(int direction);

	void DestroyAllEnemies();
	void DestroyAllBullets();
};
