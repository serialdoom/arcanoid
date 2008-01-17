/* Header file of the Game. */

#ifndef GAME_H
#define GAME_H


#include <allegro.h>
#include <string>

#include "KeyLogger.h"
#include "TerrainBuilder.h"
#include "CollisionChecker.h"
#include "StateHolder.h"
#include "SpriteHolder.h"
#include "LoadFilmsInfo.h"
#include "LoadFilmsInfo.h"
#include "AnimationFilmHolder.h"
#include "Ball.h"
#include "Board.h"
#include "Wall.h"

class Game {
private:
	CollisionChecker *cc;
	TerrainBuilder *tbuilder;
	SpriteHolder *sp;
	LoadFilmsInfo *filmsInfo;
	BitmapLoader *bitmaps;
	AnimationFilmHolder *afh;

public:
	Game();
};

#endif