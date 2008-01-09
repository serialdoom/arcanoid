/*
 *author: koutsop
 */
//TODO prepei na e3afanizw ton cursor sta shmeia pou den mporei na balei 
//toublakia

#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <allegro.h>
#include "Point.h"
#include "Terrain.h"
#include "Brick.h"

using namespace std; 

class Terrain {
private:
	friend class LoadData;
	Brick** terrain;
	Point coordinates;			//Oi suntetagmenes gia to pou briskete to terrain
	bool callLoadTerrain;		//An den exoume kalesei thn loadTerrain na mhn ekteleite kwdikas ston destructor
	string fileNameBackgroundImage;
	int width;
	int height;
	int colum;
	int row;

	//prosoxh kaloume thn malloc edw kai mporei na exoume problhma
	void CreateTerrain(void);

public:
	Terrain(void);
	~Terrain(void);

	string GetFileNameBackgroundImage(void)	const { return fileNameBackgroundImage; }

	Point GetTerrainCort(void)	const { return coordinates; }
	int GetTerrainWidth(void)	const { return width; }
	int GetTerrainHeight(void)	const { return height; }
	int GetTerrainColum(void)	const { return colum; }
	int GetTerrainRow(void)		const { return row; }

	//prepei prwta na exei kalestei h LoadData::LoadTerrainInfo
	//dimiourgei ton pinaka gia ta dedomena
	/* @target: Na dinei arxikes times sta bricks tou terrain mas.
	 * @param : To mikos kai to platos tou ka8e tera
	 * @precodition: Prepei na exei kalesth prwta h method LoadData::LoadTerrainInfo
	 *			   :wste na thn kalesoume
	 */
	void LoadTerrain(int brickWidth, int brickHeigth);
	
	/* @target: na kanei load to bitmap gia to terrain. An den mporesei stamata h 
	 *		  :diadikasia h ektelesh.
	 * @param : To bitmap sto opoio 8a ginei ti load
	 * @return: To source pou 8a exei plewn ginei to load.
	 */
	BITMAP *LoadBitmapTerrain(BITMAP *source);

	/* @target: kanei blit to bitmap tou terrain
	 * @input : source einai to bitmap pou exei thn pliroforia gia to terrain
	 *		  :dest einai se poio shmeio 8a ginei to blit.
	 */
	void BlitTerrain(BITMAP *source, BITMAP *dest);

	/* @target: Na epistrfei ena sugkekrimeno Brick apo to terrain.
	 * @parama: thn gramh kai thn sthlh pou brikete to sigkekrimeno brick mesa
	 *		  :ston pinakas me ta bricks pou anaparistoun to terrain.
	 * @return: To brick pou ziti8ike.
	 */
	Brick* GetTerrainBrick(const int i, const int j) const;

	/* target: Na grafei se ena arxeio tis coordinates pou exei to ka8e brick
	 *		 :tou terrain.
	 */
	void PrintTerrainBricksCor(void);
};

#endif
