/* header file for a wall. */

#ifndef __WALL_H__
#define __WALL_H__


#include "Sprite.h"


class Wall: public Sprite {
private:
	//Someday, something will be in here...
public:
	Wall(int upper_left_x, int upper_left_y, int down_x, int down_y);
	~Wall();
};


#endif