#ifndef _GAME_HPP
#define _GAME_HPP

#include <string>
#include "Move.hpp"

namespace GO{
	class Game{
		
		public:
		
		Move* root_move;
		Move* last_move;
		
		Game();
		~Game();
		
		std::string extract_moves() const;
		
	};
};

#include "Game.cpp"

#endif
