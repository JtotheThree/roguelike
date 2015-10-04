#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <map>

class Input {
public:
	Input();

	void BeginNewFrame();

	void KeyDownEvent( const SDL_Event& event );
	void KeyUpEvent( const SDL_Event& event );

	bool WasKeyPressed( SDL_Scancode key );
	bool WasKeyReleased( SDL_Scancode key );
	bool IsKeyHeld( SDL_Scancode key );

private:
	std::map< SDL_Scancode, bool > held_keys;
	std::map< SDL_Scancode, bool > pressed_keys;
	std::map< SDL_Scancode, bool > released_keys;

};

#endif //INPUT_H
