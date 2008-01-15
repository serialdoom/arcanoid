/* header file for the Ball. */

#ifndef __BALL_H__
#define __BALL_H__

#include "Sprite.h"
#include "AnimationFilmHolder.h"


class Ball : public Sprite {
private:

public:
	Ball(int start_x, int start_y, AnimationFilmHolder *afm, const char *ball_string);
	~Ball();
};


#endif