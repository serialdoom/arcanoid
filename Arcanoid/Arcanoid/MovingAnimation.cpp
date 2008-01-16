/*
 * author: koutsop
 */
#include "MovingAnimation.h"

Animation*	MovingAnimation::Clone (animid_t newId) const{ 
	return new MovingAnimation(dx, dy, delay, continuous, newId); 
}