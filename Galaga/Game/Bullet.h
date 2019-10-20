#ifndef BULLET_H
#define BULLET_H
#include "Core/GameObjects/GameObject.h"

#include <iostream>

class SpriteComponent;
class ColliderComponent;
class VelocityComponent;
struct Vector2D;
enum class CollisionLayer;

class Bullet : public GameObject
{
public:
	Bullet(const Vector2D& pos, float angle, float speed, CollisionLayer collisionLayer, float lifeSpan = 5.f);
	void Update(float deltaTime) override;

	void OnHitted();

protected:
	void OnCollisionEnter(ColliderComponent* other);

	SpriteComponent* spriteComponent;
	ColliderComponent* colliderComponent;
	VelocityComponent* velocityComponent;

	float lifeSpan;
	float lifeSpanCounter = 0.f;
};

#endif // !BULLET_H
