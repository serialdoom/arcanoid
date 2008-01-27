/* header file for a wall. */

#ifndef __WALL_H__
#define __WALL_H__


#include "Sprite.h"


class Wall: public Sprite {
private:
	//Someday, something will be in here...
	//ok
public:
	Wall(int upper_left_x, int upper_left_y, int down_right_x, int down_right_y);
	virtual void Collide(Sprite *s);
	~Wall();
};


#endif