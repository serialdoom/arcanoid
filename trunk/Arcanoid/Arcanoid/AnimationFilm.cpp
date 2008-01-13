/*
 * author: koutsop
 */
#include "AnimationFilm.h"

AnimationFilm::AnimationFilm(BITMAP* , const std::vector<Oblong>, const std::string&)
{
}

AnimationFilm::~AnimationFilm(void)
{
}


const Oblong *AnimationFilm::GetFrameBox(char frameNo) const { 
	assert(boxes.size() > frameNo); 
	return &boxes[frameNo]; 
}

//void AnimationFilm::DisplayFrame (Bitmap d, const Point& at, byte frameNo) const
