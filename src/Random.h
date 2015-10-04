#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>
#include "units.h"
#include "Vec2d.h"

class Random {
public:
	Random();
	Random( uint64_t random_seed );

	~Random();

	static int 		Int( int min, int max );
	static float 	Float( float min, float max );
	static double 	Double( double min, double max );

	static Vec2d <float> PointInCircle( float radius );

	static std::mt19937_64	random_engine;
private:
	uint64_t 				random_seed;
	std::random_device 		seed_generator;
};

#endif //__RANDOM_H__
