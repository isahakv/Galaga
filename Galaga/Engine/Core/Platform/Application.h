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

private:
	bool isRunnig = false;

	void HandleInput();

protected:
	SDL_Window* window;
	Scene* activeScene;
};

#endif // !APPLICATION_H
