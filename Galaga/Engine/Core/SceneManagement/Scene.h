#ifndef SCENE_H
#define SCENE_H
#include <vector>

struct SDL_Renderer;
class GameObject;

/** Base class for Scenes. */
class Scene
{
public:
	virtual void Update(float deltaTime);
	void AddToScene(GameObject* gameObject);
	void RemoveFromScene(GameObject* gameObject);
	void Destroy(GameObject* gameObject);

protected:
	std::vector<GameObject*> gameObjects;
};

#endif // !SCENE_H
