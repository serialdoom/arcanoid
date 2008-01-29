/* header file for a wall. */

#ifndef __WALL_H__
#define __WALL_H__


#include "Sprite.h"
#include "SpriteType.h"


class Wall: public Sprite {
private:
	spritetype_t spriteType;
	//Someday, something will be in here...
	//ok
public:
	void SetType(spritetype_t type) { spriteType = type; }
	spritetype_t GetType(void) const { return spriteType; }
	Wall(int upper_left_x, int upper_left_y, int down_right_x, int down_right_y);
	virtual void Collide(Sprite *s);
	~Wall();
};


#endif