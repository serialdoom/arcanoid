/* Implementation of the Ball */

#include "Ball.h"

Ball::Ball(int start_x, int start_y, 
		   AnimationFilm *af, 
		   const char *ball_string) : Sprite(x, y, af){
	speed = 0;
}

void Ball::SetSpeed(int _newspeed){
	speed = _newspeed;
	return;
}

int Ball::GetSpeed(void){
	return speed;
}

/*
void Ball::Activate(){
	isActive = true;
	return;
}

void Ball::Deativate(){
	isActive = false;
	return;
}

bool Ball::isActive(){
	return isActive;
	return;
}

Ball::~Ball(){
	return;
}
*/