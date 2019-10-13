#pragma once
#include "Ship.h"

class PlayerShip : public Ship
{
public:
	PlayerShip(const Vector2D& pos, float _moveSpeed, float _fireRate);

	virtual void Update(float deltaTime) override;

private:
	void HandleInput(float deltaTime);
	void Fire();

	float moveSpeed;
	float fireRate;
};
