#ifndef TIME_H
#define TIME_H
#include "SDL_timer.h"

class Time
{
private:
	Time();

	static Uint32 FPS;
	static Uint32 frameDelay;
	static Uint32 frameStart;
	static Uint32 deltaTime;
public:
	static void Init(Uint32 fixedFPS = 0);
	static void CalculateDeltaTime();
	inline static Uint32 GetDeltaTime() { return deltaTime; }
	static float GetDeltaSeconds();
	inline static bool IsFixedFrameRate() { return ((Uint32)FPS) != 0; }
};

#endif // !TIME_H
