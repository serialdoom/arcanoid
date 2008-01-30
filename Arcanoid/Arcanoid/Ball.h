/* header file for the Ball. */

#ifndef __BALL_H__
#define __BALL_H__

#include <allegro.h>

#include "Sprite.h"
#include "SpriteType.h"
#include "StateHolder.h"
#include "AnimationFilm.h"
#include "Brick.h"


class Ball : public Sprite {
private:
	Point old;			//Auto edw den xriazetai na einai edw.
	int speedX, speedY;
	bool goingLeft, goingUp;
	spritetype_t spriteType;

public:
	void SetType(spritetype_t type) { spriteType = type; }
	spritetype_t GetType(void) const { return spriteType; }

	void SetSpeedX(int _newspeed);
	void SetSpeedY(int _newspeed);
	int GetSpeedX(void);
	int GetSpeedY(void);
	void Move(const int dx, const int dy);
	void Collide(Sprite *s);
	
	Ball(int start_x, int start_y, AnimationFilm *af, const char *ball_string);
	~Ball(){}
};


#endif