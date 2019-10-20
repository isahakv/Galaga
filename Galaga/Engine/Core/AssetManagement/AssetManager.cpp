#include "AssetManager.h"
#include "SDL_image.h"
#include "../../Render/Renderer.h"

AssetManager* AssetManager::instance = nullptr;

AssetManager* AssetManager::Get()
{
	if (instance == nullptr)
		instance = new AssetManager();
	return instance;
}

SDL_Texture* AssetManager::LoadTexture(const char* path)
{
	// If we not cached this texture yet, then load it.
	if (textures[path] == nullptr)
	{
		SDL_Renderer* renderer = Renderer::Get()->GetRawRenderer();

		SDL_Surface* surface = IMG_Load(path);
		if (surface == nullptr)
			return nullptr;

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		textures[path] = texture;
	}
	return textures[path];
}

TTF_Font* AssetManager::LoadFont(const char* path, int size)
{
	std::string str;
	str.append(path);
	str.append(std::to_string(size));
	// If we not cached this font yet, then load it.
	if (fonts[str] == nullptr)
	{
		//this opens a font style and sets a size
		TTF_Font* font = TTF_OpenFont(path, size);
		fonts[str] = font;
	}
	return fonts[str];
}

SDL_Texture* AssetManager::GetText(const char* text, const char* path, int size)
{
	TTF_Font* font = LoadFont(path, size);

	SDL_Renderer* renderer = Renderer::Get()->GetRawRenderer();
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	return texture;
}

AssetManager::~AssetManager()
{
	for (auto map : textures)
		SDL_DestroyTexture(map.second);
	textures.clear();
	for (auto map : fonts)
		TTF_CloseFont(map.second);
	fonts.clear();
}
