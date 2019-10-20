#pragma once
#include "Ship.h"
#include <SDL_render.h>
#include "Core/Components/SpriteComponent.h"
#include "Core/AssetManagement/AssetManager.h"
#include "Core/Math/Vector2D.h"

class EnemyShip : public Ship
{
public:
	EnemyShip(const Vector2D& pos, const Vector2D& _bulletOffset, float _moveSpeed, float _minFireRate, float _maxFireRate);

	virtual void Update(float deltaTime) override;

private:
	virtual void Fire() override;

	Vector2D bulletOffset;
	float minfireRate;
	float maxfireRate;
	float fireRate;
	float fireRateCounter;
};
