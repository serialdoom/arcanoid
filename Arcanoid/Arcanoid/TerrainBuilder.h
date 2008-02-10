/* TerrainBuilder.h */
#ifndef __TERRAINBUILDER_H__
#define __TERRAINBUILDER_H__

#include <allegro.h>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "Point.h"
#include "Brick.h"
#include "Animator.h"
#include "Animation.h"
#include "KeyLogger.h"
#include "SpriteHolder.h"
#include "AnimatorHolder.h"
#include "MovingAnimator.h"
#include "MovingAnimation.h"
#include "AnimationHolder.h"
#include "CollisionChecker.h"
#include "AnimationFilmHolder.h"
#include "GameStats.h"


class TerrainBuilder {
private:
	SpriteHolder		*sp;
	AnimationHolder		*ah;
	CollisionChecker	*cc; // Holds the Collision checker in order to be able to register items in him.
	AnimationFilmHolder *afm;

	

	void Register(Sprite *toreg);
	int getNumber(char *buffer, const char *pattern);
	const char *AppendIntegerToString( std::string str, int i);

public:
	TerrainBuilder( CollisionChecker *_cc, 
					SpriteHolder *_sp, 
					AnimationFilmHolder *_afm, 
					AnimationHolder * _ah);
	animid_t Load(const char *filename, 
				  const char *brick_id, 
				  animid_t countAnimationID, 
				  AnimatorMap &bricksAnimator);
};


#endif