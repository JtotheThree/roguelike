#ifndef __GAME_H__
#define __GAME_H__

#include <chrono>
#include <memory>

#include "Graphics.h"
#include "SDLEngine.h"

class Player;
class Map;
class Random;

class Game {
public:
	Game();
	~Game();

	static int 		k_resolution_width;
	static int 		k_resolution_height;
private:
	void EventLoop();
	void Update( Graphics &graphics, const std::chrono::milliseconds elapsed_time );
	void Render( Graphics &graphics ) const;

	const SDLEngine sdl_engine;
	Graphics 		graphics;

	std::shared_ptr <Random> 	random;
	std::shared_ptr <Player> 	player;
	std::shared_ptr <Map> 		map;
};

#endif //__GAME_H__
