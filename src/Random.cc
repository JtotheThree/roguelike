#include <iostream>
#include "Random.h"

std::mt19937_64 Random::random_engine = std::mt19937_64();

Random::Random() {
	random_seed = seed_generator();
	std::cout << "Seed: " + std::to_string( random_seed ) << std::endl;

	Random::random_engine = std::mt19937_64( random_seed );
}

Random::Random( uint64_t random_seed ) {
	this->random_seed = random_seed;
	Random::random_engine = std::mt19937_64( random_seed );
}

Random::~Random() {
}

int Random::Int( int min, int max ) {
	std::uniform_int_distribution <int> dist( min, max );
	return dist( Random::random_engine );
}

float Random::Float( float min, float max ) {
	std::uniform_real_distribution <float> dist( min, max );
	return dist( Random::random_engine );
}

double Random::Double( double min, double max ) {
	std::uniform_real_distribution <double> dist( min, max );
	return dist( Random::random_engine );
}

Vec2d <float> Random::PointInCircle( float radius ) {
	Vec2d <float> pos = { 0, 0 };

	float t = 2 * units::k_pi * Random::Float( 0.0f, 1.0f );
	float u = Random::Float( 0.0f, 2.0f );
	float r = 0.0f;

	if ( u > 1.0f ) {
		r = 2.0f - u;
	} else {
		r = u;
	}

	pos.x = radius * r * std::cos( t );
	pos.y = radius * r * std::sin( t );

	return pos;
}
