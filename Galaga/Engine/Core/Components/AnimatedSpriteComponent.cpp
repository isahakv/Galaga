#include "AnimatedSpriteComponent.h"
#include "Core/GameObjects/GameObject.h"
#include "Core/Components/TransformComponent.h"

/** class SpriteAnimation. */
SpriteAnimation::SpriteAnimation(const std::vector<AnimFrameData>& animFrames)
	: animFrames(animFrames), loop(false) {}

SpriteAnimation::SpriteAnimation(Vector2D offset, Vector2D size, int numHoriz, int numVert, float showTime, bool loop)
{
	this->loop = loop;
	SDL_Rect spriteRect{ (int)offset.x, (int)offset.y, (int)size.x, (int)size.y };
	for (int i = 0; i < numVert; i++)
	{
		for (int j = 0; j < numHoriz; j++)
		{
			spriteRect.x = (int)offset.x + j * (int)size.x;
			spriteRect.y = (int)offset.y + i * (int)size.y;
			AddFrame(AnimFrameData{ spriteRect, SDL_RendererFlip::SDL_FLIP_NONE, showTime });
		}
	}
}

const AnimFrameData& SpriteAnimation::GoToNextFrame()
{
	// If anim looped.
	if (loop)
		currFrameIdx = (currFrameIdx + 1) % animFrames.size();
	else // If not looped.
	{
		if (currFrameIdx < (animFrames.size() - 1))
			currFrameIdx++;
		else if (handlerAnimFinished)
			handlerAnimFinished();
	}
	// currFrameIdx = (currFrameIdx + 1) % animFrames.size();
	return animFrames[currFrameIdx];
}

int SpriteAnimation::AddFrame(const AnimFrameData& frameData)
{
	animFrames.push_back(frameData);
	return animFrames.size() - 1;
}

void SpriteAnimation::RemoveFrame(int index)
{
	animFrames.erase(animFrames.begin() + index);
}

/** class AnimatedSpriteComponent. */
AnimatedSpriteComponent::AnimatedSpriteComponent(GameObject* _owner)
	: SpriteComponent(_owner), textureOffset(0.f, 0.f), deltaSize(0.f, 0.f)
	, spriteFlip(SDL_RendererFlip::SDL_FLIP_NONE)
{
}

void AnimatedSpriteComponent::Update(float deltaTime)
{
	if (currentAnimIdx >= 0)
	{
		showTimeCounter -= deltaTime;
		if (showTimeCounter < 0)
		{
			AnimFrameData frameData = animations[currentAnimIdx].GoToNextFrame();
			SetFrame(frameData);
		}
	}
}

int AnimatedSpriteComponent::AddAnimation(const SpriteAnimation& animation)
{
	animations.push_back(animation);
	return animations.size() - 1;
}

void AnimatedSpriteComponent::RemoveAnimation(int index)
{
	animations.erase(animations.begin() + index);
}

SpriteAnimation AnimatedSpriteComponent::GetAnimation(int index) const
{
	SpriteAnimation anim = animations.at(index);
	return anim;
}

void AnimatedSpriteComponent::Start(int index)
{
	currentAnimIdx = index;
	SetFrame(animations[currentAnimIdx].GetCurrentFrame());
}

void AnimatedSpriteComponent::Stop()
{
	currentAnimIdx = -1;
}

Vector2D AnimatedSpriteComponent::GetSize() const
{
	return deltaSize;
}

SDL_Texture* AnimatedSpriteComponent::GetRenderTarget(SDL_Rect& srcRect, SDL_Rect& dstRect, float& angle, SDL_RendererFlip& flip, SDL_Color& color)
{
	SDL_Texture* texture = SpriteComponent::GetRenderTarget(srcRect, dstRect, angle, flip, color);
	Vector2D& pos = owner->GetTranform()->GetPosition();
	srcRect = SDL_Rect{ (int)textureOffset.x, (int)textureOffset.y, srcRect.w, srcRect.h };
	dstRect = SDL_Rect{ (int)pos.x, (int)pos.y, dstRect.w, dstRect.h };
	return texture;
}

void AnimatedSpriteComponent::SetFrame(const AnimFrameData& frameData)
{
	showTimeCounter = frameData.showTime;
	spriteFlip = frameData.flip;
	textureOffset = Vector2D{ (float)frameData.spriteRect.x, (float)frameData.spriteRect.y };
	deltaSize = Vector2D{ (float)frameData.spriteRect.w, (float)frameData.spriteRect.h };
}
