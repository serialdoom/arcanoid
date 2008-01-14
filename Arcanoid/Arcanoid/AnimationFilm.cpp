/*
 * author: koutsop
 */
#include "AnimationFilm.h"

AnimationFilm::AnimationFilm(BITMAP* _bitmap, 
							 const vector<Oblong> &_boxes, 
							 const string& _id) : bitmap(_bitmap),
												  boxes(_boxes),
												  id(_id){}

AnimationFilm::~AnimationFilm(void){
	boxes.clear();
}


const Oblong * AnimationFilm::GetFrameBox(char frameNo) const { 
	assert(boxes.size() > frameNo); 
	return &boxes[frameNo]; 
}

//void AnimationFilm::DisplayFrame (Bitmap d, const Point& at, byte frameNo) const
