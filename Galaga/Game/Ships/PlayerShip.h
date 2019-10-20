#pragma once
#include "Ship.h"

class PlayerShip : public Ship
{
public:
	PlayerShip(const Vector2D& pos, const Vector2D& _bulletOffset, float _moveSpeed, float _fireRate);

	virtual void Update(float deltaTime) override;

private:
	void HandleInput(float deltaTime);
	virtual void Fire() override;

	float moveSpeed;
	float fireRate;
	int xBound;
};
