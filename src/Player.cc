#include <cassert>
#include <iostream>
#include "Screen.h"
#include "Map.h"
#include "Graphics.h"
#include "Player.h"


const units::Acceleration 	k_acceleration( 0.00012 ); //0.000083997812 );
const units::Acceleration 	k_friction( 0.000016 );
const units::Velocity 		k_max_speed( 0.03089375 );

const Rectangle 			k_collision{ 1, 0, 15, 11 };

struct CollisionInfo {
	bool 		collided;
	int 	row;
	int 	col;
};

CollisionInfo GetWallCollisionInfo( const Map& map, const Rectangle& rect ) {
	CollisionInfo info{ false, 0, 0 };
	std::vector <Map::CollisionTile> tiles( map.GetCollidingTiles( rect ) );

	for ( auto &tile : tiles ) {
		if ( tile.blocked ) {
			info = { false, tile.row, tile.col };
			break;
		}
	}
	
	return info;
}


Player::Player( Graphics &graphics, Vec2d <double> pos ) : 
	pos( std::move( pos ) ),
	velocity{ 0.0, 0.0 }
{
	Move( false, false, false, false );
}

Player::~Player() {
}

void Player::Update( const Map& map, const std::chrono::milliseconds elapsed_time ) {
	UpdateX( map, elapsed_time );
	UpdateY( map, elapsed_time );
}

void Player::Render( Graphics &graphics ) const {
	Vec2d <double> offset = { 0, 0 };

	offset = Screen::PosToScreen( pos );

	graphics.RenderChar( character, offset.x, offset.y, foreground_color );
}

void Player::Move( bool left, bool right, bool up, bool down ) {
	if ( !left && !right ) {
		accel_dir_x = 0;
	} else if ( left && !right ) {
		accel_dir_x = -1;
	} else if ( !left && right ) {
		accel_dir_x = 1;
	} else if ( left && right ) {
		accel_dir_x  = 0;
	}

	if ( !up && !down ) {
		accel_dir_y = 0;
	} else if ( up && !down ) {
		accel_dir_y = -1;
	} else if ( !up && down ) {
		accel_dir_y = 1;
	} else if ( up && down ) {
		accel_dir_y = 0;
	}
}

void Player::SetPosition( const Vec2d <double> newPos ) {
	pos = newPos;
}

//COLLSION
const Rectangle Player::LeftCollision( double delta) const {
	assert( delta <= 0 && "Wrong delta value" );
	return Rectangle(
			pos.x + k_collision.GetLeft() + delta,
			pos.y + k_collision.GetUp(),
			k_collision.GetWidth() / 2.0 - delta,
			k_collision.GetHeight()
	);
}

const Rectangle Player::RightCollision( double delta ) const {
	assert( delta >= 0 && "Wrong delta value" );
	return Rectangle {
			pos.x + k_collision.GetLeft() + k_collision.GetWidth() / 2,
			pos.y + k_collision.GetUp(),
			k_collision.GetWidth() / 2 + delta,
			k_collision.GetHeight()
	};
}

const Rectangle Player::UpCollision( double delta ) const {
	assert( delta <= 0 && "Wrong delta value" );
	return Rectangle {
			pos.x + k_collision.GetLeft(),
			pos.y + k_collision.GetUp() + delta,
			k_collision.GetWidth(),
			k_collision.GetHeight() / 2 - delta
	};
}

const Rectangle Player::DownCollision( double delta ) const {
	assert( delta >= 0 && "Wrong delta value" );
	return Rectangle { 
			pos.x + k_collision.GetLeft(),
			pos.y + k_collision.GetUp() + k_collision.GetHeight() / 2,
			k_collision.GetWidth(),
			k_collision.GetDown() + delta 
	};
}

