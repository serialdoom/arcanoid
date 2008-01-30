/* Implementation of the Ball */

#include "Ball.h"

#include <iostream>

#define BALL_SPEED	1

Ball::Ball(int start_x, int start_y, 
		   AnimationFilm *af, 
		   const char *ball_string) : Sprite(start_x, start_y, af)
{
	old.SetX(start_x);
	old.SetY(start_y);
	spriteType = SPRITE_BALL;
	speedX = BALL_SPEED;
	speedY = BALL_SPEED;
	goingLeft	= false;
	goingUp		= true;
}

void Ball::Move(const int dx, const int dy){

	if(goingLeft)	{ SetPosition(GetPosition().GetX() - speedX, GetPosition().GetY()); }
	else			{ SetPosition(GetPosition().GetX() + speedX, GetPosition().GetY()); }

	if(goingUp)		{ SetPosition(GetPosition().GetX(), GetPosition().GetY() - speedY); }
	else			{ SetPosition(GetPosition().GetX(), GetPosition().GetY() + speedY); }

	return;
}

//TODO na kanw kai alla edw aplos blepw an einai tixos h' bricks kkai to paw sthn arxikh tou 8esh
void Ball::Collide(Sprite *s){
	spritetype_t type = s->GetType();
	
	if( (type == SPRITE_WALL_RIGHT) && goingUp && !goingLeft ){
		goingUp		= true;
		goingLeft	= true;
	}
	else if( (type == SPRITE_WALL_RIGHT) && !goingUp && !goingLeft ){
		goingUp		= false;
		goingLeft	= true;
	}
	else if( (type == SPRITE_WALL_UP) && goingUp && goingLeft ){
		goingUp		= false;
		goingLeft	= true;
	}
	else if( (type == SPRITE_WALL_UP) && goingUp && !goingLeft ){
		goingUp		= false;
		goingLeft	= false;
	}
	else if( (type == SPRITE_WALL_LEFT) && !goingUp && goingLeft ){
		goingUp		= false;
		goingLeft	= false;
	}
	else if( (type == SPRITE_WALL_LEFT) && goingUp && goingLeft ){
		goingUp		= true;
		goingLeft	= false;
	}
	else if( type == SPRITE_BOARD ){			//ok
		if		( StateHolder::IsGoLeft() )	{ goingLeft = true;  }
		else if ( StateHolder::IsGoRight())	{ goingLeft = false; }
		else								{ goingLeft = goingLeft; }		
		goingUp = true;
	}
	else if( type == SPRITE_BRICK ) {
		s->Set}



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
