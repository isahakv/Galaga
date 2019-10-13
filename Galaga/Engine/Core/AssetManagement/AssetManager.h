#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

struct SDL_Texture;

class AssetManager
{
public:
	static SDL_Texture* LoadTexture(const char* path);
};

#endif // !ASSETMANAGER_H
