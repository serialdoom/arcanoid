#ifndef __GAME_H__
#define __GAME_H__

#include "allegro.h"
#include "ball.h"
#include "board.h"


class Game {

private:
	Ball *the_ball;
	Board *the_board;
	BITMAP *background;
	BITMAP *buffy;

public:
	Game(int hasGraphics);
	void play(void);
	~Game(void);
};

#endif