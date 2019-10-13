#include "Input.h"

SDL_Event Input::event;

void Input::Update()
{
	SDL_PollEvent(&event);
}

bool Input::IsKeyType(Uint32 keyType)
{
	return event.type == keyType;
}

bool Input::IsKeyDown(SDL_Keycode keyCode)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == keyCode)
		return true;
	return false;
}

bool Input::IsKeyUp(SDL_Keycode keyCode)
{
	if (event.type == SDL_KEYUP && event.key.keysym.sym == keyCode)
		return true;
	return false;
}
