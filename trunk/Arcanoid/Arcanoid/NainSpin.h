#ifndef NAINSPIN_H
#define NAINSPIN_H

#include "Sprite.h"
#include "AnimationFilm.h"

class NainSpin : public Sprite {
	int speed;

public:

	int GetSpeed(void) const { return speed; }
	void SetSpeed(int newSpeed) { speed = newSpeed; }
	virtual void Collide(Sprite *s){}
	
	/* @target: Einai h Move gia to ekatos8e sprite
	 */
	virtual void Move(const int dx, const int dy);

	NainSpin(Point point, AnimationFilm* film);
	NainSpin(int x, int y, AnimationFilm* film);
	~NainSpin(void){}
};

#endif
