/*
 * author: koutsop
 */

#ifndef LOADDATA_H
#define LOADDATA_H

#include <string>
#include <cassert>
#include <allegro.h>
#include <vector>
#include "Point.h"
#include "Brick.h"
#include "Terrain.h"
#include "OkCancel.h"
#include "BricksFilm.h"



using namespace std;

class LoadData {
	string fileNameToWrite;
	/* @target: Kanei sunenwsei enos string me enan ari8mo.*/
	const char * AppendIntegerToString( string str, int i);

public:
	LoadData(void);
	~LoadData(void);

	/* @target: Na epistrefei to onoma tou arxeiou pou prokite na grafei h 
	 *		  : pliroforia pou exei o terrain.
	 * @return: to onoma tou arxeiou.
	 */
	string GetFileNameToWrite(void)	const { return fileNameToWrite; }

	
	/* @target: Na diabazei apo to cfg. file to onoma tou arxeiou pou prokite
	 *		  :na graftoun ta dedomena pou 8a exei to terrain mas.
	 */
	void LoadFileNameToWrite(void);


	/* @target: Na dibazei apo to cfg. file ola ta dedomena pou exoun sxesh me 
	 *		  :to terrain.
	 */
	void LoadTerrainInfo(Terrain& terrain);


	/* @target: Na dibazei apo to cfg. file ola ta dedomena pou xriazete gia to
	 *		  :ok, cancel.
	 */
	void LoadOkCancel(OkCancel& oc);

	/* @traget: Na diabazei apo to cgf. file ola ta dedomena pou aforoun to film
	 *		  :pou exei ta bricks.
	 */
	void LoadBricksFilmInfo(BricksFilm& film);

	/* @target: Na dibazei apo to cfg. file ola ta dedomena gia to ka8e ena brick
	 *		  :pou exei mesa sto film me ta bricks.
	 * @param : Mia anafora sthn domh twn films
	 * @precodition: Prepei prwtoun kalestei auth h method na exoume ton ari8mo twn
	 *			   :bricks pou briskonte mesa sto film me ta bricks.
	 */
	void LoadBricksFilm(BricksFilm& film);
};
#endif