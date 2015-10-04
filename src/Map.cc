#include <iostream>
#include "Map.h"

#include "Game.h"
#include "Graphics.h"
#include "Tiles.h"
#include "Random.h"
#include "Rectangle.h"
#include "Screen.h"

Map::Map( Graphics& graphics ) :
	tiles(),
	rooms()
{
	GenerateMap( 400, 400, 100 );
}

Map::~Map() {}

Vec2d <int> Map::GetEntrancePosition() {
	return entrance_pos;
}

void Map::FillInWalls() {
	for ( auto row = 0u; row < tiles.size(); ++row ) {
		for ( auto col = 0u; col < tiles[ row ].size(); ++col ) {
			if ( tiles[ row ][ col ].tile_type == TileType::EARTH ) {
				if(  row > 1) {
					if ( tiles[ row - 1 ][ col ].tile_type == TileType::GROUND ) {
						tiles[ row ][ col ] = TileWall();
					}
				}
				if ( row + 1 < tiles.size() ) {
					if ( tiles[ row + 1 ][ col ].tile_type == TileType::GROUND ) {
						tiles[ row ][ col ] = TileWall();
					}
				}
				if ( col > 1 ) {
					if ( tiles[ row ][ col - 1 ].tile_type == TileType::GROUND ) {
						tiles[ row ][ col ] = TileWall();
					}
				}
				if( col + 1 < tiles[ row ].size() ) {
					if ( tiles[ row ][ col + 1 ].tile_type == TileType::GROUND ) {
						tiles[ row ][ col ] = TileWall();
					}
				}

				//DIIIAGONAAAAALS
				if ( row > 1 && col > 1 ) {
					if ( tiles[ row - 1 ][ col - 1 ].tile_type == TileType::GROUND ) {
						tiles[ row ] [ col] = TileWall();
					}
				}
				if ( row > 1 && col + 1 < tiles[ row ].size() ) {
					if ( tiles[ row - 1][ col + 1 ].tile_type == TileType::GROUND ) {
						tiles[ row ][ col ] = TileWall();
					}
				}
				if ( row + 1 < tiles.size() && col + 1 < tiles[ row ].size() ) {
					if ( tiles[ row + 1 ][ col + 1 ].tile_type == TileType::GROUND ) {
						tiles[ row ][ col ] = TileWall();
					}
				}
				if ( row + 1 < tiles.size() && col > 1 ) {
					if ( tiles[ row + 1 ][ col - 1 ].tile_type == TileType::GROUND ) {
						tiles[ row ][ col ] = TileWall();
					}
				}
			}
		}
	}
}

void Map::DigRooms() {
	int booboohole = 0;

	for ( auto room : rooms ) {
/*		std::cout << "Room #: " << booboohole << std::endl;
		std::cout << "Room Start.x: " << room.start.x << std::endl;
		std::cout << "Room End.X: " << room.end.x << std::endl;
		std::cout << "Room Start.y: " << room.start.y << std::endl;
		std::cout << "Room End.y: " << room.end.y << std::endl; */

		for ( auto row = room.start.y; row <= room.end.y; ++row ) {
			for ( auto col = room.start.x; col <= room.end.x; ++col ) {
				if ( row == room.start.y ) {
					tiles[ row ][ col ] = TileWall();
				} else if ( row == room.end.y ) {
					tiles[ row ][ col ] = TileWall();
				} else if ( col == room.start.x ) {
					tiles[ row ][ col ] = TileWall();
				} else if ( col == room.end.x ) {
					tiles[ row ][ col ] = TileWall();
				} else { 
					tiles[ row ][ col ] = TileGround();
				}
			}
		}

		booboohole++;
	}
}

void Map::CreateHorizTunnel( int x1, int x2, int row ) {
	for ( auto col = x1; col < x2; ++col ) {
		tiles[ row ][ col ] = TileGround();
	}
}

void Map::CreateVertTunnel( int y1, int y2, int col ) {
	for ( auto row = y1; row < y2; ++row ) {
		tiles[ row ][ col ] = TileGround();

		if( col + 1 <= tiles[ row ].size() ) {
			tiles[ row ][ col + 1 ] = TileGround();
		}
	}
}

