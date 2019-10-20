#include "Input.h"

SDL_Event Input::event;
const Uint8* Input::keyboardState = NULL;
Uint32 Input::mouseState = SDL_MOUSEBUTTONUP;
bool Input::isLeftMousePressed = false;
bool Input::isLeftMouseReleased = false;

void Input::Update()
{
	SDL_PollEvent(&event);
	// Keyboard update.
	keyboardState = SDL_GetKeyboardState(NULL);

	// Mouse update.
	if (mouseState != event.button.type)
	{
		if (event.button.type == SDL_MOUSEBUTTONDOWN)
		{
			isLeftMousePressed = true;
			isLeftMouseReleased = false;
		}
		else if (event.button.type == SDL_MOUSEBUTTONUP)
		{
			isLeftMousePressed = false;
			isLeftMouseReleased = true;
		}
		mouseState = event.button.type;
	}
	else
	{
		isLeftMousePressed = false;
		isLeftMouseReleased = false;
	}
}

bool Input::IsKeyType(Uint32 keyType)
{
	return event.type == keyType;
}

bool Input::IsKeyDown(SDL_Scancode scanCode)
{
	/*if (event.type == SDL_KEYDOWN && event.key.keysym.sym == keyCode)
		return true;
	return false;*/
	return keyboardState[scanCode];
}

bool Input::IsKeyUp(SDL_Scancode scanCode)
{
	/*if (event.type == SDL_KEYUP && event.key.keysym.sym == keyCode)
		return true;
	return false;*/
	return !keyboardState[scanCode];
}

bool Input::IsMouseKeyDown(Uint8 index, Vector2D& position)
{
	// Return false, if indices don't match.
	if (event.button.button != index)
		return false;

	position = Vector2D(event.button.x, event.button.y);
	return isLeftMousePressed;
}

bool Input::IsMouseKeyUp(Uint8 index, Vector2D& position)
{
	// Return false, if indices don't match.
	if (event.button.button != index)
		return false;

	position = Vector2D(event.button.x, event.button.y);
	return isLeftMouseReleased;
}
