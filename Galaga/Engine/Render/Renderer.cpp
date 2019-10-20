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

void Renderer::Render(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect, float angle, SDL_RendererFlip flip, SDL_Color color)
{
	if (color.r != 255 && color.g != 255 && color.b != 255)
		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	if (color.a != 255)
		SDL_SetTextureAlphaMod(texture, color.a);

	SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle, NULL, flip);
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
	SDL_Rect srcRect, dstRect;
	SDL_RendererFlip flip;
	float angle;
	SDL_Color color;
	for (auto drawable : drawables)
	{
		texture = drawable->GetRenderTarget(srcRect, dstRect, angle, flip, color);
		if (texture == nullptr)
			continue;
		Render(texture, srcRect, dstRect, angle, flip, color);
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
