#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "units.h"

struct Rectangle {
	Rectangle( double x, double y, double width, double height ) :
		x( x ),
		y( y ),
		width( width ),
		height( height )
	{}

	double GetLeft() const { return x; }
	double GetRight() const { return x + width; }
	double GetUp() const { return y; }
	double GetDown() const { return y + height; }

	double GetWidth() const { return width; }
	double GetHeight() const { return height; }

	bool CollidesWith( const Rectangle &rhs ) const {
		return GetRight() >= rhs.GetLeft() &&
			GetLeft() <= rhs.GetRight() &&
			GetUp() <= rhs.GetDown() &&
			GetDown() >= rhs.GetUp();
	}

private:
	const double x;
	const double y;
	const double width;
	const double height;
};

#endif //RECTANGLE_H
