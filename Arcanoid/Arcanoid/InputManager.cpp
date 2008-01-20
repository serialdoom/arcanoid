#include "InputManager.h"
#include <allegro.h>
#include <iostream>
#include "StateHolder.h"

InputManager::InputManager(void)
{
}

InputManager::~InputManager(void)
{
}

/////////////////////////////////////////////////////////////////////

static void presedLeftKey(Animator* anim,  timestamp_t t){
	StateHolder::SetKey(Key_Left);
	anim->Progress(t);
	return;
}

/////////////////////////////////////////////////////////////////////

static void presedRightKey(Animator* anim,  timestamp_t t){
	StateHolder::SetKey(Key_Right);
	anim->Progress(t);
	return;
}

/////////////////////////////////////////////////////////////////////

static void presedPKey(Animator* anim,  timestamp_t t){

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

static void prededPauseKey(Animator* anim,  timestamp_t t){

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

void InputManager::CheckInput(Animator* anim,  timestamp_t t){
	
	if		( key[KEY_LEFT] )	{ presedLeftKey(anim, t); }
	else if	( key[KEY_RIGHT] )	{ presedRightKey(anim, t); }
	else if	( key[KEY_P] )		{ presedPKey(anim, t); }
	else if	( key[KEY_PAUSE])	{ prededPauseKey(anim, t); }
	return;
}
