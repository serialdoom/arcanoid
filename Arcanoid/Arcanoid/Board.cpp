/*
 * author: koutsop
 */

#include <cassert>


#include "Board.h"
#include "Terrain.h"

#define BOARD_SPEED 4

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
	boardSpeed = BOARD_SPEED;
}
/////////////////////////////////////////////////////////////////////



void Board::Collide(Sprite *s){
	return;
}
/////////////////////////////////////////////////////////////////////



int Board::GetKeyboardCoordinates(void){
	int x		= Terrain::coordinates.GetX();
	int w		= Terrain::width;
	int dx		= GetPosition().GetX();

	if( StateHolder::IsGoLeft() ){		//aristero collision
		if( (dx - boardSpeed) < x )	{ return x; }
		else						{ return dx - boardSpeed; }
	}
	else if(StateHolder::IsGoRight()){	//de3i collision
		if ( (dx + boardSpeed) > (x + w) - GetWidth())	{ return (x + w) - GetWidth(); }
		else											{ return dx + boardSpeed; }
	}
	else
		assert(0);
	return 0;
}
/////////////////////////////////////////////////////////////////////



int Board::GetMouseCoordinates(int dx){
	int x		= Terrain::coordinates.GetX();
	int w		= Terrain::width;

	if( dx < x ) { return x; }									//aristero collision
	else if ( dx > (x + w) - GetWidth()) { return (x + w) - GetWidth(); } //de3i collision
	else { return dx; }
}
/////////////////////////////////////////////////////////////////////



void Board::Move(const int dx, const int dy){
	//Save the old possitions.
	oldPosition = GetPosition();
	
	
	if( player1 ){
		if( StateHolder::IsGoLeft() || StateHolder::IsGoRight())
			SetPosition(GetKeyboardCoordinates(), startY);
		else if( (keyPressed.Key_Mouse_Left || keyPressed.Key_Mouse_Right))
			SetPosition(GetMouseCoordinates(dx), startY);
	}//if
	
	/*
	if( player1 ){
		if( StateHolder::stateKey.Key_Left )
			SetPosition(GetKeyboardCoordinates(), startY);
		else if( StateHolder::stateKey.Key_Right )
			SetPosition(GetKeyboardCoordinates(), startY);
		else if( (keyPressed.Key_Mouse_Left || keyPressed.Key_Mouse_Right))
			SetPosition(GetMouseCoordinates(dx), startY);
	}//if
	*/
/*
//ton player 2 mporw na ton balw mesa ston stateHolder na mou leei
//auto poios paixths einai ka8e fora :D
	else if( player2 ){ 
		if( StateHolder::stateKey.Key_A)
			SetPosition(GetPosition().GetX() - BOARD_SPEED, startY);
		else if( StateHolder::stateKey.Key_D)
			SetPosition(GetPosition().GetX() + BOARD_SPEED, startY);
	}//else if
*/
	else { assert(0); }
	return;
}
