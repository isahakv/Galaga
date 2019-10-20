#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <memory>

struct SDL_Renderer;
class GameObject;

/** Base class for Scenes. */
class Scene
{
public:
	virtual ~Scene();
	virtual void Update(float deltaTime);
	void AddToScene(const std::shared_ptr<GameObject>& gameObject);
	void RemoveFromScene(const std::shared_ptr<GameObject>& gameObject);

protected:
	std::vector<std::shared_ptr<GameObject>> gameObjects;
};

#endif // !SCENE_H
