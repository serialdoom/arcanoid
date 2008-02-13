#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Sprite.h"
#include "AnimationFilm.h"
class Explosion : public Sprite {

public:
	virtual void Collide(Sprite *s){}
	/* @target: Einai h Move gia to ekatos8e sprite
	 */
	virtual void Move(const int dx, const int dy){}

	Explosion(Point point, AnimationFilm* film);
	Explosion(int x, int y, AnimationFilm* film);
	~Explosion(void){}
};

#endif
