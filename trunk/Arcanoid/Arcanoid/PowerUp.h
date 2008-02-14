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
#include "AnimatorHolder.h"
#include "AnimationHolder.h"
#include "CollisionChecker.h"
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


/*= 
{MAX, 
    MIN, 
    STIC, 
    LIFE_UP,	
    CLONE_BALL,	
    SPEED_UP, 
    SPEED_DOWN,	
    DESTRUCTION, 
    EXPLOSION,	
    BUCKLER, 
    BAD, 
    MONEY, 
    BOMB, 
    BANANA, 
    FIRE, 
    MONEY_X2, 
	NONE};	
*/
class PowerUp {

private:
	static Ball*	ball;
	static Board*	board;
	static std::vector< std::pair<powerups_t, Point> > powersToExecute;
	static AnimatorMap		powerupAnimator;
	static string			NamePowerUp[MAX_POWER];

public:
	//static int giftArray[MAX_POWER+1];
	static void Init(AnimationHolder *ah, 
			  AnimationFilmHolder *afh, 
			  SpriteHolder *sp,
  			  CollisionChecker *cc,
			  animid_t &countAnimationID,
			  Ball* _ball,
			  Board* _baord);

	static void clear(void);
	static void ApplyBonus(SpriteHolder *sp, AnimationHolder *ah);	
	static void SpeedUp(void);
	static void SpeedDown(void);
	static void Money();
	static void LifeUp();
	static void Max(void);
	static void Min(void);
	static void Bad(void);
	static void Destruction(void);
	static void Explosion(void);
	static void Banana(void);
	static void DoubleMoney(void);
	static void DesplayAll(BITMAP * bitmap,SpriteHolder *sp);
	static void AddPowerToExecute( std::pair<powerups_t, Point> item) { powersToExecute.push_back(item); };

};

#endif




