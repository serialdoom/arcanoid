/*
 * author: koutsop
 */
#ifndef ANIMATIONFILM_H
#define ANIMATIONFILM_H

#include <allegro.h>

#include <vector>
#include <cassert>
#include <string.h>

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
    

    const Oblong *GetFrameBox(char frameNo) const;
    
	void DisplayFrame(BITMAP* d, const Point& at,char frameNo) const;
    
	AnimationFilm(BITMAP* , const vector<Oblong>, const string&);

	~AnimationFilm();
};


#endif
