/*
 * author: koutsop
 */

#ifndef TERRAIN_H
#define TERRAIN_H

#include <allegro.h>
#include <string>

#include "Point.h"
#include "Animator.h"
#include "SpriteHolder.h"
#include "TerrainBuilder.h"
#include "AnimationHolder.h"
#include "CollisionChecker.h"
#include "AnimationFilmHolder.h"





class Terrain{
private:
	int			levelsNo;
	string		cfg, levelPath;
	AnimatorMap	bricksAnimator;
	TerrainBuilder *	terrainB;

	void LoadingLevelsInfo(void);
	void LoadingTerrainInfo(void);

public:
	static int		width;
	static int		height;	
	static Point	coordinates;

	int LoadingTerrain(int countAnimationID, int levelNo);
	void DisplayTerrain(BITMAP *bitmap, SpriteHolder* sh);

	int GetLevelsNo(void) const { return levelsNo; }

	Terrain(string _cfg, 
			AnimationFilmHolder * afh, 
			CollisionChecker * cc, 
			AnimationHolder * ah,
			SpriteHolder * sh);
	~Terrain(void);
};

#endif
