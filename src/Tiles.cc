#include <SDL_image.h>
#include <iostream>
#include "Random.h"
#include "Tiles.h"

TileEntrance::TileEntrance() {
	blocked = false;
	background = false;
	foreground = true;
	tile_type = TileType::ENTRANCE;
	
	character = '<';

	foreground_color = { 255, 255, 102, 255 };
}

TileGround::TileGround() {
	blocked = false;
	background = true;
	foreground = true;
	tile_type = TileType::GROUND;

	character = '.';

	foreground_color = { 50, 50, 50, 255 };
	background_color = { 12, 10, 10, 255 };
}

TileWall::TileWall() {
	blocked = true;
	background = true;
	foreground = true;
	tile_type = TileType::WALL;

	character = 'X';//'#';

	foreground_color = { 20, 20, 20, 255 };
	background_color = { 234, 234, 200, 255 };
}

TileEarth::TileEarth() {
	blocked = true;
	background = true;
	foreground = false;
	tile_type = TileType::EARTH;

	character = '-';

	uint8_t random_color = Random::Int( 0, 30 );

	uint8_t r = 120 + random_color;
	uint8_t g = 92 + random_color;
	uint8_t b = 37 + random_color;

	foreground_color = { 92, 46, 0, 255 };
	background_color = { r, g, b, 255 };
	//background_color = { 200, 172, 117, 255 };
}
