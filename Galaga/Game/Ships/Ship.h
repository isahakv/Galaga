#pragma once
#include "../../Engine/Core/GameObjects/GameObject.h"

class SpriteComponent;
struct Vector2D;

class Ship : public GameObject
{
public:
	Ship(const Vector2D& pos);

protected:
	SpriteComponent* spriteComponent;
};
