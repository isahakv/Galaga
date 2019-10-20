#include "Application.h"
// SDL
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
// Core
#include "Core/TypeDefs.h"
#include "Physics/Physics.h"
#include "Render/Renderer.h"
#include "Core/Time/Time.h"
#include "Core/Input/Input.h"
#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
// STD
#include <iostream>
#include <random>
#include <ctime>

float Application::scaleFactor = 0.f;

Application::Application()
{
	window = nullptr;
	activeScene = nullptr;
}

void Application::Init(int width, int height, bool isFullScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		IMG_Init(IMG_INIT_PNG);
		TTF_Init();
		srand((Uint32)time(0));

		// Deal with aspect ratio.
		ResolveAspectRatio(width, height);
		// Deal with scaling.
		scaleFactor = width / (float)targetScreenWidth;
		std::cout << "scalingFactor: " << scaleFactor << std::endl;

		window = SDL_CreateWindow("Galaga", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
			, width, height, isFullScreen ? SDL_WINDOW_FULLSCREEN : 0);
		Time::Init(60);
		Renderer::Get()->Init(window);
	}
}

int Application::Run()
{
	isRunnig = true;
	activeScene = SceneManager::GetActiveScene();

	while (isRunnig)
	{
		// Input Update.
		Input::Update();
		HandleInput();
		// Render Update.
		Renderer::Get()->ClearFrame();
		// Debugging.
		// std::cout << Time::GetDeltaSeconds() << std::endl;
		// Debugging.
		activeScene->Update(Time::GetDeltaSeconds());
		Physics::Get()->Update();
		Renderer::Get()->RenderFrame();
		// Time Update.
		Time::CalculateDeltaTime();
	}

	return 0;
}

void Application::HandleInput()
{
	if (Input::IsKeyType(SDL_QUIT))
		Exit();
}

void Application::ResolveAspectRatio(int& width, int& height)
{
	float aspect = width / (float)height;
	// If current aspect is wider then target aspect.
	if (aspect > targetAspectRatio)
		width = height * targetAspectRatio;
	// If current aspect is heighter then target aspect.
	else if (aspect < targetAspectRatio)
		height = width * (1 / targetAspectRatio);
}

void Application::Exit()
{
	isRunnig = false;
}

Vector2D Application::GetWindowSize() const
{
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	return Vector2D((float)width, (float)height);
}

Application::~Application()
{
	Renderer::Get()->Destroy();
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
