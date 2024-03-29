#include "Client.hpp"
#include <iostream>

void GO::_make_FRect(SDL_FRect& rect, double x, double y, double w, double h){
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void fatal_error(const std::string& errorString){
	std::cout << errorString << std::endl;
	std::cout << "press enter to quit...";
	SDL_Quit();
	std::cin.get();
	exit(1);
}

GO::Client::Client(size_t board_size) : _board_size(board_size), _g(board_size){
    if(board_size == 9){
        _board_screen_ratio_w = 0.6;
        _board_screen_ratio_h = 0.6;
    }
    else if(board_size == 9){
        _board_screen_ratio_w = 0.75;
        _board_screen_ratio_h = 0.75;
    }
    else{
        _board_screen_ratio_w = 0.75;
        _board_screen_ratio_h = 0.75;
    }
    
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
    
    _board_size_px = std::min(cur_width*_board_screen_ratio_w, cur_heigth*_board_screen_ratio_h);
    _gap_size_px = _board_size_px / (_board_size-1);
    _stone_size_px = _gap_size_px * 0.8;
    x_offset = (cur_width - _board_size_px)/2;
    y_offset = (cur_heigth - _board_size_px)/2;
}

void GO::Client::_render_board(){
    SDL_SetRenderDrawColor(_renderer, 190, 190, 190, 255);
    SDL_RenderClear(_renderer);
    
    _recalibrate();
    SDL_FRect filler;
    
    SDL_SetRenderDrawColor(_renderer, 240, 190, 70, 255);
    _make_FRect(filler, x_offset-_gap_size_px, y_offset-_gap_size_px, _board_size_px+_gap_size_px*2, _board_size_px+_gap_size_px*2);
    SDL_RenderFillRectF(_renderer, &filler);
    
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    for(size_t i = 0; i < _board_size; i++){
        SDL_RenderDrawLineF(_renderer, x_offset + i * _gap_size_px, y_offset, x_offset + i * _gap_size_px, y_offset + (_board_size-1) * _gap_size_px);
        SDL_RenderDrawLineF(_renderer, x_offset, y_offset + i * _gap_size_px, x_offset + (_board_size-1) * _gap_size_px, y_offset + i * _gap_size_px);
    }
    
    for(size_t i = 0; i < _board_size; i++){
        for(size_t j = 0; j < _board_size; j++){
            if(_g.last_move->board[i][_board_size-j-1] == Stone::White){
                SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
                filler.x = x_offset + i * _gap_size_px - _stone_size_px / 2;
                filler.y = y_offset + j * _gap_size_px - _stone_size_px / 2; 
                filler.w = _stone_size_px;
                filler.h = _stone_size_px;
                SDL_RenderFillRectF(_renderer, &filler);
            }
            else if(_g.last_move->board[i][_board_size-j-1] == Stone::Black){
                SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
                filler.x = x_offset + i * _gap_size_px - _stone_size_px / 2;
                filler.y = y_offset + j * _gap_size_px - _stone_size_px / 2; 
                filler.w = _stone_size_px;
                filler.h = _stone_size_px;
                SDL_RenderFillRectF(_renderer, &filler);
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
    x_pos -= (x_offset - _stone_size_px / 2); y_pos -= (y_offset - _stone_size_px / 2);
    if(x_pos < 0 || y_pos < 0)
        return;
    int idx_x = x_pos / _gap_size_px, idx_y = y_pos / _gap_size_px;
    
    if(abs(idx_x * _gap_size_px - x_pos) < _stone_size_px 
        && abs(idx_y * _gap_size_px - y_pos) < _stone_size_px){
        _g.insert_move((int)idx_x, _board_size - (int)idx_y - 1);
    }
}

void GO::Client::_new_game(size_t n){
	
}
