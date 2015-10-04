#include <stdexcept>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"
#include "Game.h"
#include "util.h"

Graphics::Graphics() :
	sdl_window{ SDL_CreateWindow(
				"RogueLike",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				Game::k_resolution_width, 
				Game::k_resolution_height,
				SDL_WINDOW_RESIZABLE
				)},
	sdl_renderer{ SDL_CreateRenderer(
			sdl_window,
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)}
{
	if ( sdl_window == nullptr )
		throw std::runtime_error( "SDL_CreateWindow" );
	if ( sdl_renderer == nullptr )
		throw std::runtime_error( "SDL_CreateRenderer" );

	SDL_RenderSetLogicalSize( sdl_renderer, Game::k_resolution_width, Game::k_resolution_height);

	font = LoadImage( "Cheepicus_16x16.png", false );
}

Graphics::~Graphics() {
	SDL_DestroyRenderer( sdl_renderer );
	SDL_DestroyWindow( sdl_window );
}

SDL_Texture* Graphics::LoadImage( const std::string &filename, const bool is_black_transparent ) {
	const std::string filepath = util::GetResourcePath( "res" ) + filename;

	SDL_Texture *tex;

	if ( is_black_transparent ) {
		SDL_Surface *surf = IMG_Load( filepath.c_str() );
		if( surf == nullptr )
		{
			std::cout << IMG_GetError() << " " << SDL_GetError() << std::endl;
			throw std::runtime_error( "LoadImage: Unable To Load Surface" );
		}
		const Uint32 black_color = SDL_MapRGB( surf->format, 0, 0, 0 );
		SDL_SetColorKey( surf, SDL_TRUE, black_color );
		tex = SDL_CreateTextureFromSurface( sdl_renderer, surf );
	} else {
		SDL_Surface *surf = IMG_Load( filepath.c_str() );
		if ( surf == nullptr )
			throw std::runtime_error( "LoadImage" );
		tex = SDL_CreateTextureFromSurface( sdl_renderer, surf );
	}

	if ( tex == nullptr )
		throw std::runtime_error( "LoadImage" );
	
	return tex;

}

void Graphics::RenderChar( const uint8_t &character, const int x, const int y, SDL_Color color ) {
	SDL_Rect dst;
	SDL_Rect clip;

	int char_y = character / 16;
	char_y = char_y * 16;
	int char_x = character % 16;
	char_x = char_x * 16;

	dst.x = x;
	dst.y = y;
	dst.w = 16;
	dst.h = 16;

	clip.x = char_x;
	clip.y = char_y;
	clip.w = dst.w;
	clip.h = dst.h;

	SetColor( font, color );
	RenderTexture( font, dst, &clip );
}

void Graphics::RenderText( const std::string &text, const int x, const int y, SDL_Color color ) {
}

void Graphics::SetColor( SDL_Texture *tex, const SDL_Color color ) {
	SDL_SetTextureColorMod( tex, color.r, color.g, color.b );
	SDL_SetTextureAlphaMod( tex, color.a );
}

void Graphics::RenderTexture( 
		SDL_Texture *tex, 
		const SDL_Rect dest, 
		const SDL_Rect *clip ) const 
{
	SDL_RenderCopy( sdl_renderer, tex, clip, &dest );
}

void Graphics::RenderTexture( SDL_Texture *tex, const int x, const int y, 
		const SDL_Rect *clip) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	if ( clip != nullptr ) {
		dest.w = clip->w;
		dest.h = clip->h;
	} else {
		SDL_QueryTexture( tex, nullptr, nullptr, &dest.w, &dest.h );
	}
	RenderTexture( tex, dest, clip );
}

void Graphics::RenderFillRect( const SDL_Rect rect, const SDL_Color color ) {
	SDL_SetRenderDrawColor( sdl_renderer, color.r, color.g, color.b, color.a );
	SDL_RenderFillRect( sdl_renderer, &rect );
}

void Graphics::Flip() const {
	SDL_RenderPresent( sdl_renderer );
}

void Graphics::Clear() const {
	SDL_SetRenderDrawColor( sdl_renderer, 0, 0, 0, 255 );
	SDL_RenderClear( sdl_renderer );
}

