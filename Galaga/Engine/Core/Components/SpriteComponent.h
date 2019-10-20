#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "BaseComponent.h"
// STL
#include <vector>
// Core
#include "Render/Drawable.h"
#include "Core/Math/Vector2D.h"
#include "Core/TypeDefs.h"

struct SDL_Texture;

class SpriteComponent : public BaseComponent, public Drawable
{
public:
	SpriteComponent(GameObject* _owner);
	virtual ~SpriteComponent();

	virtual void Update(float deltaTime) override {}
	inline void SetTexture(SDL_Texture* _texture) { texture = _texture; }
	void SetTexture(SDL_Texture* _texture, SDL_RendererFlip _flip);
	inline SDL_Texture* GetTexture() const { return texture; }
	virtual Vector2D GetSize() const;
	Vector2D GetScaledSize() const;
	Vector2D GetOrigin(Space space) const;
	
	inline float GetScale() const { return scale; }
	inline void SetScale(float _scale) { scale = _scale; }
	inline const Vector2D& GetPosOffset() const { return posOffset; }
	inline void SetPosOffset(const Vector2D& offset) { posOffset = offset; }

	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetAlpha(Uint8 a);

	// Drawable.
	SDL_Texture* GetRenderTarget(SDL_Rect& srcRect, SDL_Rect& dstRect, float& angle, SDL_RendererFlip& flip, SDL_Color& color);

private:
	SDL_Texture* texture;
	SDL_RendererFlip flip;
	SDL_Color color;

	float scale = 1.f;
	float scaleFactor;
	Vector2D posOffset;
};

#endif // !SPRITECOMPONENT_H
