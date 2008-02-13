#ifndef AI_H
#define AI_H

#include "Brick.h"
#include "Sprite.h"
#include "SpriteHolder.h"

class AI {

private:
	class StopBricksFunctor : public std::unary_function<Animator*, void> {
	public: 
		void operator()(std::pair<string, Sprite*> p) const {
			if( dynamic_cast<Brick*>(p.second) )
				dynamic_cast<Brick*>(p.second)->SetSpeed(0);
		}
	    StopBricksFunctor (void){}
	};
	
	class SetSpeedFunctor : public std::unary_function<Animator*, void> {
	private:
		int speed;
	public: 
		void operator()(std::pair<string, Sprite*> p) const {
			if( dynamic_cast<Brick*>(p.second) ){
				dynamic_cast<Brick*>(p.second)->SetSpeed(speed);
			}
		}
		SetSpeedFunctor (int _speed) : speed(_speed){}
	};

public:
	void AIBricks(SpriteHolder* sp);
	void AINain();
	AI(void){}
	~AI(void){}
};

#endif
