/*
 *author: koutsop
 */
#include "Terrain.h"

Terrain::Terrain(void)
{
	callLoadTerrain = false;
}

Terrain::~Terrain(void)
{
	if( callLoadTerrain ){				//Se periptwsh pou den exoume kalesei thn LoadTerrain
		for(int i = 0; i < row; i++ )
			delete(terrain[i]);
		delete(terrain);
	}
}

void Terrain::CreateTerrain(void){
	assert(row > 0);
	assert(colum > 0);

	terrain = (Brick **)malloc( row * sizeof(Brick *) );
	for(int i = 0; i < row; i++  )
		terrain[i] = (Brick *)malloc( colum * sizeof(Brick) );
	return;
}


//na dinei arxikes times sta bricks tou pinaka
void Terrain::LoadTerrain(int brickWidth, int brickHeigth){
	assert(row > 0);
	assert(colum > 0);
	assert(terrain);

	CreateTerrain();

	for(int i = 0; i < row; i++){
		for(int j = 0; j < colum; j++){			//Pernoun times ta bricks tou pinaka
			terrain[i][j].SetIsActive(false);
			terrain[i][j].SetPointUpLeft(
										 coordinates.GetX() + (j*brickWidth),
										 coordinates.GetY() + (i*brickHeigth) 
										 );
			terrain[i][j].SetPointDownRight(
											terrain[i][j].GetPointUpLeft().GetX()+brickWidth,
											terrain[i][j].GetPointUpLeft().GetY()+brickHeigth
											);
			terrain[i][j].SetWidth(brickWidth);
			terrain[i][j].SetHeight(brickHeigth);
		}
	}

	return;
}

BITMAP *Terrain::LoadBitmapTerrain(BITMAP *source){
	if( !(source = load_bitmap(fileNameBackgroundImage.c_str(), NULL)) ){
		allegro_message(fileNameBackgroundImage.c_str());
		exit(-1);
	}
	return source;
}

//prepei prwta na exei ginei load to source
void Terrain::BlitTerrain(BITMAP *source, BITMAP *dest){
	assert(source);
	assert(dest);
	blit(source, dest, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}


Brick* Terrain::GetTerrainBrick(const int i, const int j)const{
	assert(i >=0 && i < row);
	assert(j >= 0 && j < colum);
	return &terrain[i][j];
}

void Terrain::PrintTerrainBricksCor(void){
	ofstream out("terrainCoordinates.txt");

	for(int i = 0; i < row; i++){
		for(int j = 0; j < colum; j++ ){
			if(out.is_open()){
				out<<"["<<i<<", "<<j<<"] ";
				out<< "up{x=" << terrain[i][j].GetPointUpLeft().GetX() << ", y=" << terrain[i][j].GetPointUpLeft().GetY()<<"}  ";
				out<<"down{x="<<terrain[i][j].GetPointDownRight().GetX()<<", y=" << terrain[i][j].GetPointDownRight().GetY()<<"}\n";
			}
		}
		out<<"\n\n\n";
	}
	return;
}