#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <chrono>
#include <map>
#include <memory>
#include <vector>

#include "Room.h"
#include "Tile.h"
#include "units.h"
#include "Vec2d.h"

class Graphics;
class Rectangle;

class Map {
public:
	Map( Graphics& graphics );
	~Map();
	
	struct CollisionTile {
		CollisionTile( int row, int col, TileType tile_type, bool blocked ) :
			row( row ),
			col( col ),
			tile_type( tile_type ),
			blocked( blocked )
		{}

		int 	row;
		int 	col;
		TileType	tile_type;
		bool 		blocked;
	};

	bool seperated;

	void RelativeNeighborhoodGraph();
	bool RoomOverlap( Room a, Room b );
	Vec2d <int> ComputeSeperation( Room agent );
	void GenerateMap( int num_cols, int num_rows, int num_rooms  );

	const std::vector <CollisionTile> GetCollidingTiles( const Rectangle& rect ) const;

	void Update( Graphics& graphics, std::chrono::milliseconds elapsed_time );
	void Render( Graphics& graphics ) const;

	Vec2d <int> GetEntrancePosition();

private:
	void FillInWalls();

	void DigRooms();
	void CreateHorizTunnel( int x1, int x2, int row );
	void CreateVertTunnel( int y1, int y2, int col );

	int num_rows;
	int num_cols;

	std::vector <std::vector <Tile>> 		tiles;
	std::vector <Room>						rooms;
	std::map <int, std::vector <Room>> 		graph;
	Vec2d <int> 							entrance_pos;

	Graphics 	*graphics;
};
#endif //MAP_H
