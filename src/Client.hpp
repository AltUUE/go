#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"

namespace GO{
	class Client{	
	public:	
		Client();
		~Client();
		
		void run();
		
	private:
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		SDL_Texture* _board;

		int _screen_width = 1000;
		int _screen_heigth = 600;
		bool _loop_on;

		void _process_events();
		void _initialize();
		void _loop();
		void _new_game(size_t n);
	};
};

#endif
