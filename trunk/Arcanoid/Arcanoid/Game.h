/*
 * author: koutsop
 */


#ifndef GAME_H
#define GAME_H


#include <string>
#include <allegro.h>
#include <algorithm> 


#include "Ball.h"
#include "Point.h"
#include "Board.h"
#include "MyTime.h"
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
#include "GameStats.h"

#define SCORE_MAX_DIGIT 4

class Game {
private:
	BITMAP *			buffer;
	BITMAP *			baground;
	Ball *				theBall;
	Board *				theBoard;
	int					currLevel;
	animid_t			countAnimationID;
	Terrain	*			terrain;
	BitmapLoader *		bitmaps;
	SpriteHolder *		spriteH;
	LoadFilmsInfo *		filmsInfo;
	MovingAnimator *	board;
	MovingAnimator *	ball;
	MovingAnimation *	movBall;
	MovingAnimation *	movBoard;
	AnimationHolder *	animationH;
	CollisionChecker *	collisionC;
	AnimationFilmHolder*animationFH;

	int scoreDigit[SCORE_MAX_DIGIT];
	int scoreDigitPos[2];
	int lifeDigitPos[2];
	int levelDigitPos[2];
	char *digit_string;

	void InitiallizingFilmsInfo(void);
	void InitiallizingBitmapLoader(void);

	Board * CreatingBoard(int playerNo);
	Ball * CreatingBall(void);

	void CreateAll(void);
	void DeleteAll(void);
	void SystemLoopDispatching(void);
	void CheckF1(void);
	void CheckBoardInput(void);
	void GameLoop(void);
	void DisplayALL(void);
	void DisplayScore(BITMAP *buffy);
	void DisplayLife(BITMAP *buffy);
	void DisplayLevel(BITMAP *buffy);
	void SetUpStats(void);
	void NextLevel(void);
	void ResetBall(void);
	void ResetBoard(void);

public:
	
	void PlayGame(void);
	
	Game();
	
	~Game();
};

#endif