/* header file for a wall. */

#ifndef __WALL_H__
#define __WALL_H__


#include "Sprite.h"
#include "AnimationFilm.h"

class Wall: public Sprite {
private:
	//Someday, something will be in here...
public:
	Wall(int upper_left_x, int upper_left_y, AnimationFilm *Null);
	~Wall();
};


#endif