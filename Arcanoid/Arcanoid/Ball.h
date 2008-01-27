/* header file for the Ball. */

#ifndef __BALL_H__
#define __BALL_H__

#include "Sprite.h"
#include "AnimationFilm.h"


class Ball : public Sprite {
private:
	int speed;
public:
	Ball(int start_x, int start_y, AnimationFilm *af, const char *ball_string);
	void SetSpeed(int _newspeed);
	int GetSpeed(void);
	virtual void Collide(Sprite *s);
	~Ball();
};


#endif