#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <chrono>

class Graphics;

enum class TileType {
	ENTRANCE,
	GROUND,
	WALL,
	EARTH
};

struct Tile {
	Tile() {} 

	bool background = false;
	bool foreground = false;

	bool blocked;

	TileType tile_type;
	uint8_t character = ' ';

	SDL_Color background_color = { 0, 0, 0, 255 };
	SDL_Color foreground_color = { 255, 255, 255, 255 };

	void Update( Graphics &graphics, std::chrono::milliseconds elapsed_time );
	void Render( Graphics &graphics, const int x, const int y ) const;
};

#endif //TILE_H
