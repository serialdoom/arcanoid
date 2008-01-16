/*
 *author: koutsop
 */
#ifndef ANIMATORHOLDER_H
#define ANIMATORHOLDER_H


#include <list>
#include <algorithm>
#include "Animator.h"

class AnimatorHolder {

private:
	static std::list<Animator*> running, suspended;

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
};

#endif