#include "Screen.h"
#include "Game.h"
#include "units.h"

double Screen::x = 0;
double Screen::y = 0;
double Screen::width = Game::k_resolution_width;
double Screen::height = Game::k_resolution_height;

int Screen::offset_x = 0;
int Screen::offset_y = 0;

Screen::Screen() {}
Screen::~Screen() {}

void Screen::CenterScreen( const double x, const double y ) {
	Screen::x = x - Game::k_resolution_width / 2.0;
	Screen::y = y - Game::k_resolution_height / 2.0;
	Screen::width = x + Game::k_resolution_width;
	Screen::height = y + Game::k_resolution_height;
}

void Screen::SetOffset( const double x, const double y ) {
	Screen::x += x;
	Screen::y += y;
	Screen::width += x;
	Screen::height += y;
}

Vec2d <double> Screen::GetOffset() {
	Vec2d <double> offset = { (double) offset_x, (double) offset_y };
	return offset;
}

Vec2d <double> Screen::PosToScreen( const Vec2d <double> pos ) {
	Vec2d <double> offset = { 0, 0 };

	offset.x = pos.x - Screen::x;
	offset.y = pos.y - Screen::y;

	return offset;
}

/*void Camera::UpdatePlayerPosition( const int x, const int y ) {
	Camera::x = x - ( units::ColToPixel( Game::kScreenWidth / 2.0 ) );
	Camera::y = y - ( units::RowToPixel( Game::kScreenHeight / 2.0 ) );

	Camera::width = Camera::x + units::ColToPixel( Game::kScreenWidth );
	Camera::height = Camera::y + units::RowToPixel( Game::kScreenHeight );
}*/


// GAME SCREEN DIMENSIONS TO ACTUAL RESOLUTION
// GET RID OF FUCKING UNITS
