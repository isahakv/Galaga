#include "Time.h"

Uint32 Time::FPS;
Uint32 Time::frameDelay;
Uint32 Time::frameStart;
Uint32 Time::deltaTime;

void Time::Init(Uint32 fixedFPS)
{
	frameStart = SDL_GetTicks();
	FPS = fixedFPS;
	if (FPS != 0)
		frameDelay = 1000 / FPS;
}

void Time::CalculateDeltaTime()
{
	deltaTime = SDL_GetTicks() - frameStart;
	frameStart = SDL_GetTicks();
	if (IsFixedFrameRate() && deltaTime < frameDelay)
	{
		int timeToWait = frameDelay - deltaTime;
		// Delay if we have fixed frame rate.
		SDL_Delay(timeToWait);
	}
}

float Time::GetDeltaSeconds()
{
	return deltaTime / 1000.f;
}
