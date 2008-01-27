/*
 * author: koutsop
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <cassert>
#include <allegro.h>		//Eidea den exw giati xriazete ala stamata na peta la8oi h allgero

#include "Point.h"
#include "Oblong.h"
#include "AnimationFilm.h"


class Sprite : public Oblong {
private:
	char			frameNo;
    bool			isVisible;
    AnimationFilm*	currFilm;

public:	
	char GetFrame(void) const { return frameNo; }

	bool IsVisible(void) const { return isVisible; }

	void SetFrame(char i);

	AnimationFilm * GetFilm(void) { return currFilm; }

    void SetVisibility(bool v) { isVisible = v; }
    
	/* @target: Kanei arnitiko elenxo. Dhl den epikaliptontai 
	 *		  :se sxesh me to epikaliptontai
	 * @return: true an epikaliptontai alios false
	 */
    bool CollisionCheck(Sprite* s);
	virtual void Collide(Sprite *s) = 0;

	virtual void Move(const int dx, const int dy);
	
	Sprite(Point point, AnimationFilm* film);
	Sprite(int x, int y, AnimationFilm* film);
	Sprite(const Point * const point, AnimationFilm* film);
	Sprite(int upper_x, int upper_y, int down_x, int down_y);

	virtual~Sprite(){}
};

#endif