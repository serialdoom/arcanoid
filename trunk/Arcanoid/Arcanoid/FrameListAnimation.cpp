/*
 * author: koutsop
 */
#include "FrameListAnimation.h"

void FrameListAnimation::SetFrames (const std::list<frame_t>& f){ 
	frames.clear(); 
	frames = f; 
}

///////////////////////////////////////////////////////////////////////

Animation* FrameListAnimation::Clone (animid_t newId) const {
	return new FrameListAnimation(	frames, GetDx(), 
									GetDy(), GetDelay(), 
									GetContinuous(), newId
								  ); 
}