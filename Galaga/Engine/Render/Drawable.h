#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Core/Math/Vector2D.h"

struct SDL_Texture;

/** Inherit from this class if you want to draw something. */
class Drawable
{
public:
	Drawable() : sortOrder(0) {}
	Drawable(int sortingOrder) : sortOrder(sortingOrder) {}

	inline void SetSortOrder(int order) { sortOrder = order; }
	inline int GetSortOrder() const { return sortOrder; }
	virtual SDL_Texture* GetRenderTarget(Vector2D& pos, Vector2D& size) = 0;

private:
	int sortOrder;
};

#endif // !DRAWABLE_H
