#pragma once
#include "Core/SceneManagement/Scene.h"

class PlayerShip;

class GalagaScene : public Scene
{
public:
	GalagaScene();
	~GalagaScene();

	virtual void Update(float deltaTime) override;

private:
	PlayerShip* playerShip;

	void SpawnPlayerShip();
	void SpawnEnemyShip();
};
