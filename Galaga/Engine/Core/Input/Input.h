#ifndef INPUT_H
#define INPUT_H
#include "SDL_events.h"

class Input
{
public:
	static void Update();
	static bool IsKeyType(Uint32 keyType); // Returns true if the keyType is current key type.
	static bool IsKeyDown(SDL_Keycode keyCode); // Returns true if the key was just pressed.
	static bool IsKeyUp(SDL_Keycode keyCode); // Returns true if the key was just released.

private:
	static SDL_Event event;
};

#endif // !INPUT_H
