#include "Renderer.h"
// STD
#include <algorithm>
// SDL
#include "SDL.h"
#include "SDL_image.h"
// Engine
#include "Core/Math/Vector2D.h"
#include "Render/Drawable.h"

Renderer* Renderer::instance = nullptr;

Renderer* Renderer::Get()
{
	if (instance == nullptr)
		instance = new Renderer();
	return instance;
}

bool Renderer::Init(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
		return false;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	return true;
}

void Renderer::ClearFrame()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Renderer::Render(SDL_Texture* texture, const Vector2D& pos, float angle, SDL_RendererFlip flip, const Vector2D& size)
{
	SDL_Rect destRect{ pos.x, pos.y, size.x, size.y};
	SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, NULL, flip);
}

void Renderer::SortDrawables()
{
	std::sort(drawables.begin(), drawables.end(), [](const Drawable* a, const Drawable* b)
		{
			return a->GetSortOrder() < b->GetSortOrder();
		});
}

void Renderer::RenderFrame()
{
	SDL_Texture* texture = nullptr;
	SDL_RendererFlip flip;
	Vector2D pos, size;
	float angle;
	for (auto drawable : drawables)
	{
		texture = drawable->GetRenderTarget(pos, angle, flip, size);
		if (texture == nullptr)
			continue;
		Render(texture, pos, angle, flip, size);
	}

	SDL_RenderPresent(renderer);
}

void Renderer::Destroy()
{
	SDL_DestroyRenderer(renderer);
}

void Renderer::RegisterDrawable(Drawable* drawable)
{
	std::vector<Drawable*>::iterator it = std::find(drawables.begin(), drawables.end(), drawable);
	// If drawable not found in drawables, then add it.
	if (it == drawables.end())
	{
		drawables.push_back(drawable);
		// Sort by Sort Order.
		SortDrawables();
	}
}

void Renderer::UnregisterDrawable(Drawable* drawable)
{
	std::vector<Drawable*>::iterator it = std::find(drawables.begin(), drawables.end(), drawable);
	// If drawable found in drawables, then remove it.
	if (it != drawables.end())
		drawables.erase(it);
}

void Renderer::DrawDebugRect(SDL_Rect* rect)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, rect);
}
