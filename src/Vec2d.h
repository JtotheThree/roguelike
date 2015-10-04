#ifndef __VEC2D_H__
#define __VEC2D_H__

#include <cmath>

template< typename T >
struct Vec2d {
	T x;
	T y;
	Vec2d< T > operator+( const Vec2d< T >& rhs) const {
		return Vec2d( x + rhs.x, y + rhs.y );
	}
};

#endif //__VEC2D_H__
