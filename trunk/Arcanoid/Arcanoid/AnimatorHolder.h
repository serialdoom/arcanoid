/*
 *author: koutsop
 */
#ifndef ANIMATORHOLDER_H
#define ANIMATORHOLDER_H

//TODO na sbisw thn print size

#include <list>
#include <algorithm>


#include "MyTime.h"
#include "Animator.h"
#include "KeyLogger.h"

class AnimatorHolder {

private:
	static timestamp_t startPauseTime;
	static std::list<Animator*> running, suspended, paused;

	class ProgressFunctor : public std::unary_function<Animator*, void> {
	private:	
		timestamp_t t;
	public: 
	    void operator()(Animator* a) const { a->Progress(t); }
	    ProgressFunctor (timestamp_t _t) : t(_t){}
	};

public:
	
	static void Register(Animator* a);
	
	static void Cancel(Animator* a);
	
	static void MarkAsRunning (Animator* a);
	
	static void MarkAsSuspended (Animator* a);
	
	static void Progress (timestamp_t currTime);

	static void Pause(void);

	static void Resum(void);

	static void Clear(void);
	
	//debug skopous
	static void printSize(void){
		KeyLogger::Write("paused size: %d\n", paused.size());
		KeyLogger::Write("running size: %d\n", running.size());
		KeyLogger::Write("suspended size: %d\n\n\n", suspended.size());
	}
};

#endif