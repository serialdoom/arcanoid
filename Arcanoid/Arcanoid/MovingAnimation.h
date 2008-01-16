/*
 * author: koutsop
 */

/*
Orizei mia metakinish me sugkekrimeno (dx, dy), ka8ws kai daley
meta apo thn parodo tou opoiou h kinhsh 8a efarmostei.
*/
#ifndef MOVINGANIMATION_H
#define MOVINGANIMATION_H

#include "Animation.h"

class MovingAnimation : public Animation {
private:
	bool		continuous;
	delay_t		delay;
	offset_t	dx, dy;

public:
    offset_t	GetDx(void)		const { return dx; }
	offset_t  	GetDy(void)		const { return dy; }
	delay_t   	GetDelay(void)	const { return delay; }
	bool		GetContinuous(void) const { return continuous; }

    void	    SetDx (offset_t v) { dx = v; }
    void	    SetDy (offset_t v) { dy = v; }
    void	    SetDelay (delay_t v) { delay = v; }
    void	 	SetContinuous (bool v) { continuous = v; }

    virtual Animation*	Clone (animid_t newId) const;
    
	//cunstractor
	MovingAnimation (
	offset_t _dx, offset_t _dy, delay_t _delay, bool c, animid_t _id
    ): dx(_dx), dy(_dy), delay(_delay), continuous(c), Animation(_id){}
	
	//destructor
	virtual ~MovingAnimation(void) {}
};

#endif