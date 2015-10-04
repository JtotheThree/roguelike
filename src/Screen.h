#ifndef SCREEN_H
#define SCREEN_H

#include "Game.h"
#include "units.h"
#include "Player.h"
#include "Map.h"
#include "Rectangle.h"
#include "Tile.h"
#include "Vec2d.h"

class Screen {
public:
	Screen();
	~Screen();

	static void CenterScreen( const double x, const double y );

	static void SetOffset( const double x, const double y );
	static Vec2d <double> GetOffset();

	static Vec2d <double> PosToScreen( const Vec2d <double> pos );

private:
	friend class Map;
	friend class Player;
	friend class Tile;

	static int 		offset_x;
	static int 		offset_y;

	static double	x;
	static double 	y;

	static double 	width;
	static double 	height;
};

#endif //SCREEN_H
