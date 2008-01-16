/*
 *author: koutsop
 */
#include "AnimatorHolder.h"

std::list<Animator*> AnimatorHolder::running;
std::list<Animator*> AnimatorHolder::suspended;

void AnimatorHolder::Register(Animator* a){ 
	suspended.push_back(a); 
}

/////////////////////////////////////////////////////////////////////

void AnimatorHolder::Cancel(Animator* a){ 
	suspended.remove(a); 
}

/////////////////////////////////////////////////////////////////////

void AnimatorHolder::MarkAsRunning (Animator* a){ 
	suspended.remove(a); 
	running.push_back(a); 
}

/////////////////////////////////////////////////////////////////////

void AnimatorHolder::MarkAsSuspended (Animator* a){ 
	running.remove(a); 
	suspended.push_back(a); 
}

/////////////////////////////////////////////////////////////////////

void AnimatorHolder::Progress (timestamp_t currTime) {
    std::for_each( running.begin(), running.end(), ProgressFunctor(currTime) );
	return;
}
