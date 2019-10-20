#ifndef ANIMATEDSPRITECOMPONENT_H
#define ANIMATEDSPRITECOMPONENT_H
#include "SpriteComponent.h"
// STL
#include <functional>

struct AnimFrameData
{
	SDL_Rect spriteRect;
	SDL_RendererFlip flip;
	float showTime;
};

class SpriteAnimation
{
public:
	typedef std::function<void(void)> HandlerAnimFinishedType;

	SpriteAnimation(const std::vector<AnimFrameData>& animFrames);
	// Sets animation frames based on specified params.
	SpriteAnimation(Vector2D offset, Vector2D size, int numHoriz, int numVert, float showTime, bool loop = true);

	// Get animation frame with specified index.
	inline const AnimFrameData& GetFrame(int index) const { return animFrames[index]; }
	
	// Get current animation frame.
	inline const AnimFrameData& GetCurrentFrame() const { return animFrames[currFrameIdx]; }
	const AnimFrameData& GoToNextFrame();

	// Add animation frame, return index of created frame.
	int AddFrame(const AnimFrameData& frameData);
	// Remove animation frame with specified index.
	void RemoveFrame(int index);

	// Events.
	HandlerAnimFinishedType handlerAnimFinished;

private:
	std::vector<AnimFrameData> animFrames;
	int currFrameIdx = 0;
	bool loop;
};

class AnimatedSpriteComponent : public SpriteComponent
{
public:
	AnimatedSpriteComponent(GameObject* _owner);

	void Update(float deltaTime) override;

	// Add animation, return index of created animation.
	int AddAnimation(const SpriteAnimation& animation);
	// Remove animation with specified index.
	void RemoveAnimation(int index);
	// Get animation with specified index.
	SpriteAnimation GetAnimation(int index) const;

	// Starts the animation of specified index.
	void Start(int index);
	// Stops the current playing animation.
	void Stop();

	Vector2D GetSize() const override;

	// Drawable.
	SDL_Texture* GetRenderTarget(SDL_Rect& srcRect, SDL_Rect& dstRect, float& angle, SDL_RendererFlip& flip, SDL_Color& color);

private:
	void SetFrame(const AnimFrameData& frameData);

	std::vector<SpriteAnimation> animations;
	int currentAnimIdx = -1;
	float showTimeCounter = 0;
	Vector2D textureOffset;
	Vector2D deltaSize;
	SDL_RendererFlip spriteFlip;
};

#endif // !ANIMATEDSPRITECOMPONENT_H
