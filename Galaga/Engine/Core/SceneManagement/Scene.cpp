#include "Scene.h"
#include "../GameObjects/GameObject.h"

void Scene::Update(float deltaTime)
{
	for (auto go : gameObjects)
		go->Update(deltaTime);
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
