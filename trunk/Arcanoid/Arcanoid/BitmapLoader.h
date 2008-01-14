/*
 * author: koutsop
 */

#ifndef BITMAPLOADER_H
#define BITMAPLOADER_H


#include <string>
#include <allegro.h>

using std::string;



//Bitmap	LoadBitmap (const std::string& path);
//void	DestroyBitmap (Bitmap);
/*

class BitmapLoader {
private:
	typedef std::map<std::string, Bitmap> BitmapMap;
    BitmapMap bitmaps;
    
	BITMAP * GetBitmap(const string path) const;

public:
    BITMAP * Load (const std::string& path) {
		Bitmap b = GetBitmap(path);
		if (!b) {
			bitmaps[path] = (b = LoadBitmap(path));
			assert(b);
		}
		return b;
    }
    BitmapLoader (void){}
    ~BitmapLoader() { 
		// Destroy all bitmaps in the map.
		bitmaps.clear();
    }

};
*/
#endif