#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "BaseComponent.h"
#include "Render/Drawable.h"
#include "Core/Math/Vector2D.h"

struct SDL_Texture;

class SpriteComponent : public BaseComponent, Drawable
{
public:
	SpriteComponent(GameObject* _owner, SDL_Texture* _texture, int sortingOrder);
	~SpriteComponent();

	void Update(float deltaTime) override;
	inline void SetTexture(SDL_Texture* _texture) { texture = _texture; }
	inline SDL_Texture* GetTexture() const { return texture; }
	Vector2D GetSize() const;

	// Drawable.
	SDL_Texture* GetRenderTarget(Vector2D& pos, Vector2D& size) override;

private:
	SDL_Texture* texture;
};

#endif // !SPRITECOMPONENT_H