void Player::UpdateX( const Map& map, const std::chrono::milliseconds elapsed_time ) {
	units::Acceleration accel_x{ 0.0 };

	if ( accel_dir_x < 0 ) {
		accel_x = -k_acceleration;
	} else if ( accel_dir_x > 0 ) {
		accel_x = k_acceleration;
	}

	velocity.x += accel_x * elapsed_time.count();

	if ( accel_dir_x < 0 ) {
		velocity.x = std::max( velocity.x, -k_max_speed );
	} else if ( accel_dir_x > 0 ) {
		velocity.x = std::min( velocity.x, k_max_speed );
	} else {
		velocity.x = velocity.x > 0.0 
			? std::max( 0.0, velocity.x - k_friction * elapsed_time.count() )
			: std::min( 0.0, velocity.x + k_friction * elapsed_time.count() );
	}

	const double delta = velocity.x * elapsed_time.count();

	if ( delta > 0.0 ) {
		CollisionInfo info = GetWallCollisionInfo( map, RightCollision( delta ) );

		if ( info.collided ) {
			//pos.x = units::TileToGame( info.col ) - kCollisionX.GetRight();
			velocity.x = 0.0;
		} else {
			pos.x += delta;
			Screen::SetOffset( delta, 0.0 );
		}

		//info = GetWallCollisionInfo( map, LeftCollision( 0 ) );
		//if ( info.collided ) {
		//	pos.x = units::TileToGame( info.col ) + kCollisionX.GetRight();
		//}
	} else {
		CollisionInfo info = GetWallCollisionInfo( map, LeftCollision( delta ) );
		if ( info.collided ) {
			//pos.x = units::TileToGame( info.col ) + kCollisionX.GetRight();
			velocity.x = 0.0;
		} else {
			pos.x += delta;
			Screen::SetOffset( delta, 0.0 );
		}

		//info = GetWallCollisionInfo( map, RightCollision( 0 ) );
		//if ( info.collided ) {
		//	pos.x = units::TileToGame( info.col ) - kCollisionX.GetRight();
		//}
	}
}

void Player::UpdateY( const Map& map, const std::chrono::milliseconds elapsed_time ) {
	units::Acceleration accel_y{ 0.0 };

	if ( accel_dir_y < 0 ) {
		accel_y = -k_acceleration;
	} else if ( accel_dir_y > 0 ) {
		accel_y = k_acceleration;
	}

	velocity.y += accel_y * elapsed_time.count();

	if ( accel_dir_y < 0 ) {
		velocity.y = std::max( velocity.y, -k_max_speed );
	} else if ( accel_dir_y > 0 ) {
		velocity.y = std::min( velocity.y, k_max_speed );
	} else {
		velocity.y = velocity.y > 0.0
			? std::max( 0.0, velocity.y - k_friction * elapsed_time.count() )
			: std::min( 0.0, velocity.y + k_friction * elapsed_time.count() );
	}

	const double delta = velocity.y * elapsed_time.count();

	if ( delta > 0.0 ) {
		CollisionInfo info = GetWallCollisionInfo( map, DownCollision( delta ) );

		if ( info.collided ) {
			//pos.y = units::TileToGame( info.col ) - kCollisionX.GetDown();
			velocity.y = 0.0;
		} else {
			pos.y += delta;
			Screen::SetOffset( 0.0, delta );
		}

		//info = GetWallCollisionInfo( map, UpCollision( 0 ) );
		//if ( info.collided ) {
		//	pos.y = units::TileToGame( info.col ) + kCollisionX.GetDown();
		//}
	} else {
		CollisionInfo info = GetWallCollisionInfo( map, UpCollision( delta ) );
		
		if( info.collided ) { 
			//pos.y = units::TileToGame( info.col ) + kCollisionX.GetDown();
			velocity.y = 0.0;
		} else {
			pos.y += delta;
			Screen::SetOffset( 0.0, delta );
		}

		//info = GetWallCollisionInfo( map, UpCollision( 0 ) );
		//if ( info.collided ) {
		//	pos.y = units::TileToGame( info.col ) - kCollisionX.GetDown();
		//}
	}
}
