#include "BackgroundParticle.h"
#include "Core/Math/Vector2D.h"
#include "Core/Math/Math.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/AssetManagement/AssetManager.h"

BackgroundParticle::BackgroundParticle(const SDL_Rect& bounds, const char* texturePath,
	int numStars, float minStarLifeSpan, float maxStarLifeSpan, float fadeInAlpha, float fadeOutAlpha)
	: bounds(bounds), minStarLifeSpan(minStarLifeSpan), maxStarLifeSpan(maxStarLifeSpan), fadeInAlpha(fadeInAlpha), fadeOutAlpha(fadeOutAlpha)
{
	starTexture = AssetManager::Get()->LoadTexture(texturePath);

	for (int i = 0; i < numStars; i++)
		SpawnStar();
}

void BackgroundParticle::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	for (auto& star : stars)
	{
		star.lifeSpanCounter += deltaTime;
		if (star.lifeSpanCounter > star.lifeSpan)
			RespawnStar(star);
		Fade(star);
	}
}

void BackgroundParticle::Fade(Star& star)
{
	// FadeIn.
	if (star.lifeSpanCounter < star.fadeInTime)
	{
		float alpha = Math::Lerp(0, star.fadeInTime, star.lifeSpanCounter);
		star.starSprite->SetAlpha(Uint8(alpha * 255));
	}
	// FadeOut.
	else if (star.lifeSpanCounter > star.fadeOutTime)
	{
		float alpha = Math::Lerp(star.fadeOutTime, star.lifeSpan, star.lifeSpanCounter);
		star.starSprite->SetAlpha(Uint8((1 - alpha) * 255));
	}
}

void BackgroundParticle::SpawnStar()
{
	Star star;
	SpriteComponent* starSprite = AddComponent<SpriteComponent>();
	starSprite->SetTexture(starTexture);
	starSprite->SetPosOffset(GetPointInBounds());
	starSprite->SetScale(0.3f);
	starSprite->SetAlpha(0);
	starSprite->SetSortOrder(-1);
	star.starSprite = starSprite;
	star.lifeSpan = Math::Random(minStarLifeSpan, maxStarLifeSpan);
	star.fadeInTime = fadeInAlpha * star.lifeSpan;
	star.fadeOutTime = fadeOutAlpha * star.lifeSpan;
	stars.push_back(star);
}

void BackgroundParticle::RespawnStar(Star& star)
{
	star.lifeSpanCounter = 0;
	star.starSprite->SetPosOffset(GetPointInBounds());
	star.lifeSpan = Math::Random(minStarLifeSpan, maxStarLifeSpan);
	star.fadeInTime = fadeInAlpha * star.lifeSpan;
	star.fadeOutTime = fadeOutAlpha * star.lifeSpan;
}

Vector2D BackgroundParticle::GetPointInBounds() const
{
	Vector2D point;
	point.x = (float)Math::Random(bounds.x, bounds.w);
	point.y = (float)Math::Random(bounds.y, bounds.h);
	return point;
}
