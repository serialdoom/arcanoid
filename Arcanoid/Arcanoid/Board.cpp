/*
 * author: koutsop
 */

#include <cassert>

#include "Board.h"

#define BOARD_SPEED	2


Board::Board(int start_x, 
			 int start_y, 
			 AnimationFilm *af,
			 char playerNo) : 	startY(start_y),
								Sprite(start_x, start_y, af)
{	
	assert( playerNo == 1 || playerNo == 2);
	spriteType = SPRITE_BOARD;
	SetVisibility(true);
	
	if( playerNo == 1){
		player1 = true;
		player2 = false;
	}
	else{
		player1 = false;
		player2 = true;
	}
}
/////////////////////////////////////////////////////////////////////



void Board::Collide(Sprite *s){
	if(s->GetType() == SPRITE_WALL)
		SetPosition(oldPosition);
	return;
}
/////////////////////////////////////////////////////////////////////



void Board::Move(const int dx, const int dy){
	//Save the old possitions.
	oldPosition = GetPosition();

	if( player1 ){
		if( StateHolder::stateKey.Key_Left )
			SetPosition(GetPosition().GetX() - BOARD_SPEED, startY);
		else if( StateHolder::stateKey.Key_Right )
			SetPosition(GetPosition().GetX() + BOARD_SPEED, startY);
		else if( (keyPressed.Key_Mouse_Left || keyPressed.Key_Mouse_Right)) 
			SetPosition(dx, startY);
	}//if
	
	else if( player2 ){
		if( StateHolder::stateKey.Key_A)
			SetPosition(GetPosition().GetX() - BOARD_SPEED, startY);
		else if( StateHolder::stateKey.Key_D)
			SetPosition(GetPosition().GetX() + BOARD_SPEED, startY);
	}//else if
	else { assert(0); }
	return;
}
