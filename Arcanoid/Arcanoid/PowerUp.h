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


#define MAX_POWER 17

class PowerUp {
private:
	string NamePowerUp[MAX_POWER];
	const char *AppendIntegerToString( string str, int i);

public:

	PowerUp(AnimationFilmHolder *ah, SpriteHolder *sp, const char *configFileName);

	~PowerUp(void);

	void ApplyBonus(string gift);
	


};







