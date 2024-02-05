#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"

namespace GO{
	class Client{	
	public:	
		Client(size_t board_size);
		~Client();
		
		// void run();
		
	private:
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		SDL_Texture* _board;

		size_t _board_size;
		Game _g;

		int _screen_width = 1000;
		int _screen_heigth = 750;
		bool _loop_on;
		double x_factor, y_factor;
		double x_offset, y_offset;
		double gap_xsize, gap_ysize;
		double stone_xsize, stone_ysize;

		void _recalibrate();
		void _handle_mouse_button_down(SDL_Event& evt);
		void _render_board();
		void _process_events();
		void _initialize();
		void _loop();
		void _new_game(size_t n);
	};
};

#endif
