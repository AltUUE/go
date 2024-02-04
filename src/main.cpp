#include <iostream>

#include "Game.hpp"

int main(){
	GO::Game<9> g;
	g.mode = GO::GameMode::Analysis;
	
	int in1, in2;
	
	while(1){
		std::cin >> in1 >> in2;
		
		if(in1 == -1){
			break;
		}
		
		if(in1 == -2){
			g.last_move = g.last_move->prev;
		}
		
		g.insert_move(in1, in2);
		
		system("clear");
		for(int j=8; j>=0; j--){
			for(int i=0; i<9; i++){
				std::cout << int(g.last_move->board[i][j]) << ' ';
			}
			std::cout << '\n';
		}
	}
	
	return 0;
}
