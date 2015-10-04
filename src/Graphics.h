#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <SDL.h>
#include <string>
#include "units.h"

class Graphics {
public:
	Graphics();
	~Graphics();

	Graphics( const Graphics& ) = delete;
	Graphics& operator= ( const Graphics& ) = delete;

	SDL_Texture* LoadImage( const std::string &filename, const bool is_black_transparent );
	
	void SetColor( SDL_Texture *tex, const SDL_Color color );
	
	void RenderChar( const uint8_t &character, const int x, const int y, SDL_Color color );
	void RenderText( const std::string &text, const int x, const int y, SDL_Color color );

	void RenderTexture( SDL_Texture *tex,
			const SDL_Rect dest, 
			const SDL_Rect *clip = nullptr ) const;
	void RenderTexture( SDL_Texture *tex, 
			const int x, 
			const int y, 
			const SDL_Rect *clip = nullptr ) const;

	void RenderFillRect( const SDL_Rect rect, const SDL_Color color );

	void Flip() const;
	void Clear() const;
private:
	SDL_Window 		*sdl_window;
	SDL_Renderer 	*sdl_renderer;

	SDL_Texture		*font;
};

#endif //__GRAPHICS_H__
