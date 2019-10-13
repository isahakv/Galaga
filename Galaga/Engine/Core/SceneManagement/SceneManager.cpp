#include "SceneManager.h"
#include "Scene.h"

Scene* SceneManager::activeScene = nullptr;

void SceneManager::LoadScene(Scene* sceneToLoad)
{
	activeScene = sceneToLoad;
}

void SceneManager::UnloadScene(Scene* sceneToUnload)
{
	// activeScene = nullptr;
}

void SceneManager::DestroyScene(Scene* sceneToDestroy)
{
	if (sceneToDestroy == nullptr)
		return;

	UnloadScene(sceneToDestroy);
	delete sceneToDestroy;
}
