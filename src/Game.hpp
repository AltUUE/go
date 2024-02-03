#ifndef _GAME_HPP
#define _GAME_HPP

#include "Move.hpp"

namespace GO{
	class Game{
		
		public:
		
		Move* root_move;
		Move* last_move;
		
		Game();
		~Game();
		
		
	};
};

#include "Game.cpp"

#endif
