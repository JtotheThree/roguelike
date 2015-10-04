#ifndef UNITS_H
#define UNITS_H

#include <iostream>
#include <cmath>

namespace units {
	typedef double Degrees;
	typedef double Velocity;
	typedef double Acceleration;
	typedef double AngularVelocity;

	namespace {
		const double k_tile_size( 16.0 );
		const double k_pi( atan( 1 ) * 4 );
	}

	inline double DegreesToRadians( Degrees degrees ) {
		return degrees * k_pi / 180.0;
	}

	inline double sin( Degrees degrees ) {
		return static_cast< double >( std::sin( DegreesToRadians( degrees ) ) );
	}

	inline double cos( Degrees degrees ) {
		return static_cast< double >( std::cos( DegreesToRadians( degrees ) ) );
	}

	inline int DoubleToInt( double variable ) {
		return int( round ( variable ) );
	}

	inline double TileToPos( int tile_position ) {
		return tile_position * k_tile_size;
	}

	inline int PosToTile( double position ) {
		return int( position / k_tile_size );
	}

	inline int TileToPixel( int tile_position ) {
		return DoubleToInt( TileToPos( tile_position ) );
	}

	inline bool ValueInRange( int value, int min, int max ) {
		return ( value >= min ) && (value <= max );
	}

	//const Game kHalfTile( TileToGame(1) / 2.0 );
}

#endif //UNITS_H
