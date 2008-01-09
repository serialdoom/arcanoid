/*
 *author: koutsop
 * TODO na koita3w giati mou ebgaze tosa la8oi protoun kanw include to allegro??
 */


#ifndef STOREDATA_H
#define STOREDATA_H

#include <allegro.h>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

#include "Brick.h"
#include "Terrain.h"


class StoreData {
private:
	string fileName;
public:
	StoreData(string _fileName) : fileName(_fileName){}
	~StoreData(void);
	
	/* @target: Na grafei oles tis plirofories pou exei to terrain se ena arxeio.
	 */
	void StoreGame(const Terrain& terrain) const;
};

#endif