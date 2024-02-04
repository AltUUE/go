#ifndef _MOVE_CPP
#define _MOVE_CPP

GO::Move::Move(){
	play_x = -1;
	play_y = -1;
	ko_x = -1;
	ko_y = -1;
	prev = nullptr;
	turn = 0;
}

GO::Move::Move(char x, char y, GO::Move* p){
	play_x = x;
	play_y = y;
	ko_x = -1;
	ko_y = -1;
	prev = p;
	board = p->board;
	turn = !p->turn;
}

GO::Move::~Move(){
	for(Move* mv : next){
		delete mv;
	}
}

#endif
