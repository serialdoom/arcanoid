/*
 *author: koutsop
 */
#include "AnimatorHolder.h"
#include <iostream>

unsigned long AnimatorHolder::startPauseTime;
std::list<Animator*> AnimatorHolder::paused;
std::list<Animator*> AnimatorHolder::running;
std::list<Animator*> AnimatorHolder::suspended;

/////////////////////////////////////////////////////////////////////



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
/////////////////////////////////////////////////////////////////////


void AnimatorHolder::Clear(void){
	paused.clear();
	running.clear();
	suspended.clear();
}

void AnimatorHolder::Pause(void){
	startPauseTime = time( (time_t *)0 );
	std::list<Animator*>::iterator start	= running.begin();
	std::list<Animator*>::iterator end		= running.end();

	while(start!=end){
		Animator * a = (*start);
		start++;
		running.remove(a);
		paused.push_back(a);
	}
	return;
}

void AnimatorHolder::Resum(void){
	unsigned long pauseTime = time( (time_t *)0 ) - startPauseTime;
	std::list<Animator*>::iterator start	= paused.begin();
	std::list<Animator*>::iterator end		= paused.end();

	while(start!=end){
		Animator *a = (*start);
		start++;
		a->TimeShift(pauseTime);
		paused.remove(a);
		running.push_back(a);
	}
	return;
}

