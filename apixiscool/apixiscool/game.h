#ifndef __GAME_H__
#define __GAME_H__

//Start of arcanoid incudes
#include "KeyLogger.h"
#include "allegro.h"

//Various includes TODO: elliminate all of them.
#include "ball.h"
#include "board.h"


class Game {

private:
	Ball *the_ball;
	Board *the_board;
	BITMAP *background;
	BITMAP *buffy;

public:
	Game(void);
	bool Init(char *config_file);
	void play(void);
	~Game(void);
};

#endif