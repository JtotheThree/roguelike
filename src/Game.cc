#include <SDL.h>
#include <iostream>
#include "Game.h"

#include "Graphics.h"
#include "Timer.h"
#include "Input.h"
#include "Player.h"
#include "Map.h"
#include "Random.h"
#include "Screen.h"
#include "Vec2d.h"

const int 	k_fps{ 60 };
const auto 	k_max_frame_time = std::chrono::milliseconds{ 5 * 1000 / 60 };

int 		Game::k_resolution_width( 800 );
int 		Game::k_resolution_height( 600 );

//
// Game - Constructor
//
Game::Game() :
	sdl_engine(),
	graphics(),
	random{ new Random(  ) },
	player{ new Player( graphics, Vec2d <double> { 
			Game::k_resolution_width / 2.0,
			Game::k_resolution_height / 2.0 } ) },
	map{ new Map( graphics ) }
{
	Vec2d <int> entrance = map->GetEntrancePosition();
	Vec2d <double> pos = { 0, 0 };
	pos.x = units::TileToPos( entrance.x );
	pos.y = units::TileToPos( entrance.y );

	std::cout << "Entrance X: " << entrance.x << std::endl;
	std::cout << "Entrance Y: " << entrance.y << std::endl;

	std::cout << "Player X: " << pos.x << std::endl;
	std::cout << "Player Y: " << pos.y << std::endl;

	player->SetPosition( pos );
	Screen::CenterScreen( pos.x, pos. y );

	EventLoop();
}

//
// Game - Destructor
//
Game::~Game() {
}

void Game::EventLoop() {
	Input input;
	SDL_Event event;

	bool running( true );

	auto last_updated_time = std::chrono::high_resolution_clock::now();

	while (running) {
		using std::chrono::high_resolution_clock;
		using std::chrono::milliseconds;
		using std::chrono::duration_cast;

		const auto start_time = high_resolution_clock::now();

		bool left, right, up, down;
		left = false;
		right = false;
		up = false;
		down = false;

		input.BeginNewFrame();

		while (SDL_PollEvent( &event )) {
			switch (event.type) {
				case SDL_KEYDOWN:
					input.KeyDownEvent( event );
					break;
				case SDL_KEYUP:
					input.KeyUpEvent( event );
					break;
				default:
					break;
			}
		}

		if (input.WasKeyPressed( SDL_SCANCODE_Q )) {
			running = false;
		}

		if (input.IsKeyHeld( SDL_SCANCODE_A )) {
			left = true;
		}
		if (input.IsKeyHeld( SDL_SCANCODE_D )) {
			right = true;
		} 
		if (input.IsKeyHeld( SDL_SCANCODE_W )) {
			up = true;
		}
		if (input.IsKeyHeld( SDL_SCANCODE_S )) {
			down = true;
		}
		
		player->Move( left, right, up, down );

		const auto current_time = high_resolution_clock::now();
		const auto upd_elapsed_time = current_time - last_updated_time;

		Update( graphics, std::min( duration_cast <milliseconds>( upd_elapsed_time ), k_max_frame_time ) );
		Render( graphics );

		const auto end_time = high_resolution_clock::now();
		const auto elapsed_time = duration_cast <milliseconds>( end_time - start_time );

		const auto delay_duration = milliseconds( 1000 ) / k_fps - elapsed_time;
		if ( delay_duration.count() >= 0 ) {
			SDL_Delay( delay_duration.count() );
		}

		//const double fps = 1000.0 / (elapsedTime + delayDuration).count();
		//std::cout << "FPS: " << std::to_string( fps ) << std::endl;
	}
}

void Game::Update( Graphics &graphics, const std::chrono::milliseconds elapsed_time  ) {
	Timer::UpdateAll( elapsed_time );

	map->Update( graphics, elapsed_time );
	player->Update( *map, elapsed_time );
}

void Game::Render( Graphics &graphics ) const {
	graphics.Clear();

	map->Render( graphics );
	player->Render( graphics );

	graphics.Flip();
}
