#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "BaseComponent.h"
#include "Render/Drawable.h"
#include "Core/Math/Vector2D.h"
#include "Core/TypeDefs.h"

struct SDL_Texture;

class SpriteComponent : public BaseComponent, Drawable
{
public:
	SpriteComponent(GameObject* _owner);
	virtual ~SpriteComponent();

	void Update(float deltaTime) override;
	inline void SetTexture(SDL_Texture* _texture) { texture = _texture; }
	void SetTexture(SDL_Texture* _texture, SDL_RendererFlip _flip);
	inline SDL_Texture* GetTexture() const { return texture; }
	Vector2D GetSize() const;
	Vector2D GetOrigin(Space space) const;

	// Drawable.
	SDL_Texture* GetRenderTarget(Vector2D& pos, float& angle, SDL_RendererFlip& flip, Vector2D& size);

private:
	SDL_Texture* texture;
	SDL_RendererFlip flip;
};

#endif // !SPRITECOMPONENT_H
