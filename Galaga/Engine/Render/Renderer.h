#ifndef RENDERER_H
#define RENDERER_H
// STD
#include <vector>
// SDL
#include <SDL_render.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct Vector2D;
class Drawable;

class Renderer
{
public:
	static Renderer* Get();
	bool Init(SDL_Window* window);
	void ClearFrame();
	void RenderFrame();
	void Destroy();

	void RegisterDrawable(Drawable* drawable);
	void UnregisterDrawable(Drawable* drawable);

	inline SDL_Renderer* GetRawRenderer() const { return renderer; }

	// DEBUG.
	void DrawDebugRect(SDL_Rect* rect);

private:
	void Render(SDL_Texture* texture, const Vector2D& pos, float angle, SDL_RendererFlip flip, const Vector2D& size);
	void SortDrawables();

	SDL_Renderer* renderer;
	std::vector<Drawable*> drawables;

	static Renderer* instance;
};

#endif // !RENDERER_H
