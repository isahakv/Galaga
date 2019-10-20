#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <SDL_render.h>
#include "Core/Math/Vector2D.h"
#include "Renderer.h"

struct SDL_Texture;

/** Inherit from this class if you want to draw something. */
class Drawable
{
public:
	Drawable() : sortOrder(0) {}
	Drawable(int sortingOrder) : sortOrder(sortingOrder) {}

	inline void SetSortOrder(int order)
	{ 
		sortOrder = order;
		Renderer::Get()->SortDrawables();
	}
	inline int GetSortOrder() const { return sortOrder; }
	virtual SDL_Texture* GetRenderTarget(SDL_Rect& srcRect, SDL_Rect& dstRect, float& angle, SDL_RendererFlip& flip, SDL_Color& color) = 0;

private:
	int sortOrder;
};

#endif // !DRAWABLE_H
