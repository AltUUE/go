#ifndef _MOVE_CPP
#define _MOVE_CPP

template<size_t N>
GO::Move<N>::Move(){
	play_x = -1;
	play_y = -1;
	ko_x = -1;
	ko_y = -1;
	prev = nullptr;
	turn = 0;
}

template<size_t N>
GO::Move<N>::Move(char x, char y, GO::Move<N>* p){
	play_x = x;
	play_y = y;
	ko_x = -1;
	ko_y = -1;
	prev = p;
	board = p->board;
	turn = !p->turn;
}

template<size_t N>
GO::Move<N>::~Move(){
	for(Move* mv : next){
		delete mv;
	}
}

#endif
