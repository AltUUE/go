#include "Client.hpp"
#include <iostream>

void fatal_error(const std::string& errorString){
	std::cout << errorString << std::endl;
	std::cout << "press enter to quit...";
	SDL_Quit();
	std::cin.get();
	exit(1);
}

GO::Client::Client(size_t board_size) : _board_size(board_size), _g(board_size){
	_window = nullptr;
    _renderer = nullptr;
    _board = nullptr;

    _g.mode = GameMode::Analysis;

    _initialize();
    _loop();
}

GO::Client::~Client(){
	SDL_Quit();
}

void GO::Client::_initialize(){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    _window = SDL_CreateWindow("GO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                    _screen_width, _screen_heigth, 
                                    SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    if(_window == nullptr)
        fatal_error("SDL Window couldn't be created.");
    
    SDL_RaiseWindow(_window);

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if(_renderer == nullptr)
        fatal_error("SDL Surface couldn't be created.");

    _board = IMG_LoadTexture(_renderer, "assets/board.png");
    if(_board == nullptr)
        fatal_error("Board Texture couldn't be loaded.");
}

void GO::Client::_loop(){
    _loop_on = true;
    Uint64 start, end;
	float elapsed, delta;
	while(_loop_on){
		start = SDL_GetPerformanceCounter();

        _process_events();
        _render_board();

		end = SDL_GetPerformanceCounter();
		elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
		delta = 6.6f - elapsed * 1000.0f;
		if(delta > 0) SDL_Delay(delta);
	}
}

void GO::Client::_recalibrate(){
    int cur_width, cur_heigth;
    SDL_GetWindowSize(_window, &cur_width, &cur_heigth);

    x_factor = (double)cur_width / _screen_width;
    y_factor = (double)cur_heigth / _screen_heigth;
    x_offset = 60 * x_factor, y_offset = 60 * y_factor;
    gap_xsize = 30 * x_factor, gap_ysize = 30 * y_factor;

    stone_xsize = 25 * x_factor, stone_ysize = 25 * y_factor; 
}

void GO::Client::_render_board(){
    SDL_SetRenderDrawColor(_renderer, 190, 190, 190, 255);
    SDL_RenderClear(_renderer);

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

    _recalibrate();
    for(size_t i = 0; i < _board_size; i++){
        SDL_RenderDrawLineF(_renderer, x_offset + i * gap_xsize, y_offset, x_offset + i * gap_xsize, y_offset + (_board_size-1) * gap_ysize);
        SDL_RenderDrawLineF(_renderer, x_offset, y_offset + i * gap_ysize, x_offset + (_board_size-1) * gap_xsize, y_offset + i * gap_ysize);
    }

    SDL_FRect stone;
    for(size_t i = 0; i < _board_size; i++){
        for(size_t j = 0; j < _board_size; j++){
            if(_g.last_move->board[i][_board_size-j-1] == Stone::White){
                SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
                stone.x = x_offset + i * gap_xsize - stone_xsize / 2;
                stone.y = y_offset + j * gap_ysize - stone_ysize / 2; 
                stone.w = stone_xsize;
                stone.h = stone_ysize;
                SDL_RenderFillRectF(_renderer, &stone);
            }
            else if(_g.last_move->board[i][_board_size-j-1] == Stone::Black){
                SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
                stone.x = x_offset + i * gap_xsize - stone_xsize / 2;
                stone.y = y_offset + j * gap_ysize - stone_ysize / 2; 
                stone.w = stone_xsize;
                stone.h = stone_ysize;
                SDL_RenderFillRectF(_renderer, &stone);
            }
        }
    }

    SDL_RenderPresent(_renderer);
}

void GO::Client::_process_events(){
    SDL_Event evt;
    if(SDL_PollEvent(&evt)){
        if(evt.type == SDL_QUIT)
            _loop_on = false;

        if(evt.type == SDL_MOUSEBUTTONDOWN){
            _handle_mouse_button_down(evt);
        }
    }
}

void GO::Client::_handle_mouse_button_down(SDL_Event& evt){
    _recalibrate();
    double x_pos = evt.button.x, y_pos = evt.button.y;
    x_pos -= (x_offset - stone_xsize / 2); y_pos -= (y_offset - stone_ysize / 2);
    if(x_pos < 0 || y_pos < 0)
        return;
    int idx_x = x_pos / gap_xsize, idx_y = y_pos / gap_ysize;

    if(abs(idx_x * gap_xsize - x_pos) < stone_xsize 
        && abs(idx_y * gap_ysize - y_pos) < stone_ysize){
        _g.insert_move((int)idx_x, _board_size - (int)idx_y - 1);
    }

    // if(idx_x < 0 || idx_x > _board_size-1) 
    //     return;
    // if(idx_y < 0 || idx_y > _board_size-1)
    //     return;

    // double x_margin = idx_x - (int)idx_x;
    // double y_margin = idx_y - (int)idx_y;
    // if(x_margin < .25 || x_margin > .75)
    //     return;
    // if(y_margin < .25 || y_margin > .75)
    //     return;

}

void GO::Client::_new_game(size_t n){
	
}
