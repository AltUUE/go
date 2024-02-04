#include "Client.hpp"
#include <iostream>

void fatal_error(const std::string& errorString){
	std::cout << errorString << std::endl;
	std::cout << "press enter to quit...";
	SDL_Quit();
	std::cin.get();
	exit(1);
}

GO::Client::Client(){
	_window = nullptr;
    _renderer = nullptr;
    _board = nullptr;

    _initialize();
    _loop();
}

GO::Client::~Client(){
	
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

    // SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    // SDL_RenderClear(_renderer);
    // SDL_RenderPresent(_renderer);

    // SDL_RenderClear(_renderer);
    // SDL_Rect dstrect;
    // dstrect.x = 100;
    // dstrect.y = 100;
    // dstrect.w = 98;
    // dstrect.h = 106;
    // SDL_RenderCopy(_renderer, _board, NULL, &dstrect);
    // SDL_RenderPresent(_renderer);
}

void GO::Client::_loop(){
    _loop_on = true;
    Uint64 start, end;
	float elapsed, delta;
	while(_loop_on){
		start = SDL_GetPerformanceCounter();

        _process_events();

		end = SDL_GetPerformanceCounter();
		elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
		delta = 6.6f - elapsed * 1000.0f;
		if(delta > 0) SDL_Delay(delta);
	}
}

void GO::Client::_process_events(){
    SDL_Event evt;
    if(SDL_PollEvent(&evt)){
        if(evt.type == SDL_QUIT)
            _loop_on = false;
    }
}

void GO::Client::_new_game(size_t n){
	
}
