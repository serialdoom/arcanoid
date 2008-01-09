/* TerrainBuilder.h */
#ifndef __TERRAINBUILDER_H__
#define __TERRAINBUILDER_H__

#include "CollisionChecker.h"
#include "Point.h"
#include "Brick.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

class TerrainBuilder {
private:
	CollisionChecker *cc; // Holds the Collision checker in order to be able to register items in him.
	void Register(Sprite *toreg);
	int getNumber(char *buffer, const char *pattern);

public:
	TerrainBuilder(CollisionChecker *_cc);
	bool Load(char *filename);
	void ToRemove(void);
};


#endif