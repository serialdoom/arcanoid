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
	string NamePorewUp[MAX_POWER];

public:

	PowerUp(void);

	~PowerUp(void);

	ApplyBonus(string gift);
	


};







