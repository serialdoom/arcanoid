/*
 *author: koutsop
 */
#ifndef MOVINGANIMATOR_H
#define MOVINGANIMATOR_H

#include "Sprite.h"
#include "Animator.h"
#include "MovingAnimation.h"

class MovingAnimator : public Animator {

private:
	Sprite*				sprite;
	MovingAnimation*	anim;

public:
	void Progress (timestamp_t currTime);

	void Start (Sprite* s, MovingAnimation* a, timestamp_t t);

	MovingAnimator (void): sprite((Sprite*) 0), anim((MovingAnimation*) 0){}
	
	~MovingAnimator(){}
};


#endif