#include "Scene.h"
#include "../GameObjects/GameObject.h"

Scene::~Scene()
{
}

void Scene::Update(float deltaTime)
{
	for (int i = gameObjects.size() - 1; i >= 0; i--)
	{
		if (gameObjects[i]->IsPendingToDestroy())
		{
			RemoveFromScene(gameObjects[i]);
			continue;
		}

		gameObjects[i]->Update(deltaTime);
	}
}

void Scene::AddToScene(const std::shared_ptr<GameObject>& gameObject)
{
	std::vector<std::shared_ptr<GameObject>>::iterator it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
	// If object not found in scene, then add it.
	if (it == gameObjects.end())
		gameObjects.push_back(gameObject);
}

void Scene::RemoveFromScene(const std::shared_ptr<GameObject>& gameObject)
{
	std::vector<std::shared_ptr<GameObject>>::iterator it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
	// If object found in scene, then remove it.
	if (it != gameObjects.end())
		gameObjects.erase(it);
}