void Map::RelativeNeighborhoodGraph() {
	Room a, b, c;
	double abDist, acDist, bcDist;

	bool skip;

	for ( int i = 0; i < rooms.size(); i++ ) {
		a = rooms[ i ];

		for ( int j = i+1; j < rooms.size(); j++ ) {
			skip = false;

			b = rooms[ j ];
			abDist = std::pow( a.GetCenter().x - b.GetCenter().x, 2 ) 
				+ std::pow( a.GetCenter().y - b.GetCenter().y, 2 );

			for ( int k = 0; k < rooms.size(); k++ ) {
				if ( rooms[ k ].id == rooms[ i ].id || rooms[ k ].id == rooms[ j ].id ) 
					continue;
				
				c = rooms[ k ];

				acDist = std::pow( a.GetCenter().x - c.GetCenter().x, 2 )
					+ std::pow( a.GetCenter().y - c.GetCenter().y, 2 );
				bcDist = std::pow( b.GetCenter().x - c.GetCenter().x, 2 )
					+ std::pow( b.GetCenter().y - c.GetCenter().y, 2 );
				
				if ( acDist < abDist && bcDist < abDist )
					skip = true;

				if ( skip )
					break;

				if ( !skip ) {
					//if ( graph[ a.id ] == NULL ) 
					//	graph[ a.id ].push_back( new std::vector<Room> );
					std::cout << "Strange sauce" << std::endl;
					graph[ a.id ].push_back( b );
				}
			}
		}
	}

}


bool Map::RoomOverlap( Room a, Room b ) {
	bool x_overlap = units::ValueInRange( a.start.x, b.start.x, b.end.x ) ||
					 units::ValueInRange( b.start.x, a.start.x, a.end.x );
	bool y_overlap = units::ValueInRange( a.start.y, b.start.y, b.end.y ) ||
					 units::ValueInRange( b.start.y, a.start.y, a.end.y );

	return x_overlap && y_overlap;
}

Vec2d <int> Map::ComputeSeperation( Room agent ) {
	Vec2d <double> velocity = { 0.0, 0.0 };
	Vec2d <int> move = { 0, 0 };
	Vec2d <int> agent_center = agent.GetCenter();


	for ( auto &room : rooms ) {
		if ( agent.id != room.id ) 
		{
			//std::cout << "Collided: " << RoomOverlap( agent, room ) << std::endl;

			if ( RoomOverlap( agent, room ) ) {
				seperated = false;

				Vec2d <int> room_center = room.GetCenter();
				Vec2d <int> diff = { agent_center.x - room_center.x, agent_center.y - room_center.y };

				//std::cout << "DiffX: " << diff.x << std::endl;
				//std::cout << "DiffY: " << diff.y << std::endl;

				double distance = std::sqrt( diff.x*diff.x + diff.y*diff.y );

				//std::cout << "Distance: " << distance << std::endl;

				if ( distance > 0.0f ) {
					double repel_decay_coefficient = 1.0f;
					double scale = repel_decay_coefficient / distance;

					double normal = std::sqrt( diff.x*diff.x + diff.y*diff.y );
					Vec2d <double> normalized_diff = {0,0};

					if ( normal != 0 ) {
						normalized_diff.x = diff.x / normal;
						normalized_diff.y = diff.y / normal;
					}

					//std::cout << "Normalized DistanceX: " << normalized_diff.x << std::endl;
					//std::cout << "Normalized DistanceY: " << normalized_diff.y << std::endl;

					normalized_diff.x *= scale;
					normalized_diff.y *= scale;

					//std::cout << "Scaled DistanceX: " << normalized_diff.x << std::endl;
					//std::cout << "Scaled DIstanceY: " << normalized_diff.y << std::endl;

					velocity.x += normalized_diff.x;
					velocity.y += normalized_diff.y;

					//std::cout << "velocity.x: " << velocity.x << std::endl;
					//std::cout << "velocity.y: " << velocity.y << std::endl;
				}

			}
		}
	}

	//double length = std::sqrt( velocity.x*velocity.x + velocity.y*velocity.y );

	//if ( length > 0.0 ) {
	//	seperated = false;

		//std::cout << "SHIIIT: " << (int)(velocity.x * 100.0) << std::endl;
	velocity.x *= 20.0;
	velocity.y *= 20.0;
	
	//std::cout << "Velocity.X: " << velocity.x << std::endl;
	//std::cout << "Velocity.Y: " << velocity.y << std::endl;

	if ( velocity.x < 0.0 ) {
		velocity.x = std::floor( velocity.x );
	}

	if ( velocity.x > 0.0 ) {
		velocity.x = std::ceil( velocity.x );
	}

	if ( velocity.y < 0.0 ) {
		velocity.y = std::floor( velocity.y );
	}

	if ( velocity.y > 0.0 ) {
		velocity.y = std::ceil( velocity.y );
	}

	move.x = (int) velocity.x;
	move.y = (int) velocity.y;

	//std::cout << "Move.x: " << move.x << std::endl;
	//std::cout << "Move.y: " << move.y << std::endl;

	return move;
}

