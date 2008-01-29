/* Implementation of the Ball */

#include "Ball.h"

Ball::Ball(int start_x, int start_y, 
		   AnimationFilm *af, 
		   const char *ball_string) : Sprite(start_x, start_y, af){
	spriteType = SPRITE_BALL;
	SetSpeedX(4);
	SetSpeedY(4);
}

Ball::~Ball(){
	return;
}
void Ball::Move(const int dx, const int dy){
	SetPosition(new Point((GetPosition().GetX() + GetSpeedX()), (GetPosition().GetY() + GetSpeedY())));
	return;
}

void Ball::Collide(Sprite *s){
	//TODO: write something here
	return;
}

void Ball::SetSpeedX(int _newspeed){
	this->speedX = _newspeed;
	return;
}

void Ball::SetSpeedY(int _newspeed){
	this->speedY = _newspeed;
	return;
}

int Ball::GetSpeedX(void){
	return this->speedX;
}

int Ball::GetSpeedY(void){
	return this->speedY;
}
