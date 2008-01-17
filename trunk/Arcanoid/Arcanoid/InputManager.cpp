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

static void presedLeftKey(Sprite* sp){
	StateHolder::SetKey(Key_Left);
	sp->Move(0,0);
	return;
}

/////////////////////////////////////////////////////////////////////

static void presedRightKey(Sprite* sp){
	StateHolder::SetKey(Key_Right);
	sp->Move(0,0);
	return;
}

/////////////////////////////////////////////////////////////////////

static void presedPKey(Sprite* sp){

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

static void prededPauseKey(Sprite* sp){

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

void InputManager::CheckInput(Sprite* sp){
	
	if		( key[KEY_LEFT] )	{ presedLeftKey(sp); }
	else if	( key[KEY_RIGHT] )	{ presedRightKey(sp); }
	else if	( key[KEY_P] )		{ presedPKey(sp); }
	else if	( key[KEY_PAUSE])	{ prededPauseKey(sp); }
	return;
}
