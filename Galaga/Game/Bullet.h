#ifndef BULLET_H
#define BULLET_H
#include "Core/GameObjects/GameObject.h"

#include <iostream>

class SpriteComponent;
class ColliderComponent;
class VelocityComponent;
struct Vector2D;

class Bullet : public GameObject
{
public:
	Bullet(const Vector2D& pos, float angle, float speed);

protected:
	void OnCollisionEnter(ColliderComponent* other);

	SpriteComponent* spriteComponent;
	ColliderComponent* colliderComponent;
	VelocityComponent* velocityComponent;
};

#endif // !BULLET_H
