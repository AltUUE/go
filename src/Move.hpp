#ifndef _MOVE_HPP
#define _MOVE_HPP

#include <vector>
#include <array>

namespace GO{
	enum class Stone : char {
		Empty, Black, White
	};
	
	template<size_t N>
	class Move{
		
		public:
		
		char play_x, play_y;
		char ko_x, ko_y;
		std::array<std::array<Stone, N>, N> board;
		bool turn; // 0 -> white played last
		
		Move* prev;
		std::vector<Move*> next;
		
		Move();
		Move(char x, char y, Move* p);
		~Move();
	};
};

#include "Move.cpp"

#endif
