/*
 * author: koutsop
 */

#include "Board.h"
#include "StateHolder.h"
#include <iostream>

Board::Board(int start_x, int start_y, 
			 AnimationFilm *af, 
			 const char *id) : 	startY(start_y),
								Sprite(start_x, start_y, af){}




void Board::Move(const int dx, const int dy){
	if( StateHolder::GetKey() == Key_Left )
		SetPointUpLeft(GetPointUpLeft().GetX() - 1, startY);

	else if( StateHolder::GetKey() == Key_Right )
		SetPointUpLeft(GetPointUpLeft().GetX() + 1, startY);
	return;
}
