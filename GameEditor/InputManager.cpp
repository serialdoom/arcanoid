/*
 *author: koutsop
 */
//TODO na dw an mesa sthn collision xriazete telika h isotita h' oxi
//An 8elw na mporw na paw kai na pana=ografw 8a prepei na paw sthn
//CheckMouseButton kai na bgalw bgalw ton elegxo isActive apo thn
//Deuterh else if
#include "InputManager.h"

InputManager::InputManager(void){
	currentBrick = (Brick*)0;
}

InputManager::~InputManager(void)
{
}
// kanei elegxo an: x1 < x < x2 kai y1 < y < y2
//Den kanoume elegxo sthn isotita gia thn epikaliyh ton gutonikwn sumeiwn.
bool InputManager::Collision( int x1, int  y1, int x2, int y2, int x, int y ){
	if( (x1 <= x) && (x <= x2) && (y1 <= y) && (y <= y2) )
		return true;
	return false;
}


bool InputManager::CheckAreaMenuBricks(const BricksFilm& film){
	Brick* start = film.GetBrick(0);							//To panw aristera point 8a einai kai to panw aristera point gia to menu me ta bricks
	Brick* end   = film.GetBrick(film.GetNumberOfBricks()-1);	//To idio me panw

	assert(start);
	assert(end);
		
	int upX		= start->GetPointUpLeft().GetX();
	int upY		= start->GetPointUpLeft().GetY();
	int downX	= end->GetPointDownRight().GetX();
	int downY	= end->GetPointDownRight().GetY();
	return Collision(upX, upY, downX, downY, mouse_x, mouse_y);
}

bool InputManager::CheckAreaTerrain(const Terrain& terrain){
	int row				= terrain.GetTerrainRow();
	int colum			= terrain.GetTerrainColum();
	Brick* upBrick		= terrain.GetTerrainBrick(0, 0);
	Brick* downBrick	= terrain.GetTerrainBrick(row-1, colum-1);
	
	assert(row >= 0);
	assert(colum >= 0);
	assert(upBrick);
	assert(downBrick);
	return Collision( upBrick->GetPointUpLeft().GetX(), 
					  upBrick->GetPointUpLeft().GetY(), 
					  downBrick->GetPointDownRight().GetX(), 
					  downBrick->GetPointDownRight().GetY(), 
					  mouse_x, mouse_y );
}

// Diatrexei olh thn domh me ta bricks kai elegxei an uparxei collision me kapio apo ta bricks
Brick* InputManager::FindMenuBrick(const BricksFilm& film){

	brickContainer tmp				= film.GetAllBricks();
	brickContainer::iterator start	= tmp.begin();
	brickContainer::iterator end	= tmp.end();

	while( start != end ){
		if( Collision  (
						(*start)->GetPointUpLeft().GetX(),
						(*start)->GetPointUpLeft().GetY(), 
						(*start)->GetPointDownRight().GetX(), 
						(*start)->GetPointDownRight().GetY(), 
						mouse_x, mouse_y
						)
		   ){ return (*start); }
		start++;
	}

	return false;
}

//diatrexei olh thn domh tou terrain gia na brei an upaxei brick pou exei 
//collision me to mouse.
Brick* InputManager::FindBrickTerrain(const Terrain& terrain){
	int	row		= terrain.GetTerrainRow();
	int colum	= terrain.GetTerrainColum();

	for(int i = 0; i < row; i++){
		for(int j = 0; j < colum; j++){
			Brick* tmp = terrain.GetTerrainBrick(i, j);
			if( Collision(  
							tmp->GetPointUpLeft().GetX(),
							tmp->GetPointUpLeft().GetY(),
							tmp->GetPointDownRight().GetX(),
							tmp->GetPointDownRight().GetY(),
							mouse_x, mouse_y
						 )
				) {return tmp;}
		}
	}
	return (Brick*)0;
}

//Ginete 3exwristh sunarthshkai oxi mesa sthn alh e3etias tou mege8ous pou exei h alh
void InputManager::CheckOkCancel(OkCancel& choice){
	if( mouse_b & 1){
		//Elegxos an pati8ike to ok
		if( Collision(
						choice.GetOkUpCort().GetX(),
						choice.GetOkUpCort().GetY(),
						choice.GetOkDownCort().GetX(),
						choice.GetOkDownCort().GetY(),
						mouse_x, mouse_y
					 ) 
		  ){ choice.SetPushOk(true); }

		if( Collision(
						choice.GetCancelUpCort().GetX(),
						choice.GetCancelUpCort().GetY(),
						choice.GetCancelDownCort().GetX(),
						choice.GetCancelDownCort().GetY(),
						mouse_x, mouse_y
					 ) 
		  ){ choice.SetPushCancel(true); }
	}
	return;
}


