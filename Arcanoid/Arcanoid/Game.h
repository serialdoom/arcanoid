/*
 * author: koutsop
 */


#ifndef GAME_H
#define GAME_H


#include <allegro.h>
#include <string>


#include "Wall.h"
#include "Ball.h"
#include "Point.h"
#include "Board.h"
#include "Animator.h"
#include "KeyLogger.h"
#include "StateHolder.h"
#include "SpriteHolder.h"
#include "BitmapLoader.h"
#include "InputManager.h"
#include "LoadFilmsInfo.h"
#include "LoadFilmsInfo.h"
#include "TerrainBuilder.h"
#include "AnimatorHolder.h"
#include "MovingAnimator.h"
#include "MovingAnimation.h"
#include "AnimationHolder.h"
#include "CollisionChecker.h"
#include "AnimationFilmHolder.h"


class Game {
private:
	unsigned long		currTime;
	int					levelsNo;
	int					currLevel;
	string				levelPath;
	Wall *				twelve;
	Wall *				three;
	Wall *				six;
	Wall *				nine;
	BitmapLoader *		bitmaps;
	SpriteHolder *		spriteH;
	InputManager *		inputManager;
	LoadFilmsInfo *		filmsInfo;
	TerrainBuilder *	terrainB;
	AnimationHolder *	animationH;
	CollisionChecker *	collisionC;
	AnimationFilmHolder*animationFH;

	void LoadLevelsInfo(void);
	void LoadingTerrain(int levelNo);
	void InitiallizingFilmsInfo(void);
	void InitiallizingBitmapLoader(void);
	void InitiallizingAnimationFilmHolder(void);

	Wall * CreatingTwelveWall(void);
	Wall * CreatingThreeWall(void);
	Wall * CreatingSixWall(void);
	Wall * CreatingNineWall(void);

	void GameLoop(BITMAP *baground, BITMAP *buffer);
	void DisplayALL(BITMAP *baground, BITMAP *buffer);

public:
	
	void PlayGame(void);
	
	void SetGameTime(void){ currTime = time((time_t *)0); }

	unsigned long GetGameTime(void) const { return currTime; }
	
	Game();
	
	~Game();
};

#endif