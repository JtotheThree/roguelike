#include "Input.h"

Input::Input() :
	held_keys(),
	pressed_keys(),
	released_keys()
{}

void Input::BeginNewFrame() {
	pressed_keys.clear();
	released_keys.clear();
}

void Input::KeyDownEvent( const SDL_Event& event ) {
	pressed_keys[ event.key.keysym.scancode ] = true;
	held_keys[ event.key.keysym.scancode ] = true;
}

void Input::KeyUpEvent( const SDL_Event& event) {
	released_keys[ event.key.keysym.scancode ] = true;
	held_keys[ event.key.keysym.scancode ] = false;
}

bool Input::WasKeyPressed( SDL_Scancode key ) {
	return pressed_keys[ key ];
}

bool Input::WasKeyReleased( SDL_Scancode key ) {
	return released_keys[ key ];
}

bool Input::IsKeyHeld( SDL_Scancode key ) {
	return held_keys[ key ];
}
