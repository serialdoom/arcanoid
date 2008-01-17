/*
 * author: koutsop
 */
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
	/* @return: Epistrefei to bitmap tou film.
	 */
	BITMAP*	GetBitmap (void)	const { return bitmap; }
	
	/* @return: To id tou string.
	 */
	const string  GetId (void)	const { return id; }
    
	/* @return: Ton sunoliko ari8mo frames tou film.
	 */
	char GetTotalFrames (void) 	const { return static_cast<char>(boxes.size()); }
    
	/* @param : Ton ari8mo apo ena sugkekrimeno frame mesa apo to film
	 * @return: To bboxe apo to sigkekrmeno frame
	 */
    const Oblong * GetFrameBox(char frameNo) const;
    
	/* @parma : dest to bitmap proorismou pou 8a na kanoume to maksed_blit
	 * @parma : at se poio sumeio tis o8wneis 8a ginei to masked_blit
	 * @parma : ton ari8mo tou frame pou 8eloume na kanoume maksed_blit
	 */
	void DisplayFrame(BITMAP* dest, const Point& at,char frameNo) const;
    
	//To BTIMAP* einai to BITMAP tou film
	AnimationFilm(BITMAP* , const vector<Oblong>&, const string&);

	~AnimationFilm();
};


#endif
