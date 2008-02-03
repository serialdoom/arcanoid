/*
 * author: koutsop
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <allegro.h>		//Eidea den exw giati xriazete ala stamata na peta la8oi h allgero

#include "Point.h"
#include "Oblong.h"
#include "AnimationFilm.h"


typedef enum spritetype_t{ 
	SPRITE_BALL			= 0,
	SPRITE_BOARD		= 1,
	SPRITE_BRICK		= 2,
}spritetype_t;


class Sprite : public Oblong {
private:
	char			frameNo;
    bool			isVisible;
	Point			position;
    AnimationFilm*	currFilm;

protected:
	spritetype_t	spriteType;

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
	void		 SetType(spritetype_t type) { spriteType = type; }
	spritetype_t GetType(void)  const { return spriteType; }

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