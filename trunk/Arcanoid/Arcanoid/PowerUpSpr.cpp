#include "PowerUpSpr.h"


PowerUpSpr::PowerUpSpr(Point point, AnimationFilm* film): Sprite(point, film){
	this->SetVisibility(false);
	return;
}


void PowerUpSpr::Collide(Sprite *s){
	//TODO: wtite code.

	return;
}

PowerUpSpr::~PowerUpSpr(){
}