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



	//BITMAP * LoadBitmap(const std::string& path);  einai h load_bitmap
	//void	 DestroyBitmap(BITMAP *);				 einai h destroy_bitmap


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

	/* @target: na kanei isagwgh mesa sto map ena neo zeugarh string bitmap
	 * @return: to bitmap pou isagame. An uparxei idi mesa epistrefoume to idio
	 */
    BITMAP * Load (const char* path);

    BitmapLoader(const LoadFilmsInfo &filmsInfo);
    ~BitmapLoader();

};

#endif