#ifndef __ROOM_H__
#define __ROOM_H__

#include <stdint.h> 
#include "Vec2d.h"

struct Room {
	Room();
	Room( Vec2d <int> start, Vec2d <int> end );

	Vec2d <int>	 GetCenter();

	Vec2d <int> 	start;
	Vec2d <int> 	end;

	int			id;
	bool		main_room;

	static const int k_max_room_size = 16;
	static const int k_min_room_size = 4;
};

#endif //__ROOM_H__
