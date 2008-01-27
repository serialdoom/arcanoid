/*
 * author: koutsop
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "KeyLogger.h"
#include "Sprite.h"
#include "StateHolder.h"
#include "AnimationFilm.h"

class Board: public Sprite {
private:
	bool player1, player2;
	KEY keyPressed;
	const int startY;
	Point uperOld;
	Point downOld;

public:

	void SetKey(KEY &_key) { keyPressed = _key; }
	void Move(const int dx, const int dy);
	
	/*
	 * apix nomizw oti einai perito to id edw. Esti kai alios 8a ta filaei ola 
	 * o spriteHolder pou 8a ta filaei se ena map me id, sprite
	 */
	Board(int start_x, int start_y, AnimationFilm *af, int numPlayer);
	virtual void Collide(Sprite *s);
	~Board(){} 
};


#endif