#ifndef APPLICATION_H
#define APPLICATION_H
#include "Core/Math/Vector2D.h"

struct SDL_Window;
class Scene;

/** Abstact base Application class */
class Application
{
protected:
	Application();
	virtual ~Application();

public:
	virtual void Init(int width, int height, bool isFullScreen);
	int Run();
	void Exit();
	Vector2D GetWindowSize() const;
	inline static float GetScaleFactor() { return scaleFactor; }

private:
	bool isRunnig = false;

	void HandleInput();
	void ResolveAspectRatio(int& width, int& height);

protected:
	SDL_Window* window;
	Scene* activeScene;
	// Scale factor relative to target screen size.
	static float scaleFactor;
};

#endif // !APPLICATION_H
