#include <stdexcept>
#include "Game.hpp"

GO::Game::Game(size_t n){
	N = n;
	if(N != 9 && N != 13 && N != 19){
		throw std::invalid_argument("Only 9x9, 13x13, and 19x19 boards are supported.");
	}
	
	root_move = new Move();
	last_move = root_move;
}

GO::Game::~Game(){
	delete root_move;
}

std::string GO::Game::extract_moves() const {
	
	// TODO
	return "";
}

bool GO::Game::insert_move(char x, char y){
	if(mode == GameMode::Analysis || (mode == GameMode::Play && last_move->next.size() == 0)){
		Move* mv;
		if(x == -1){
			// -1 is the code for pass
			if(last_move->play_x == -1){
				// terminate_game();
			}
			mv = new Move(-1, -1, last_move);
		}
		else{
			// create move object with new board
			mv = _make_move(x, y);
			if(mv == nullptr){
				return false;
			}
		}
		
		last_move->next.push_back(mv);
		last_move = mv;
		
		return true;
	}
	return false;
}

size_t GO::Game::boardSize() const {
	return N;
}

GO::Move* GO::Game::_make_move(char x, char y){
	if(x == last_move->ko_x && y == last_move->ko_y){
		return nullptr;
	}
	if(last_move->board[x][y] != Stone::Empty){
		return nullptr;
	}
	
	Move* mv = new Move(x, y, last_move);
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

void GO::Game::_reset_vis(){
	for(size_t i=0; i<N; i++){
		for(size_t j=0; j<N; j++){
			_vis[i][j] = 0;
		}
	}
}

int GO::Game::_count_libs(char x, char y, GO::Move* mv, GO::Stone stone_color){
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
			else if(mv->board[ix][iy] == stone_color){
				cnt += _count_libs(ix, iy, mv, stone_color);
			}
		}
	}
	
	return cnt;
}

int GO::Game::_remove_stones(char x, char y, GO::Move* mv, GO::Stone stone_color){
	mv->board[x][y] = Stone::Empty;
	int cnt = 1;
	
	unsigned char ix, iy;
	for(std::pair<char, char> p : _it){
		ix = x+p.first;
		iy = y+p.second;
		if(ix>=0 && ix<N && iy>=0 && iy<N && mv->board[ix][iy] == stone_color){
			cnt += _remove_stones(ix, iy, mv, stone_color);
		}
	}
	
	return cnt;
}
