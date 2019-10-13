#pragma once
#include <SDL_render.h>
#include "Core/GameObjects/GameObject.h"

class SpriteComponent;
class ColliderComponent;
struct Vector2D;

class Ship : public GameObject
{
public:
	Ship(const Vector2D& pos);

protected:
	SpriteComponent* spriteComponent;
	ColliderComponent* colliderComponent;
};
