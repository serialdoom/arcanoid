/* Header file of the Game. */

#ifndef GAME_H
#define GAME_H


#include <allegro.h>

#include "KeyLogger.h"
#include "TerrainBuilder.h"
#include "CollisionChecker.h"
#include "StateHolder.h"
#include "SpriteHolder.h"


class Game {
private:
	CollisionChecker *cc;
	TerrainBuilder *tbuilder;
	SpriteHolder *sp;

public:
	Game();
};

#endif