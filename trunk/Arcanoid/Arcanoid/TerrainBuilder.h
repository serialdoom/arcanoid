/* TerrainBuilder.h */
#ifndef __TERRAINBUILDER_H__
#define __TERRAINBUILDER_H__

#include "CollisionChecker.h"
#include "SpriteHolder.h"
#include "Point.h"
#include "Brick.h"
#include "KeyLogger.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

class TerrainBuilder {
private:
	CollisionChecker *cc; // Holds the Collision checker in order to be able to register items in him.
	SpriteHolder *sp;
	void Register(Sprite *toreg);
	int getNumber(char *buffer, const char *pattern);
	const char *AppendIntegerToString( std::string str, int i);

public:
	TerrainBuilder(CollisionChecker *_cc, SpriteHolder *_sp);
	bool Load(const char *filename);
};


#endif