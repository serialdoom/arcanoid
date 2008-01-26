/*
 * author: koutsop
 */

#include <cassert>
#include <iostream>

#include "Board.h"


#define BOARD_SPEED	2


Board::Board(int start_x, 
			 int start_y, 
			 AnimationFilm *af,
			 int numPlayer) : 	startY(start_y),
								Sprite(start_x, start_y, af)
{	
	assert( numPlayer == 1 || numPlayer == 2);
	SetVisibility(true);
	
	if( numPlayer == 1){
		player1 = true;
		player2 = false;
	}
	else{
		player1 = false;
		player2 = true;
	}
}
/////////////////////////////////////////////////////////////////////



void Board::Move(const int dx, const int dy){

	if( player1 ){
		if( StateHolder::stateKey.Key_Left ){
			SetPointUpLeft(GetPointUpLeft().GetX() - BOARD_SPEED, startY);
			SetPointDownRight(GetPointDownRight().GetX() - BOARD_SPEED, GetPointDownRight().GetY());
		}
		else if( StateHolder::stateKey.Key_Right ){
			SetPointUpLeft(GetPointUpLeft().GetX() + BOARD_SPEED, startY);
			SetPointDownRight(GetPointDownRight().GetX() + BOARD_SPEED, GetPointDownRight().GetY());
		}
		else if( (keyPressed.Key_Mouse_Left || keyPressed.Key_Mouse_Right)) {
			int distance = GetPointUpLeft().GetX() - GetPointDownRight().GetX();
			SetPointUpLeft(dx, startY);
			SetPointDownRight(dx+distance, GetPointDownRight().GetY());
		}
	}//if
	
	else if( player2 ){
		if( StateHolder::stateKey.Key_A){
			SetPointUpLeft(GetPointUpLeft().GetX() - BOARD_SPEED, startY);
			SetPointDownRight(GetPointDownRight().GetX() - BOARD_SPEED, GetPointDownRight().GetY());
		}

		else if( StateHolder::stateKey.Key_D){
			SetPointUpLeft(GetPointUpLeft().GetX() + BOARD_SPEED, startY);
			SetPointDownRight(GetPointDownRight().GetX() + BOARD_SPEED, GetPointDownRight().GetY());
		}

	}//else if
	else { assert(0); }
	return;
}


/*
void Board::Move(const int dx, const int dy){
	if( StateHolder::GetKey() == Key_Left )
		SetPointUpLeft(GetPointUpLeft().GetX() - 1, startY);

	else if( StateHolder::GetKey() == Key_Right )
		SetPointUpLeft(GetPointUpLeft().GetX() + 1, startY);

	else if( StateHolder::GetKey() == Key_Mouse_Left )
		SetPointUpLeft(dx, startY);

	else if( StateHolder::GetKey() == Key_Mouse_Right )
		SetPointUpLeft(dx, startY);

	return;
}
*/