/*
 * author: koutsop
 */
#include "FrameRangeAnimation.h"

Animation* FrameRangeAnimation::Clone (animid_t newId) const {
    return new FrameRangeAnimation( start, end, 
									GetDx(), GetDy(), 
									GetDelay(), GetContinuous(), newId
								  );
}