/*
 * author: koutsop
 */

#include "BitmapLoader.h"

//destructor
BitmapLoader::~BitmapLoader(void){ 
	// Destroy all bitmaps in the map.
	BitmapMap::iterator start	= bitmaps.begin();
	BitmapMap::iterator end		= bitmaps.end();

	while(start != end){
		destroy_bitmap( start->second );
		start++;
	}
	bitmaps.clear();
}
////////////////////////////////////////////////////////////////////////////



void BitmapLoader::LoadFilms(const LoadFilmsInfo &filmsInfo){
	FilmsInfoMap films				= filmsInfo.GetFilmsInfo();
	FilmsInfoMap::iterator start	= films.begin();
	FilmsInfoMap::iterator end		= films.end();
	
	while( start != end ){			//Kanw load ola ta bitmap pou uparxoun.
		Load( (*start).second.second.c_str() );
		start++;
	}
}
////////////////////////////////////////////////////////////////////////////



BITMAP * BitmapLoader::GetBitmap(const string path) const {
	BitmapMap::const_iterator i = bitmaps.find(path);
	return i != bitmaps.end() ? i->second : (BITMAP*) 0;
}
////////////////////////////////////////////////////////////////////////////



BITMAP * BitmapLoader::Load (const char* path) {
	BITMAP * b = GetBitmap(path);
	if (!b) {
		bitmaps[path] = ( b = load_bitmap(path, NULL) );
		assert(b);
	}
	return b;
}