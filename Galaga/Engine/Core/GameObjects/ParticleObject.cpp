#include "ParticleObject.h"
// STD
#include <functional>
// Core
#include "Core/Math/Vector2D.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/AnimatedSpriteComponent.h"
#include "Core/AssetManagement/AssetManager.h"

ParticleObject::ParticleObject(const Vector2D& pos, const char* texturePath,
	int width, int height, int numHoriz, int numVert, float showTime, bool loop)
{
	// Setup TransformComponent.
	transform->SetPosition(pos - Vector2D(width / 2.f, height / 2.f));
	// Setup SpriteComponent.
	spriteComponent = AddComponent<AnimatedSpriteComponent>();
	SDL_Texture* texture = AssetManager::Get()->LoadTexture(texturePath);
	spriteComponent->SetTexture(texture);
	SpriteAnimation animation(Vector2D::Zero, Vector2D(width, height), numHoriz, numVert, showTime, loop);
	animation.handlerAnimFinished = std::bind(&ParticleObject::DestroyWhenFinished, this);
	int idx = spriteComponent->AddAnimation(animation);
	spriteComponent->Start(idx);
}

void ParticleObject::DestroyWhenFinished()
{
	Destroy();
}
