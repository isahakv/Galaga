#include "Renderer.h"
#include "SDL.h"
#include "SDL_image.h"
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
	SDL_RenderClear(renderer);
}

#include <iostream>

void Renderer::Render(SDL_Texture* texture, const Vector2D& pos, const Vector2D& size, int sortingLayer)
{
	SDL_Rect destRect{ pos.x, pos.y, size.x, size.y};
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void Renderer::RenderFrame()
{
	SDL_Texture* texture = nullptr;
	Vector2D pos, size;
	int sortingLayer;
	for (auto drawable : drawables)
	{
		texture = drawable->GetRenderTarget(pos, size);
		if (texture == nullptr)
			continue;
		sortingLayer = drawable->GetSortOrder();
		Render(texture, pos, size, sortingLayer);
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
		drawables.push_back(drawable);
}

void Renderer::UnregisterDrawable(Drawable* drawable)
{
	std::vector<Drawable*>::iterator it = std::find(drawables.begin(), drawables.end(), drawable);
	// If drawable found in drawables, then remove it.
	if (it != drawables.end())
		drawables.erase(it);
}
