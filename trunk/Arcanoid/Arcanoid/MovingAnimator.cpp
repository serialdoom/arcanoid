/*
 *author: koutsop
 */
//TODO Na elen3w thn move sto sprite giati den uparxei
#include "MovingAnimator.h"


void MovingAnimator::Progress (timestamp_t currTime) {
	if (currTime - lastTime >= anim->GetDelay()) {
//TODO Problhma otan bazoume kai thn else mesa giati????
		sprite->Move(anim->GetDx(), anim->GetDy());
		lastTime += anim->GetDelay();
		if (!anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
		}
		//else {
			//lastTime += anim->GetDelay();
			//Progress(currTime);  // Recursion (make loop)
		//}
	}
	return;
}
/////////////////////////////////////////////////////////////////////



void MovingAnimator::Start(Sprite* s, MovingAnimation* a, timestamp_t t) {
	sprite		= s;
	anim 		= a;
	lastTime 	= t;
	state 		= ANIMATOR_RUNNING;
}
