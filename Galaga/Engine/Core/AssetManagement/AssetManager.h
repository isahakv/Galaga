#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <map>
#include <string>
#include "SDL_ttf.h"

struct SDL_Texture;

class AssetManager
{
public:
	static AssetManager* Get();
	SDL_Texture* LoadTexture(const char* path);
	TTF_Font* LoadFont(const char* path, int size);
	SDL_Texture* GetText(const char* text, const char* path, int size);

private:
	AssetManager() {}
	~AssetManager();

	static AssetManager* instance;

	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};

#endif // !ASSETMANAGER_H
