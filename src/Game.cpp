#ifndef _GAME_CPP
#define _GAME_CPP

GO::Game::Game(){
	root_move = new Move();
	last_move = root_move;
}

GO::Game::~Game(){
	delete root_move;
}

#endif
