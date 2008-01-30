/* Implementation of the Ball */

#include "Ball.h"
#include "Brick.h"

#include <iostream>

#include "KeyLogger.h"
#include "Terrain.h"

#define BALL_SPEED	1

using std::cout;
using std::endl;

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
	int startX = Terrain::coordinates.GetX();
	int startY = Terrain::coordinates.GetY();
	int terrainW = Terrain::width;
	int terrainH = Terrain::height;
	int x = GetPosition().GetX();
	int y = GetPosition().GetY();

	KeyLogger::Write("x: %d  wall: %d\n", x, terrainW+startX);
	//cout<<"x: "<<x<<"  "<<"wall: "<<terrainW+startX<<endl;

	if( ((x+GetWidth()) >= (terrainW+startX)) && goingUp && !goingLeft ){
		KeyLogger::Write("1\n");
		goingUp		= true;
		goingLeft	= true;
	}
	else if( ((x+GetWidth()) >= (terrainW+startX)) && !goingUp && !goingLeft ){
		KeyLogger::Write("2\n");
		goingUp		= false;
		goingLeft	= true;
	}
	else if( (y == startY) && goingUp && goingLeft ){
				KeyLogger::Write("3\n");

		goingUp		= false;
		goingLeft	= true;
	}
	else if( (y == startY) && goingUp && !goingLeft ){
				KeyLogger::Write("4\n");

		goingUp		= false;
		goingLeft	= false;
	}
	else if( (x <= startX) && !goingUp && goingLeft ){
				KeyLogger::Write("5\n");

		goingUp		= false;
		goingLeft	= false;
	}
	else if( (x <= startX) && goingUp && goingLeft ){
				KeyLogger::Write("6\n");

		goingUp		= true;
		goingLeft	= false;
	}
	
	if(goingLeft)	{ SetPosition(GetPosition().GetX() - speedX, GetPosition().GetY()); }
	else			{ SetPosition(GetPosition().GetX() + speedX, GetPosition().GetY()); }

	if(goingUp)		{ SetPosition(GetPosition().GetX(), GetPosition().GetY() - speedY); }
	else			{ SetPosition(GetPosition().GetX(), GetPosition().GetY() + speedY); }

	return;
}

//TODO na kanw kai alla edw aplos blepw an einai tixos h' bricks kkai to paw sthn arxikh tou 8esh
void Ball::Collide(Sprite *s){
	spritetype_t type = s->GetType();
	
	if( type == SPRITE_BOARD ){			//ok
		if		( StateHolder::IsGoLeft() )	{ goingLeft = true;  }
		else if ( StateHolder::IsGoRight())	{ goingLeft = false; }
		else								{ goingLeft = goingLeft; }		
		goingUp = true;
	}
	else if( type == SPRITE_BRICK ) {
		dynamic_cast<Brick *>(s)->SetIsActive(true);
	}
	else
		assert(!"kapia malakia ekanes sthn ball malaka\n");
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
