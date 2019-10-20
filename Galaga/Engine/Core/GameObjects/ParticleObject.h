#ifndef PARTICLEOBJECT_H
#define PARTICLEOBJECT_H
#include "GameObject.h"

struct Vector2D;
class AnimatedSpriteComponent;

class ParticleObject : public GameObject
{
public:
	ParticleObject(const Vector2D& pos, const char* texturePath,
		int width, int height, int numHoriz, int numVert, float showTime, bool loop = true);

private:
	void DestroyWhenFinished();

	AnimatedSpriteComponent* spriteComponent;
};

#endif // !PARTICLEOBJECT_H
