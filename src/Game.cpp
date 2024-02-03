#ifndef _GAME_CPP
#define _GAME_CPP

#include <exception>

template<size_t N>
GO::Game<N>::Game(){
	if(N != 9 && N != 13 && N != 19){
		throw std::invalid_argument("Only 9x9, 13x13, and 19x19 boards are supported.");
	}
	
	root_move = new Move<N>();
	last_move = root_move;
}

template<size_t N>
GO::Game<N>::~Game(){
	delete root_move;
}

template<size_t N>
std::string GO::Game<N>::extract_moves() const {
	
	return "";
}

template<size_t N>
bool GO::Game<N>::insert_move(char x, char y){
	
	// check game mode
	
	Move<N>* mv = _make_move(x, y);
	if(mv == nullptr){
		return false;
	}
	
	last_move->next.push_back(mv);
	last_move = mv;
	
	return true;
}

template<size_t N>
GO::Move<N>* GO::Game<N>::_make_move(char x, char y){
	if(x == last_move->ko_x && y == last_move->ko_y){
		return nullptr;
	}
	if(last_move->board[x][y] != Stone::Empty){
		return nullptr;
	}
	
	Move<N>* mv = new Move<N>(x, y, last_move);
	Stone stone_color = (mv->turn ? Stone::Black : Stone::White),
		 opp_stone_color = (!mv->turn ? Stone::Black : Stone::White);
	mv->board[x][y] = stone_color;
	
	bool removed_flag = false;
	// remove dead stones
	unsigned char ix, iy;
	for(std::pair<char, char> p : _it){
		ix = x+p.first;
		iy = y+p.second;
		if(ix>=0 && ix<N && iy>=0 && iy<N && mv->board[ix][iy] == opp_stone_color){
			_reset_vis();
			_vis[ix][iy] = true;
			if(_count_libs(ix, iy, mv, opp_stone_color) == 0){
				removed_flag = true;
				if(_remove_stones(ix, iy, mv, opp_stone_color) == 1){
					if(mv->ko_x == -1){
						mv->ko_x = ix;
						mv->ko_y = iy;
					}
					else{
						mv->ko_x = -2;
						mv->ko_y = -2;
					}
				}
			}
		}
	}
	
	// if the move did not kill any stones, check for suicide
	if(removed_flag == false){
		_reset_vis();
		_vis[x][y] = true;
		if(_count_libs(x, y, mv, stone_color) == 0){
			delete mv;
			return nullptr;
		}
	}
	
	if(mv->ko_x == -2){
		mv->ko_x = -1;
		mv->ko_y = -1;
	}
	
	return mv;
}

template<size_t N>
void GO::Game<N>::_reset_vis(){
	for(size_t i=0; i<N; i++){
		for(size_t j=0; j<N; j++){
			_vis[i][j] = 0;
		}
	}
}

template<size_t N>
int GO::Game<N>::_count_libs(char x, char y, GO::Move<N>* mv, GO::Stone stone){
	int cnt = 0;
	
	unsigned char ix, iy;
	
	for(std::pair<char, char> p : _it){
		ix = x+p.first;
		iy = y+p.second;
		if(ix>=0 && ix<N && iy>=0 && iy<N && _vis[ix][iy] == false){
			_vis[ix][iy] = true;
			if(mv->board[ix][iy] == Stone::Empty){
				cnt++;
			}
			else if(mv->board[ix][iy] == stone){
				cnt += _count_libs(ix, iy, mv, stone);
			}
		}
	}
	
	return cnt;
}

template<size_t N>
int GO::Game<N>::_remove_stones(char x, char y, GO::Move<N>* mv, GO::Stone stone){
	mv->board[x][y] = Stone::Empty;
	int cnt = 1;
	
	unsigned char ix, iy;
	for(std::pair<char, char> p : _it){
		ix = x+p.first;
		iy = y+p.second;
		if(ix>=0 && ix<N && iy>=0 && iy<N && mv->board[ix][iy] == stone){
			cnt += _remove_stones(ix, iy, mv, stone);
		}
	}
	
	return cnt;
}

#endif
