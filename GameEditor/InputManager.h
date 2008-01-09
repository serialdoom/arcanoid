/*
 *author: koutsop
 */
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <allegro.h>
#include <cassert>

#include "Point.h"
#include "Brick.h"
#include "Terrain.h"
#include "OkCancel.h"
#include "BricksFilm.h"

using namespace std;

class InputManager {
private:

	Brick*	currentBrick;			//Einai to brick pou exei epilegei apo to menu;
	
	/* @target: Kanei elegxo an uparxei collision meta3i mias sugkekrinemhs
	 *		  :perioexhs kai enos shmiou. Dhl an: x1 < x < x2 kai y1 < y < y2.
	 * @param : int x1, y1 tis suntetagmenes tou panw aristero shmeiou ths perioxhs
	 *		  : int x2, x2 tis suntetagmenes tou kate de3iou shmeiou ths perioxhs
	 *		  : int x, y, tis suntetagmens tou sumiou pros elegxos.
	 * @return: true an uparxei collisio alios false.
	 */
	bool	Collision( int x1, int  y1, int x2, int y2, int x, int y );
	
	/* @target: Kanei elegxo an to pontikh briskete mesa sthn prioxh pou 
	 *		  : einai to menu me ta bricks. 
	 * @param : Mia anafora sthn domh pou periexei ta bricks tou menu
	 * @return: true an to pontikh briskete mesa sthn perioxh tou menu me ta bricks
	 *		  : false alios.
	 */

	bool	CheckAreaMenuBricks(const BricksFilm& film);

	/* @target: Kanei elegxo an to pontikh brickete mesa sthn perioxh tou terrain.
	 * @parma : Anafora sto terrain tou paixnidiou.
	 * @return: true an to pontikh briskete mesa sthn perioxh tou terrain false alios.
	 */
	bool	CheckAreaTerrain(const Terrain& terrain);

	/* @target: Diatrexei olh thn domh me ta menu bricks kai elegxei 
	 *		  :an uparxei collision mat3i kapiou brick kai tou mouse.
	 * @parma : Mia anafora sthn domh pou periexei ta bricks tou menu.
	 * @return: To brick pou exei to collision alios null.
	 */
	Brick*	FindMenuBrick(const BricksFilm& film);
	
	/* @target: Diatrexei olh thn domh me to terrain kai elegxei an uparxei
	 *		  :collision meta3i kapiou brick kai tou mouse
	 * @param : Anafora sto terrain tou paixnidiou.
	 * @return: To brick pou exei to collision alios null.
	 */
	Brick*	FindBrickTerrain(const Terrain& terrain);


public:
	InputManager(void);
	~InputManager(void);
	
	/* @target: Elegxei an exei pati8ei to ok h' to cancel. An exei pati8ei frontizei
	 *		  : wste na enimerwsei to stigmiotipo gia thn alagh pou exei ginei.
	 * @param : Mia anafora sthn domh tou Ok, Cancel
	 */
	void CheckOkCancel(OkCancel& choice);
	
	/* @target: Elegxei an exei pati8ei to aristero h' to de3i button tou mouse 
	 *		  :sthn perioxh tou terrain h' tou menu bricks. Kai 8etei to cursor tou
	 *		  :mouse me to katalilo bitmap.
	 * @param : Anafora sthn domh tou terrain, anafora sthn domh me to menuBricks
	 *		  :source apo poio bitmap 8a ginei to blit, dest se poio bitmap 8a 
	 *		  :ginei to blit;
	 */
	void CheckBricks(const Terrain& terrain, const BricksFilm& film, BITMAP* bricks, BITMAP* background, BITMAP* buffer);
};

#endif