void Map::GenerateMap( int num_cols, int num_rows, int num_rooms ) {
	using std::vector;

	this->num_cols = num_cols;
	this->num_rows = num_rows;

	tiles = vector <vector <Tile>>(
			num_rows, vector< Tile > (
				num_cols, Tile() ) );

	rooms = vector <Room>( num_rooms, Room() );

	for ( auto row = 0u; row < tiles.size(); ++row ) {
		for ( auto col = 0u; col < tiles[ row ].size(); ++col ) {
			tiles[ row ][ col ] = TileEarth();
		}
	}

	int room_number = 0;

	for ( auto &room : rooms ) {
		int center_col = num_cols / 2;
		int center_row = num_rows / 2;
		float radius = num_rows / 16;
		Vec2d <float> pos;

		pos = Random::PointInCircle( radius );
		
		pos.x = center_col - pos.x;
		pos.y = center_row - pos.y;


		int col_start = (int) pos.x;
		int row_start = (int) pos.y;
		int col_end;
		int row_end;

		if( Random::Int( 1, 10 ) < 8 ) {
			col_end = col_start + Random::Int( Room::k_min_room_size, Room::k_max_room_size );
			row_end = row_start + Random::Int( Room::k_min_room_size, Room::k_max_room_size );
		} else {
			room.main_room = true;
			col_end = col_start + Random::Int( Room::k_min_room_size * 2, Room::k_max_room_size * 2 );
			row_end = row_start + Random::Int( Room::k_min_room_size * 2, Room::k_max_room_size * 2 );
		}


		int width = col_end - col_start;
		int height = row_end - row_start;

		if ( width <= ( height / 2 ) ) {
			col_end = col_end + Random::Int( Room::k_min_room_size / 4, Room::k_max_room_size / 4 );
		} else if ( height <= ( width / 2 ) ) {
			row_end = row_end + Random::Int( Room::k_min_room_size / 4, Room::k_max_room_size / 4 );
		}

		room = Room( { col_start, row_start }, { col_end, row_end } );

		if (room_number == 0) {
			entrance_pos.x = Random::Int( col_start + 1, col_end - 1 );
			entrance_pos.y = Random::Int( row_start + 1, row_end - 1 );
		}

		room.id = room_number;

		room_number++;

	}

	seperated = false;

	while ( !seperated ) {
		seperated = true;

		for ( auto &room : rooms ) {
			Vec2d <int> movement = { 0, 0 };
			movement = ComputeSeperation( room );
			//std::cout << "MovementX: " << movement.x << std::endl;
			//std::cout << "MovementY: " << movement.y << std::endl;
			room.start.x += movement.x;
			room.end.x += movement.x;
			room.start.y += movement.y;
			room.end.y += movement.y;
		}
	}

	std::cout << "Rooms.size(): " << rooms.size() << std::endl;

	//Delete rooms that have gone out of bounds
	/*for ( uint32_t i = 0; i < rooms.size(); i++ ) {
		if ( rooms[i].start.x < 0 ) {
			rooms.erase( rooms.begin() + i );
		}

		if ( rooms[i].start.y < 0 ) {
			rooms.erase( rooms.begin() + i );
		}

		if ( rooms[i].end.x >= ( num_cols - 1 ) ) {
			rooms.erase( rooms.begin() + i );
		}

		if ( rooms[i].end.y >= ( num_rows - 1 ) ) {
			rooms.erase( rooms.begin() + i );
		}
	}*/

	for ( uint32_t i = 0; i < rooms.size(); i++ ) {
		if (rooms[i].start.x < 0 || rooms[i].start.y < 0 ||
			rooms[i].end.x >= num_cols - 1 || rooms[i].end.y >= num_rows - 1 ) {
			//std::cout << "Deleting room: " << rooms[i].id << std::endl;
			//rooms.erase( rooms.begin() + i );
			
			if ( i != rooms.size() - 1 )
				rooms[i] = std::move( rooms.back() );
			rooms.pop_back();
		} 	
	}

	std::cout << "Rooms.size(): " << rooms.size() << std::endl;

/*	for ( int i = 0; i < 2; i++ ) {

		for ( auto &room : rooms ) {
			//std::cout << "Room ID: " << room.id << std::endl;
			ComputeSeperation( &room );
		}

		for ( auto &room : rooms ) {
			room.desired.x += room.direction.x;
			room.desired.y += room.direction.y;
		}
	}

	for ( auto &room : rooms ) { 
		std::cout << "start.x: " << room.start.x << std::endl;
		std::cout << "start.y: " << room.start.y << std::endl;
		std::cout << "desired.x: " << room.desired.x << std::endl;
		std::cout << "desired.y: " << room.desired.y << std::endl;
		room.start.x = room.desired.x;
		room.start.y = room.desired.y;
	} */

	/*for ( auto &room : rooms ) {
		int row_start = Random::Int( 4, num_rows - Room::k_max_room_size - 4 );
		int row_end = row_start + Random::Int( Room::k_min_room_size, Room::k_max_room_size );
		int col_start = Random::Int( 4, num_cols - Room::k_max_room_size - 4 );
		int col_end = col_start + Random::Int( Room::k_min_room_size, Room::k_max_room_size );
		
		if (room_number == 0) {
			entrance_pos.x = Random::Int( col_start + 1, col_end - 1 );
			entrance_pos.y = Random::Int( row_start + 1, row_end - 1 );
		}


		int center_x = num_cols / 2;
		int center_y = num_rows / 2;
		float radius = num_rows / 8;

		penis = Random::PointInCircle( radius );

		penis.x = center_x - penis.x;
		penis.y = center_y - penis.y;
		
		room = Room( { (int)penis.x, (int)penis.y }, { col_end, row_end } );

		std::cout << "PointInCircle| x:" << penis.x << " y: " << penis.y << std::endl;

		room_number++;
	}*/

	RelativeNeighborhoodGraph();

	//CreateHorizTunnel( 25, 55, 23 );
	//CreateVertTunnel( 23, 40, 40 );


	DigRooms();

	//FillInWalls();

	tiles[ entrance_pos.y ][ entrance_pos.x ] = TileEntrance();
}

