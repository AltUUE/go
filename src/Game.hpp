#ifndef _GAME_HPP
#define _GAME_HPP

#include <string>
#include "Move.hpp"

namespace GO{
	enum class GameMode : char {
		Editor, Play, Analysis, Spectate
	};
	
	template<size_t N>
	class Game{
		
		public:
		
		GameMode mode;
		Move<N>* root_move;
		Move<N>* last_move;
		
		Game();
		~Game();
		
		std::string extract_moves() const;
		bool insert_move(char x, char y);
		
		private:
		
		static constexpr std::pair<char, char> _it[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
		
		std::array<std::array<bool, N>, N> _vis;
		void _reset_vis();
		
		Move<N>* _make_move(char x, char y);
		int _count_libs(char x, char y, Move<N>* mv, Stone stone);
		int _remove_stones(char x, char y, Move<N>* mv, Stone stone);
	};
};

#include "Game.cpp"

#endif
