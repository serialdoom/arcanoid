#ifndef __POWERUPSPR_H__
#define __POWERUPSPR_H__

#include "Sprite.h"
#include "AnimationFilm.h"
#include "Point.h"

class PowerUpSpr: public Sprite{
private:
	int kind;
public:
	PowerUpSpr(Point point, AnimationFilm* film);
	virtual void Collide(Sprite *s);


	int GetBonusType(void) const	{ return kind; };
	void SetBonusType(int _kind)	{ kind = _kind; }

	void Move(const int x, const int y);
	~PowerUpSpr();
};


#endif