const std::vector< Map::CollisionTile >
Map::GetCollidingTiles( const Rectangle& rect ) const {
	const int firstRow = units::PosToTile( rect.GetUp() );
	const int lastRow = units::PosToTile( rect.GetDown() );
	const int firstCol = units::PosToTile( rect.GetLeft() );
	const int lastCol = units::PosToTile( rect.GetRight() );

	std::vector< CollisionTile > collisionTiles;

	for ( auto row = firstRow; row <= lastRow; ++row ) {
		for ( auto col = firstCol; col <= lastCol; ++col ) {
			collisionTiles.push_back( CollisionTile{ row, col, 
					tiles[ row ][ col ].tile_type, 
					tiles[ row ][ col ].blocked } );
		}
	}

	return collisionTiles;
}

void Map::Update( Graphics &graphics, std::chrono::milliseconds elapsed_time ) {
	/*for ( auto row = 0u; row < tiles.size(); ++row ) {
		for ( auto col = 0u; col < tiles[ row ].size(); ++col ) {
			tiles[ row ][ col ].Update( graphics, elapsed_time );
		}
	}*/
}

void Map::Render( Graphics &graphics ) const {

	int start_row = 0;
	int end_row = units::PosToTile( Screen::height );

	int start_col = 0; 
	int end_col = units::PosToTile( Screen::width );

	if ( Screen::y >= units::k_tile_size ) {
		start_row = units::PosToTile( Screen::y ) - 1;
	} 

	if ( Screen::x >= units::k_tile_size ) {
		start_col = units::PosToTile( Screen::x ) - 1;
	} 

	if ( end_col > num_cols ) {
		end_col = num_cols;
	}

	if (end_row > num_rows) {
		end_row = num_rows;
	}

	for (auto row = start_row; row < end_row; ++row) {
		for( auto col = start_col; col < end_col; ++col) {
			Vec2d <double> pos {
				units::TileToPos( col ),
				units::TileToPos( row )
			};

			tiles[ row ][ col ].Render( graphics, pos.x - Screen::x, pos.y - Screen::y );
		}
	}
}
