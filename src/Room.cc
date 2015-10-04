#include "Room.h"

Room::Room() {
	main_room = false;
}

Room::Room( Vec2d <int> start, Vec2d <int> end ) : start( start ), end ( end ) {
}

Vec2d <int> Room::GetCenter() {
	Vec2d <int> center;

	center.x = start.x + ( end.x / 2 );
	center.y = start.y + ( end.y / 2 );

	return center;
}
