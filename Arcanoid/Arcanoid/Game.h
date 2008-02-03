/*
 * author: koutsop
 */


#ifndef GAME_H
#define GAME_H


#include <ctime>
#include <string>
#include <allegro.h>
#include <algorithm> 


#include "Wall.h"
#include "Ball.h"
#include "Point.h"
#include "Board.h"
#include "Terrain.h"
#include "Animator.h"
#include "Animation.h"
#include "KeyLogger.h"
#include "StateHolder.h"
#include "SpriteHolder.h"
#include "BitmapLoader.h"
#include "InputManager.h"
#include "LoadFilmsInfo.h"
#include "LoadFilmsInfo.h"
#include "AnimatorHolder.h"
#include "MovingAnimator.h"
#include "MovingAnimation.h"
#include "AnimationHolder.h"
#include "CollisionChecker.h"
#include "AnimationFilmHolder.h"


class Game {
private:
	BITMAP * buffer;
	BITMAP * baground;
	Ball *				theBall;
	Board *				theBoard;
	int					currLevel;
	animid_t			countAnimationID;
	unsigned long		currTime;
	Terrain	*			terrain;
	BitmapLoader *		bitmaps;
	SpriteHolder *		spriteH;
	InputManager *		inputManager;
	LoadFilmsInfo *		filmsInfo;

	MovingAnimator *	board;
	MovingAnimator *	ball;
	MovingAnimation *	movBall;
	MovingAnimation *	movBoard;
	AnimationHolder *	animationH;
	CollisionChecker *	collisionC;
	AnimationFilmHolder*animationFH;

	void InitiallizingFilmsInfo(void);
	void InitiallizingBitmapLoader(void);
	void InitiallizingAnimationFilmHolder(void);

	Board * CreatingBoard(int playerNo);
	Ball * CreatingBall(void);

	void CreateAll(void);
	void DeleteAll(void);
	void SystemLoopDispatching(bool input);
	void CheckF1(bool input);
	void CheckBoardInput();
	void GameLoop();
	void DisplayALL();

public:
	
	void PlayGame(void);
	
	void SetGameTime(void){ currTime = time( (time_t *)0 ); }

	unsigned long GetGameTime(void) const { return currTime; }
	
	Game();
	
	~Game();
};

#endif