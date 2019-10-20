#include "GalagaApplication.h"
#include "../Engine/Core/SceneManagement/SceneManager.h"
#include "GalagaScene.h"


GalagaApplication* GalagaApplication::instance = nullptr;

GalagaApplication::GalagaApplication()
{
}

GalagaApplication* GalagaApplication::Get()
{
	if (instance == nullptr)
		instance = new GalagaApplication();
	return instance;
}

void GalagaApplication::Init(int width, int height, bool isFullScreen)
{
	Application::Init(width, height, isFullScreen);

	// Loading Scene.
	GalagaScene* scene = new GalagaScene();
	SceneManager::LoadScene(scene);
}

GalagaApplication::~GalagaApplication()
{
	// Destroying Scene.
	Scene* activeScene = SceneManager::GetActiveScene();
	SceneManager::DestroyScene(activeScene);

	if (instance != nullptr)
		delete instance;
}
