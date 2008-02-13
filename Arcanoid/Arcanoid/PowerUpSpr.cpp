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
	if( dynamic_cast<Board*>(s) )
		SetVisibility(false);
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