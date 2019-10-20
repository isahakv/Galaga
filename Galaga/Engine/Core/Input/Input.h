#ifndef INPUT_H
#define INPUT_H
#include "SDL_events.h"
#include "Core/Math/Vector2D.h"

class Input
{
public:
	static void Update();
	static bool IsKeyType(Uint32 keyType); // Returns true if the keyType is current key type.
	static bool IsKeyDown(SDL_Scancode scanCode); // Returns true if the key was just pressed.
	static bool IsKeyUp(SDL_Scancode scanCode); // Returns true if the key was just released.
	static bool IsMouseKeyDown(Uint8 index, Vector2D& position);
	static bool IsMouseKeyUp(Uint8 index, Vector2D& position);

private:
	static SDL_Event event;
	static const Uint8* keyboardState;
	static Uint32 mouseState;
	static bool isLeftMousePressed;
	static bool isLeftMouseReleased;
};

#endif // !INPUT_H
