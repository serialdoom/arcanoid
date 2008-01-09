#ifndef __BALL_H__
#define __BALL_H__


#include <allegro.h>
#include <assert.h>


class Ball{
private:
	int pos_x, pos_y, speed;
	int going_left, going_up;
	BITMAP *ball_bmp;

public:
	Ball(char *filename);
	void display(BITMAP *board);
	void move(void);
	void setspeed(int speedo);
	~Ball();
};

#endif