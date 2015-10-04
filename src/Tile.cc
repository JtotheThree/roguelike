#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Tile.h"
#include "Graphics.h"
#include "Screen.h"

void Tile::Update( Graphics &graphics, std::chrono::milliseconds elapsed_time ) {
}

void Tile::Render( Graphics &graphics, const int x, const int y ) const {
	
	if ( background ) {
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = units::k_tile_size;
		rect.h = units::k_tile_size;

		graphics.RenderFillRect( rect, background_color );
	}

	if ( foreground ) {
		graphics.RenderChar( character, x, y, foreground_color );	
	}
}
