#ifndef BACKGROUNDPARTICLE_H
#define BACKGROUNDPARTICLE_H
#include "core/GameObjects/GameObject.h"
// STD
#include <vector>
// SDL
#include "SDL_rect.h"

struct SDL_Texture;
struct Vector2D;
class SpriteComponent;

struct Star
{
	SpriteComponent* starSprite;
	float lifeSpan;
	float lifeSpanCounter = 0;
	float fadeInTime;
	float fadeOutTime;
};

class BackgroundParticle : public GameObject
{
public:
	BackgroundParticle(const SDL_Rect& bounds, const char* texturePath, int numStars,
		float minStarLifeSpan, float maxStarLifeSpan, float fadeInAlpha, float fadeOutAlpha);

	void Update(float deltaTime) override;

private:
	void SpawnStar();
	void RespawnStar(Star& star);
	Vector2D GetPointInBounds() const;
	void Fade(Star& star);

	std::vector<Star> stars;
	float minStarLifeSpan;
	float maxStarLifeSpan;
	float fadeInAlpha;
	float fadeOutAlpha;

	SDL_Texture* starTexture;
	SDL_Rect bounds;
};

#endif // !BACKGROUNDPARTICLE_H
