#ifndef TILES_H
#define TILES_H 

#include <SDL.h>
#include "Tile.h"

struct TileEntrance : Tile {
	TileEntrance();
};

struct TileGround : Tile {
	TileGround();
};

struct TileWall : Tile {
	TileWall();
};

struct TileEarth : Tile {
	TileEarth();
};

#endif //TILES_H
