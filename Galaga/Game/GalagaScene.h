#pragma once
#include "Core/SceneManagement/Scene.h"
#include "Core/Math/Vector2D.h"

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
	void SpawnEnemyShip(const Vector2D& pos);
};
