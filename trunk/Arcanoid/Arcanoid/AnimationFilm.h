/*
 * author: koutsop
 */
//TODO line:30
//TODO na ulopieisw thn DisplayFrame;
#ifndef ANIMATIONFILM_H
#define ANIMATIONFILM_H

#include <allegro.h>

#include <vector>
#include <cassert>
#include <string.h>

#include "Point.h"
#include "Oblong.h"

using std::string;
using std::vector;

class AnimationFilm {
private:
    BITMAP*			bitmap;
    string			id;
	vector<Oblong>	boxes;
    
public:
	BITMAP*	GetBitmap (void)	const { return bitmap; }
	const string  GetId (void)	const { return id; }
    char GetTotalFrames (void) 	const { return static_cast<char>(boxes.size()); }
    
	//TODO na epistrefei ptr h' object
    const Oblong * GetFrameBox(char frameNo) const;
    
	void DisplayFrame(BITMAP* dest, const Point& at,char frameNo) const;
    
	AnimationFilm(BITMAP* , const vector<Oblong>&, const string&);

	~AnimationFilm();
};


#endif
