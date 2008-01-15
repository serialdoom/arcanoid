/*
 * author: koutsop
 */

#ifndef BITMAPLOADER_H
#define BITMAPLOADER_H

#include <map>
#include <string>
#include <cassert>
#include <allegro.h>

#include "LoadFilmsInfo.h"

using std::string;

class BitmapLoader {

private:
	//string 8a einai to path
	typedef std::map<std::string, BITMAP *> BitmapMap;
    BitmapMap bitmaps;
    
	/* @target: Na epidtrefei ena sugkekrimeno bitmap mesa apo to map ou filame ta bitmpas
	 * @param : path einai to path einai to kleidi tou map gia na broume ena bitmap me to
	 *		  :sugkekrimeno path.
	 * return : An uparxei bitmap me to sugkekrimeno path to bitmap alios null
	 */
	BITMAP * GetBitmap(const string path) const;

public:

	int GetSize(void) const { return (int)bitmaps.size(); } /* added typicast for a warning */

	/* @target: na kanei isagwgh mesa sto map ena neo zeugarh string bitmap
	 * @return: to bitmap pou isagame. An uparxei idi mesa epistrefoume to idio
	 */
    BITMAP * Load(const char* path);

	/* @target: Na kanei load ola ta films pou mporei na xrisimopiei to paixnidi mas
	 */
	void LoadFilms(const LoadFilmsInfo &filmsInfo);

	BitmapLoader(void){}
    ~BitmapLoader();

};

#endif