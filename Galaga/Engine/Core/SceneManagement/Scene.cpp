#include "Scene.h"
#include "../GameObjects/GameObject.h"

void Scene::Update(float deltaTime)
{
	for (int i = gameObjects.size() - 1; i >= 0; i--)
		gameObjects[i]->Update(deltaTime);
}

void Scene::Destroy(GameObject* gameObject)
{
	RemoveFromScene(gameObject);
	delete gameObject;
}

void Scene::AddToScene(GameObject* gameObject)
{
	std::vector<GameObject*>::iterator it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
	// If object not found in scene, then add it.
	if (it == gameObjects.end())
		gameObjects.push_back(gameObject);
}

void Scene::RemoveFromScene(GameObject* gameObject)
{
	std::vector<GameObject*>::iterator it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
	// If object found in scene, then remove it.
	if (it != gameObjects.end())
		gameObjects.erase(it);
}
