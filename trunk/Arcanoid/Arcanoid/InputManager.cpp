#include "InputManager.h"
#include <allegro.h>
#include <iostream>
#include "StateHolder.h"
#include "AnimatorHolder.h"

InputManager::InputManager(void)
{
}

InputManager::~InputManager(void)
{
}

/////////////////////////////////////////////////////////////////////

static void presedLeftKey(Animator* anim){
	StateHolder::SetKey(Key_Left);
	AnimatorHolder::MarkAsRunning(anim);
	return;
}

/////////////////////////////////////////////////////////////////////

static void presedRightKey(Animator* anim){
	StateHolder::SetKey(Key_Right);
	AnimatorHolder::MarkAsRunning(anim);
	return;
}

/////////////////////////////////////////////////////////////////////

static void presedPKey(Animator* anim){

	if( StateHolder::isRunning() ){
		StateHolder::SetKey(Key_P);
		StateHolder::Pause();
	}
	else{
		StateHolder::SetKey(Key_P);
		StateHolder::Run();
	}
	return;
}

/////////////////////////////////////////////////////////////////////

static void prededPauseKey(Animator* anim){

	if( StateHolder::isRunning() ){
		StateHolder::SetKey(Key_Pause);
		StateHolder::Pause();
	}
	else{
		StateHolder::SetKey(Key_Pause);
		StateHolder::Run();
	}
	return;
}

/////////////////////////////////////////////////////////////////////

void InputManager::CheckInput(Animator* anim){
	
	bool hasInput = false;

	if		( key[KEY_LEFT] )	{ presedLeftKey(anim);	hasInput = true;}
	else if	( key[KEY_RIGHT] )	{ presedRightKey(anim);	hasInput = true; }
	else if	( key[KEY_P] )		{ presedPKey(anim);		hasInput = true; }
	else if	( key[KEY_PAUSE])	{ prededPauseKey(anim); hasInput = true; }
	
	if( !hasInput )
		AnimatorHolder::MarkAsSuspended(anim);

	return;
}
