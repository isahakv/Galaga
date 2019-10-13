#ifndef RENDERER_H
#define RENDERER_H
#include <vector>

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
private:
	void Render(SDL_Texture* texture, const Vector2D& pos, const Vector2D& size, int sortingLayer);

	static Renderer* instance;

	SDL_Renderer* renderer;
	std::vector<Drawable*> drawables;
};

#endif // !RENDERER_H
