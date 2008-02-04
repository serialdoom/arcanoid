/*
 * author: koutsop
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <string>


#include "Sprite.h"
#include "InputManager.h"
#include "StateHolder.h"
#include "AnimationFilm.h"
#include "KeyLogger.h"

class Board: public Sprite {
private:
	KEY			keyPressed;
	Point		oldPosition;
	bool		player1, player2;
	char		boardSpeed;
	const int	startY;

	int GetKeyboardCoordinates(void);
	int GetMouseCoordinates(int dx);

public:
	void SetKey(KEY &_key) { keyPressed = _key; }
	void Move(const int dx, const int dy);

	char GetBoardSpaed(void) const { return boardSpeed; }
	void SetBoardSpeed(char speed) { boardSpeed = speed; }
	
	/*
	 * apix nomizw oti einai perito to id edw. Esti kai alios 8a ta filaei ola 
	 * o spriteHolder pou 8a ta filaei se ena map me id, sprite
	 */
	Board(int start_x, int start_y, AnimationFilm *af, char playerNo);
	virtual void Collide(Sprite *s);
	~Board(){} 
};


#endif