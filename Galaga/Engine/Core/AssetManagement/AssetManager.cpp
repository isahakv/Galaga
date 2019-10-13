#include "AssetManager.h"
#include "SDL_image.h"
#include "../../Render/Renderer.h"

SDL_Texture* AssetManager::LoadTexture(const char* path)
{
	SDL_Renderer* renderer = Renderer::Get()->GetRawRenderer();

	SDL_Surface* surface = IMG_Load(path);
	if (surface == nullptr)
		return nullptr;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}
