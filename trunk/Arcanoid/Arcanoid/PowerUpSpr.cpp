#include "PowerUpSpr.h"

#include "PowerUp.h"


#include <iostream>

#include "Terrain.h"

#define SPEED_POWER 1


PowerUpSpr::PowerUpSpr(Point point, AnimationFilm* film): Sprite(point, film){
	this->SetVisibility(false);
	return;
}


void PowerUpSpr::Collide(Sprite *s){
	//TODO: wtite code.
	if( dynamic_cast<Board*>(s) ){
		SetVisibility(false);
		switch(kind){
			case MAX:			//PowerUp::Max(); break;
			case MIN:			PowerUp::Min(); break;
			case STIC:			break;
			case LIFE_UP:		break;//PowerUp::LifeUp(); break;
			case CLONE_BALL:	break;
			case SPEED_UP:		break;//PowerUp::SpeedUp(); break;
			case SPEED_DOWN:	break;//PowerUp::SpeedDown(); break;
			case DESTRUCTION:	break;
			case EXPLOSION:		break;
			case BUCKLER:		break;
			case BAD:			break;
			case MONEY:			break;//PowerUp::Money(); break;
			case BOMB:			break;
			case BANANA:		break;
			case FIRE:			break;
			case MONEY_X2:		break;
			case NONE:			break;
			default: assert(0);
		}//end of chitc
	}
	return;
}


void PowerUpSpr::Move(const int x, const int y){
	int tmpY = GetPosition().GetY();

	//Den exei ginei collide me ton katw wall
	if( (tmpY + GetHeight()) < (Terrain::height+Terrain::coordinates.GetY())  ){	
		SetPosition(GetPosition().GetX(), tmpY + SPEED_POWER);
	}
	else{											//Kanei collide me ton katw 
		SetVisibility(false);
	}
	return;
}


PowerUpSpr::~PowerUpSpr(){
}