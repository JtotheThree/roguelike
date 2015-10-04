#ifndef __SDLENGINE_H__
#define __SDLENGINE_H__

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdexcept>

class SDLEngine {
public:
	SDLEngine() {
		if ( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
			std::cout << SDL_GetError() << std::endl;
			throw std::runtime_error( "SDL_Init");
		}
		if ( IMG_Init( IMG_INIT_PNG ) == 0 ) {
			std::cout << IMG_GetError() << std::endl;
			throw std::runtime_error( "IMG_Init" );
		}
		//if ( SDL_ShowCursor ( SDL_DISABLE ) < 0 )
		//	throw std::runtime_error( "SDL_ShowCursor" );
	}

	~SDLEngine() {
		SDL_Quit();
	}
};

#endif //__SDLENGINE_H_
