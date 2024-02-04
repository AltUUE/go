#include <iostream>

#include "Game.hpp"

int main(){
	int N;
	std::cin >> N;
	GO::Game g(N);
	g.mode = GO::GameMode::Analysis;
	
	int in1, in2;
	
	while(1){
		system("clear");
		for(int j=N-1; j>=0; j--){
			for(int i=0; i<N; i++){
				std::cout << int(g.last_move->board[i][j]) << ' ';
			}
			std::cout << '\n';
		}
		
		std::cin >> in1 >> in2;
		
		if(in1 == -1){
			break;
		}
		
		if(in1 == -2){
			g.last_move = g.last_move->prev;
		}
		
		g.insert_move(in1, in2);
	}
	
	return 0;
}
