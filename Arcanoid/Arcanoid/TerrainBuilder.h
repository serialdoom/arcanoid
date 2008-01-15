/* TerrainBuilder.h */
#ifndef __TERRAINBUILDER_H__
#define __TERRAINBUILDER_H__

#include <fstream>
#include <cstring>
#include <cstdlib>


#include "CollisionChecker.h"
#include "SpriteHolder.h"
#include "Point.h"
#include "Brick.h"
#include "KeyLogger.h"
#include "AnimationFilmHolder.h"

class TerrainBuilder {
private:
	CollisionChecker *cc; // Holds the Collision checker in order to be able to register items in him.
	SpriteHolder *sp;
	AnimationFilmHolder *afm;

	void Register(Sprite *toreg);
	int getNumber(char *buffer, const char *pattern);
	const char *AppendIntegerToString( std::string str, int i);

public:
	TerrainBuilder(CollisionChecker *_cc, SpriteHolder *_sp, AnimationFilmHolder *_afm);
	bool Load(const char *config_filename, const char *brick_id);
};


#endif