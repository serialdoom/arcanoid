#include "NainSpin.h"
#include "Terrain.h"

#define SPEED_NAIN 3
NainSpin::NainSpin(Point point, AnimationFilm* film) : Sprite(point, film){
	speed = SPEED_NAIN;
}

NainSpin::NainSpin(int x, int y, AnimationFilm* film) : Sprite(x, y, film){
	speed = SPEED_NAIN;
}


void NainSpin::Move(const int dx, const int dy){
	int tmpY = GetPosition().GetY();
	//Den exei ginei collide me ton katw wall
	if( (tmpY + GetHeight()) < (Terrain::height+Terrain::coordinates.GetY())  )		
		SetPosition(GetPosition().GetX(), tmpY + speed);
	else{											//Kanei collide me ton katw wall
		SetVisibility(false);
	}
	return;
}