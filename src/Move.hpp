#ifndef _MOVE_HPP
#define _MOVE_HPP

#include <vector>

namespace GO{
	class Move{
		
		public:
		
		char play_x, play_y;
		char ko_x, ko_y;
		
		Move* prev;
		std::vector<Move*> next;
		
		Move();
		Move(char x, char y);
		~Move();
	};
};

#include "Move.cpp"

#endif
