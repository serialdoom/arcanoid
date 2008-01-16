/*
 * author: koutsop
 */
/*
Orizei mia kinish h opoia kurios prosdiorizetai apo thn allhlouxia frames, eidikotera
meta3u enos arxikou kai enos telikou frame
*/
#ifndef FRAMERANGEANIMATION_H
#define FRAMERANGEANIMATION_H

#include "Animation.h"
#include "MovingAnimation.h"

typedef unsigned char frame_t;

class FrameRangeAnimation : public MovingAnimation {
private:
	frame_t start, end;

public:
	frame_t	GetEndFrame (void)		const { return end; }
    frame_t	GetStartFrame (void)	const { return start; }

	void	SetEndFrame (frame_t v) { end = v; }
    void	SetStartFrame (frame_t v) { start = v; }
    

    Animation* Clone (animid_t newId) const;

    FrameRangeAnimation (
        frame_t s, frame_t e, 
        offset_t dx, offset_t dy, delay_t d, bool c, animid_t id
    ): start(s), end(e), MovingAnimation(dx, dy, d, c, id){}
	
	~FrameRangeAnimation(void){}
};

#endif