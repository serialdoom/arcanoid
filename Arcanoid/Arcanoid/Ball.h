/* header file for the Ball. */

#ifndef __BALL_H__
#define __BALL_H__

#include <allegro.h>

#include "Sprite.h"
#include "SpriteHolder.h"
#include "StateHolder.h"
#include "AnimationFilm.h"


class Ball : public Sprite {
private:
	int maxSpeed;
	SpriteHolder * sh;
	Point old;			//Auto edw den xriazetai na einai edw.
	int speedX, speedY;
	bool goingLeft, goingUp;

	void CheckCoordinates(void);
public:

	int GetMaxSpeed(void) const { return maxSpeed; }
	void SetSpeedX(int _newspeed);
	void SetSpeedY(int _newspeed);
	int GetSpeedX(void);
	int GetSpeedY(void);
	void Move(const int dx, const int dy);
	void Collide(Sprite *s);
	void ReverseHorizon(void);
	void ReverseVertical(void);
	bool GoingUp(void);
	bool GoingLeft(void);
	
	Ball(int start_x, int start_y, AnimationFilm *af, const char *ball_string, SpriteHolder * _sh);
	~Ball(){}
};


#endif