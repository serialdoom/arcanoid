/*
 * author: koutsop
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "Sprite.h"
#include "AnimationFilm.h"

class Board: public Sprite {

private:
	const int startY;
public:

	void Move(const int dx, const int dy);
	
	/*
	 * apix nomizw oti einai perito to id edw. Esti kai alios 8a ta filaei ola 
	 * o spriteHolder pou 8a ta filaei se ena map me id, sprite
	 */
	Board(int start_x, int start_y, AnimationFilm *af, const char* id);
	~Board(){} 
};


#endif