//DEn prepei me tipota na einai null to terrain kai to film
void InputManager::CheckBricks(const Terrain& terrain, const BricksFilm& film, BITMAP* bricks, BITMAP* background, BITMAP* buffer){
assert(bricks && background && buffer);
	if( mouse_b & 1 ){							//an pati8ike to aristero button apo to mouse
		if(CheckAreaMenuBricks(film)){			//einai sthn perioxh pou briskontai ta bricks epiloghs
			if( currentBrick = FindMenuBrick(film) ){ 
				scare_mouse();
				blit(bricks, mouse_sprite, (currentBrick->GetFrameNum()*currentBrick->GetWidth()), 0, 0, 0, 24, 12);
				unscare_mouse();
				set_mouse_sprite(mouse_sprite);
				show_mouse(screen);
			}
		}//if
		else if(CheckAreaTerrain(terrain)){						//einai sthn perioxh tou terrain
			Brick* tmp = FindBrickTerrain(terrain);
			if(tmp && !tmp->IsActive() &&  currentBrick){	//!isActive gia na mhn panwgrafoume
				tmp->Copy(currentBrick);
				scare_mouse();							//Otan zwgrafizoume prepei na klinoume to mouse
				blit(bricks, 
					 buffer, 
					 (tmp->GetFrameNum()*tmp->GetWidth()), 0, 
					 tmp->GetPointUpLeft().GetX(), 
					 tmp->GetPointUpLeft().GetY(), 
					 tmp->GetWidth(), tmp->GetHeight()
					 );
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				unscare_mouse();
			}

		}//else if
		else return;						//Den einai pou8ena pou na mas endiaferei pros to parwn
	}

	else if( mouse_b & 2){						//An pati8ike to de3i button apo to mouse
		if(CheckAreaTerrain(terrain)){						//einai sthn perioxh tou terrain
			Brick* tmp = FindBrickTerrain(terrain);
			if(tmp && tmp->IsActive() ){	//!isActive gia na mhn panwgrafoume
				tmp->SetIsActive(false);
				scare_mouse();
				blit(background, 
					 buffer,
					 terrain.GetTerrainCort().GetX(),
					 terrain.GetTerrainCort().GetY(),
					 tmp->GetPointUpLeft().GetX(), 
					 tmp->GetPointUpLeft().GetY(), 
					 tmp->GetWidth(), tmp->GetHeight()
					);
				blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
				unscare_mouse();
			}//second if
		}//first if
	}//else if
	return;
}



/*
TODO ton tetarto elegxo den ton exw ftia3ei
//Briskei se poio tetartimwrio pati8ike to mouse button gia na brei to katalilo brick
//Me auto ton tropo den xriazete na ya3oume olo ton pinaka apo thn arxh
//prepei prwta na exei ginei elegxos an to button pati8ike se nomhmh perioxh
//tou terrain.
typedef enum Quadrant{
				quadrantUpLeft		= 1,
				quadrantUpRight		= 2,
				quadrantDowbLeft	= 3,
				quadrantDownRight	= 4
			 } Quadrant;

Quadrant InputManager::FindQuadrantTerrain(const Terrain& terrain){
	int row				= terrain.GetTerrainRow();
	int colum			= terrain.GetTerrainColum();
	Brick* upLeft		= terrain.GetTerrainBrick(0, 0);
	Brick* upRight		= terrain.GetTerrainBrick(0, colum-1);
	Brick* downLeft		= terrain.GetTerrainBrick(row-1, 0);
	Brick* downRight	= terrain.GetTerrainBrick(row-1, colum-1);
	Brick* middle		= terrain.GetTerrainBrick(row/2, colum/2);

	
	if( Collision(	upLeft->GetPointUpLeft().GetX(),
							upLeft->GetPointUpLeft().GetY(),
							middle->GetPointUpLeft().GetX(),
							middle->GetPointUpLeft().GetY(),
							mouse_x, mouse_y
						)
		) { return quadrantUpLeft;	}		//Elegxos an anikei sto panw ariste tetartimorio
	
	else if(Collision(	middle->GetPointDownRight().GetX(),
								middle->GetPointDownRight().GetY(),
								downRight->GetPointDownRight().GetX(),
								downRight->GetPointDownRight().GetY(),
								mouse_x, mouse_y
							  )
			) {return quadrantDownRight;}		//Elegxos an anikei sto katw de3ia 

	else if(Collision(	middle->GetPointUpLeft().GetX(),
								downLeft->GetPointDownRight().GetY(),
								downLeft->GetPointDownRight().GetX()-downLeft->GetWidth(),//gia na paroume katw aristera tou brick
								middle->GetPointUpLeft().GetY(),
								mouse_x, mouse_y
							  )
			){return quadrantDowbLeft;}		//Prosoxh edw 8eloume to x1 < mouse_x < x2 kai y2 < mouse_y < y1

	else if(Collision(	middle->GetPointUpLeft().GetX(),
								upLeft->GetPointUpLeft().GetY(),
								middle->GetPointUpLeft().GetX(),
								middle->GetPointUpLeft().GetY(),
								mouse_x, mouse_y
							  )
			){return quadrantUpRight;}			//Prosoxh edw 8eloume to x1 < mouse_x < x2 kai y2 < mouse_y < y1

	else{}								//Kanonika 8a eprepe se kapio apo ta tetartimoria
										//Alla den bazoume assert giati mporei na exei pesei anamesa
										//se duo shmeia pou exoun epikaliyh ;-)

	return quadrantUpLeft;
}
*/