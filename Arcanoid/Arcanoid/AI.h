/*
 *author: koutsop
 */

#ifndef AI_H
#define AI_H

#include "NainSpin.h"
#include "Brick.h"
#include "Sprite.h"
#include "SpriteHolder.h"

class AI {

private:
	class StopBricksFunctor : public std::unary_function<Animator*, void> {
	public: 
		void operator()(std::pair<string, Sprite*> p) const {
			if( dynamic_cast<Brick*>(p.second) )
				dynamic_cast<Brick*>(p.second)->SetIsRunning(false);
		}
	    StopBricksFunctor (void){}
	};
	
	class SetSpeedFunctor : public std::unary_function<Animator*, void> {
	public: 
		void operator()(std::pair<string, Sprite*> p) const {
			if( dynamic_cast<Brick*>(p.second) )
				dynamic_cast<Brick*>(p.second)->SetIsRunning(true);
		}
		SetSpeedFunctor (void) {}
	};

public:
	void AIBricks(SpriteHolder* sp);

	//precodition na exei dimiourgi8ei to terrain prwta
	void AINain(NainSpin *nain, int dx, int dy);
	AI(void){}
	~AI(void){}
};

#endif
