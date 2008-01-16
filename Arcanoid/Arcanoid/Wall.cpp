/* implementation of a Wall */

#include "Wall.h"



Wall::Wall(int upper_left_x, int upper_left_y, AnimationFilm *Nul){
	assert(!Nul); // we want this to be null. this is the wall and thus not visible.
	SetVisibility(false);
}



Wall::~Wall(){
	return;
}
