#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <chrono>
#include "Rectangle.h"
#include "units.h"
#include "Vec2d.h"

class Graphics;
class Map;

class Player {
public:
	Player( Graphics& graphics, Vec2d <double> pos);
	~Player();

	void Update( const Map& map, const std::chrono::milliseconds elapsed_time );
	void Render( Graphics& graphics ) const;

	void Move( bool left, bool right, bool up, bool down );
	void SetPosition( const Vec2d <double> pos );
	Vec2d <double>  GetPos() const;
private:
	const Rectangle LeftCollision( double delta ) const;
	const Rectangle RightCollision( double delta ) const;
	const Rectangle UpCollision( double delta ) const;
	const Rectangle DownCollision( double delta ) const;

	void UpdateX( const Map& map, const std::chrono::milliseconds elapsed_time );
	void UpdateY( const Map& map, const std::chrono::milliseconds elapsed_time );

	Vec2d <double> pos;
	Vec2d <double> velocity;

	int accel_dir_x;
	int accel_dir_y;

	const SDL_Color foreground_color = { 255, 125, 255, 255 };
	const uint8_t character = 1;//'@';
};

#endif //__PLAYER_H__
