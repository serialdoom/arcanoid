/* implementation of a Wall */

#include "Wall.h"

Wall::Wall(int upper_left_x, int upper_left_y, int down_right_x, int down_right_y) 
			: Sprite(upper_left_x, upper_left_y, down_right_x, down_right_y)
{
	SetVisibility(false);
	spriteType = SPRITE_WALL;
	this->SetPosition(new Point(upper_left_x, upper_left_y));
	this->SetHeight(down_right_y - upper_left_y);
	assert(down_right_y - upper_left_y >0);
	this->SetWidth(down_right_x - upper_left_x);
	assert(down_right_x - upper_left_x >0);
}

void Wall::Collide(Sprite *s){
	//TODO: fill it up
	return;
}


Wall::~Wall(){
	return;
}
