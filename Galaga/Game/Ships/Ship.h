#pragma once
#include <SDL_render.h>
#include "Core/GameObjects/GameObject.h"
#include "Core/Math/Vector2D.h"

class AnimatedSpriteComponent;
class ColliderComponent;
class VelocityComponent;
struct Vector2D;

class Ship : public GameObject
{
public:
	Ship(const Vector2D& pos, const Vector2D& _bulletOffset);
	virtual void Fire() = 0;

	void OnHitted();

protected:
	Vector2D GetBulletSpawnPos() const;

	AnimatedSpriteComponent* spriteComponent;
	ColliderComponent* colliderComponent;
	VelocityComponent* velocityComponent;

	Vector2D bulletOffset;
};
