#ifndef __POWERUPSPR_H__
#define __POWERUPSPR_H__

#include "Sprite.h"
#include "AnimationFilm.h"
#include "Point.h"

class PowerUpSpr: public Sprite{
private:
	int i;
public:
	PowerUpSpr(Point point, AnimationFilm* film);
	virtual void Collide(Sprite *s);

	void Move(const int x, const int y);
	~PowerUpSpr();
};


#endif