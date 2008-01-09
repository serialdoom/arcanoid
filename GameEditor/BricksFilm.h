#ifndef BRICKSFILM_H
#define BRICKSFILM_H

//TODO meta ston destructor prepei na 

#include <vector>
#include <allegro.h>
#include <cassert>
#include "Brick.h"

typedef vector<Brick *> brickContainer;

class BricksFilm {
private:
	friend class LoadData;	
	int width;
	int height;
	int numOfBricks;
	brickContainer  bricks;
	string			fileNameBricksFilm;

public:
	BricksFilm(void);
	~BricksFilm(void);
	
	string GetFileNameBricksFilm(void)	const { return fileNameBricksFilm; }
	int GetNumberOfBricks(void)			const { return numOfBricks; }
	int GetBrickWidth(void)				const { return width; }
	int GetBrickHeight(void)			const { return height; }
	Brick* GetBrick(unsigned int i)		const;

	/* @target: Na kanei load se ena bitmap to film me ta bricks. An den mporesei
	 *		  :stamata h diadikasia h ektelesh.
	 * @param : To bitmap sto opoio 8a ginei ti load
	 * @return: To source pou 8a exei plewn ginei to load.
	 */
	BITMAP *LoadBitmapBricks(BITMAP *source);

	/* @target: kanei blit to bitmap tou menu bricks
	 * @input : source einai to bitmap pou exei thn pliroforia gia to menubricks
	 *		  :dest einai se poio shmeio 8a ginei to blit.
	 * @precotidition: 8a prepei prwta na exei ginei to lad gia to source kai to dest
	 */
	void BlitBricks(BITMAP *source, BITMAP *dest);

	/* @target: Epistrefei thn domh pou einai filagmena ola ta bricks tou menu.
	 * @return: Thn domh pou filame ta bricks tou menu.
	 */
	brickContainer GetAllBricks(void)	const;
};

#endif