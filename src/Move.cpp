#ifndef _MOVE_CPP
#define _MOVE_CPP

GO::Move::Move(){
	move_number = 0;
	play_x = -1;
	play_y = -1;
	ko_x = -1;
	ko_y = -1;
	turn = 0;
	
	prev = nullptr;
}

GO::Move::Move(char x, char y, GO::Move* p){
	move_number = p->move_number+1;
	play_x = x;
	play_y = y;
	ko_x = -1;
	ko_y = -1;
	board = p->board;
	turn = !p->turn;
	
	prev = p;
}

GO::Move::~Move(){
	for(Move* mv : next){
		if(mv != nullptr){
			delete mv;
			mv = nullptr;
		}
	}
}

#endif
