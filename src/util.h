#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <SDL.h>

namespace util {
	inline std::string GetResourcePath( const std::string &sub_dir = "" ) {
#ifdef _WIN32
		const char PATH_SEP = '\\';
#else
		const char PATH_SEP = '/';
#endif
	
		static std::string base_res;

		if ( base_res.empty() ) {
			char *base_path = SDL_GetBasePath();
			if ( base_path ) {
				base_res = base_path;
				SDL_free( base_path );
			} else {
				std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
				return "";
			}

			size_t pos = base_res.rfind( "bin" );
			base_res = base_res.substr( 0, pos );
		}

		return sub_dir.empty() ? base_res : base_res + sub_dir + PATH_SEP;
	}
};

#endif //UTILIT_H
