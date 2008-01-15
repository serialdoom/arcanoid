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
	char		frameNo;
    bool		isVisible;
    AnimationFilm*	currFilm;

public:	
	char GetFrame(void)		const { return frameNo; }
	bool IsVisible(void)	const { return isVisible; }

	void SetFrame(char i);
    void SetVisibility(bool v) { isVisible = v; }
    
    bool CollisionCheck(Sprite* s);

	Sprite(Point point, AnimationFilm* film);
	Sprite(int x, int y, AnimationFilm* film);
	Sprite(const Point * const point, AnimationFilm* film);

	virtual~Sprite(){}
};

#endif