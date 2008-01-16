/*
 * author: koutsop
 */

/*
Prokeite gia epilogh opoiondhpote frames apo ena animation film ta opoia 8a
apotupw8oun me th seira pou emfanizontai se auth th lista (kai oxi sto idio to film)
*/
#ifndef FRAMELISTANIMATION_H
#define FRAMELISTANIMATION_H

#include <list>
#include "MovingAnimation.h"


typedef unsigned char frame_t;

class FrameListAnimation : public MovingAnimation {

private:
    std::list<frame_t> frames;

public:
    const std::list<frame_t>& GetFrames (void) const { return frames; }
    
	void SetFrames (const std::list<frame_t>& f);

    virtual Animation* Clone (animid_t newId) const;

    FrameListAnimation (
		const std::list<frame_t>& _frames, 
		offset_t dx, offset_t dy, delay_t d, bool c, animid_t id
    ): frames(_frames), MovingAnimation(dx, dy, d, c, id){}
};

#endif
