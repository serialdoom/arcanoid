/* Header file for the board */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "Sprite.h"
#include "AnimationFilm.h"

class Board: public Sprite {
private:
	//Someday, something will be in here...
public:
	Board(int start_x, int start_y, AnimationFilm *af, const char *board_string);
	~Board();
};


#endif