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
	if( dynamic_cast<Board*>(s) && IsVisible()){
		SetVisibility(false);
		switch(kind){
			case MAX:			PowerUp::Max();			break;	//OK
			case MIN:			PowerUp::Min();			break;	//OK
			case STIC:									break;	//NO
			case LIFE_UP:		PowerUp::LifeUp();		break;	//OK
			case CLONE_BALL:							break;	//NO
			case SPEED_UP:		PowerUp::SpeedUp();		break;	//OK
			case SPEED_DOWN:	PowerUp::SpeedDown();	break;	//OK
			case DESTRUCTION:	PowerUp::Destruction(); break;	//OK
			case EXPLOSION:		PowerUp::Explosion();	break;	//OK
			case BUCKLER:								break;	//NO
			case BAD:			PowerUp::Bad();			break;	//OK
			case MONEY:			PowerUp::Money();		break;	//OK
			case BOMB:			PowerUp::Bomb();		break;	//					
			case BANANA:		PowerUp::Banana();		break;	//OK
			case FIRE:									break;	//NO
			case MONEY_X2:		PowerUp::DoubleMoney(); break;	//OK
			case NONE:									break;	//NO
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