/*
 * author: koutsop
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <allegro.h>		//Eidea den exw giati xriazete ala stamata na peta la8oi h allgero

#include "Point.h"
#include "Oblong.h"
#include "SpriteType.h"
#include "AnimationFilm.h"


class Sprite : public Oblong {
private:
	char			frameNo;
    bool			isVisible;
	Point			position;
    AnimationFilm*	currFilm;

public:	

	void SetFrame(char i);

	void Display(BITMAP *bitmap);

	Point GetPosition(void) const { return position; }

	void SetPosition(Point point) { position = point; }

	void SetPosition(int x, int y);

	char GetFrame(void) const { return frameNo; }

	bool IsVisible(void) const { return isVisible; }

	AnimationFilm * GetFilm(void) { return currFilm; }

    void SetVisibility(bool v) { isVisible = v; }
    
	/* @target: Kanei arnitiko elenxo. Dhl den epikaliptontai 
	 *		  :se sxesh me to epikaliptontai
	 * @return: true an epikaliptontai alios false
	 */
    bool CollisionCheck(Sprite* s);
	

	virtual void Collide(Sprite *s) = 0;


	/* @return: Epistrefei ton typo tou ka8e sprite
	 */
	virtual spritetype_t GetType(void) const = 0;


	/* @target: Einai h Move gia to ekatos8e sprite
	 */
	virtual void Move(const int dx, const int dy);
	
	Sprite(Point point, AnimationFilm* film);
	Sprite(int x, int y, AnimationFilm* film);
	Sprite(const Point * const point, AnimationFilm* film);
	Sprite(int upper_x, int upper_y, int down_x, int down_y);

	virtual~Sprite(){}
};

#endif