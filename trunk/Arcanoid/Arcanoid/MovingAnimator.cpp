/*
 *author: koutsop
 */
//TODO Na elen3w thn move sto sprite giati den uparxei
#include "MovingAnimator.h"


void MovingAnimator::Progress (timestamp_t currTime) {
	if (currTime - lastTime >= anim->GetDelay()) {
//TODO
//		sprite->Move(anim->GetDx(), anim->GetDy());
		if (!anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
		}
		else {
			lastTime += anim->GetDelay();
			Progress(currTime);  // Recursion (make loop)
		}
	}
	return;
}