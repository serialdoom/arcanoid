#ifndef POWERUP_H
#define POWERUP_H


#include <vector>
#include <string>
#include <allegro.h>


#include "Ball.h"
#include "Point.h"
#include "Board.h"
#include "Animator.h"
#include "SpriteHolder.h"
#include "AnimationHolder.h"
#include "AnimationFilmHolder.h"



#define MAX_POWER 16

typedef enum powerups_t { 
	MAX			= 0,	
	MIN			= 1,
	STIC		= 2,
	LIFE_UP		= 3,
	CLONE_BALL	= 4,
	SPEED_UP	= 5,
	SPEED_DOWN	= 6,
	DESTRUCTION	= 7,
	EXPLOSION	= 8,
	BUCKLER		= 9,
	BAD			= 10,
	MONEY		= 11,
	BOMB		= 12,
	BANANA		= 13,
	FIRE		= 14,
	MONEY_X2	= 15,
	NONE		= 16
}powerups_t;

typedef std::vector< std::pair<powerups_t, Point> > powerUpVector;

class PowerUp {

private:
	powerUpVector	powersToExecute;
	AnimatorMap		powerupAnimator;
	string			NamePowerUp[MAX_POWER];
	const char *AppendIntegerToString( string str, int i);


public:

	PowerUp(AnimationHolder *ah, 
		    AnimationFilmHolder *afh, 
			SpriteHolder *sp,
			animid_t &countAnimationID);

	~PowerUp(void);

	void ApplyBonus(powerups_t gift);
	
	
	void SpeedUp(Ball *ball);
	void SpeedDown( Ball *ball);
	void Money(int &score, int level);
	void LifeUp(int &lifes);
	void Max(Board* board);
	void Min(Board* board);


	void AddPowerToExecute( std::pair<powerups_t, Point> item) { powersToExecute.push_back(item); };
	void ClearPowersToExecute(void) { powersToExecute.clear(); }
	powerUpVector *GetPowersToExecute(void) { return &powersToExecute; }

};

#endif




