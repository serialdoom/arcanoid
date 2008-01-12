/* Header file of the Game. */

#include "KeyLogger.h"
#include "TerrainBuilder.h"
#include "CollisionChecker.h"
#include "StateHolder.h"
#include "SpriteHolder.h"
#include <allegro.h>

class Game {
private:
	CollisionChecker *cc;
	TerrainBuilder *tbuilder;
	SpriteHolder *sp;

public:
	Game();
};