#pragma once
#include "Ship.h"
#include "Core/Math/Vector2D.h"

class PlayerShip : public Ship
{
public:
	PlayerShip(const Vector2D& pos, const Vector2D& _bulletOffset, float _moveSpeed, float _fireRate);

	virtual void Update(float deltaTime) override;

private:
	void HandleInput(float deltaTime);
	Vector2D GetBulletSpawnPos() const;
	void Fire();

	Vector2D bulletOffset;
	float moveSpeed;
	float fireRate;
};
