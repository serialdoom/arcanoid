#include "InputManager.h"
#include <allegro.h>
#include <iostream>
#include "StateHolder.h"
#include "AnimatorHolder.h"

InputManager::InputManager(void){
	oldMouseX = mouse_x;
	oldMouseY = mouse_y;
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

static void presedPauseKey(Animator* anim){

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

static int mouseMovedX(Animator* anim, int oldMouseX){
	if( oldMouseX - mouse_x <= 0)			//mouse moved right
		StateHolder::SetKey(Key_Mouse_Right);
	else									//mouse moved left
		StateHolder::SetKey(Key_Mouse_Left);
	
	AnimatorHolder::MarkAsRunning(anim);
	return mouse_x;
}

/////////////////////////////////////////////////////////////////////

bool InputManager::CheckInput(Animator* anim){

	bool hasInput = false;

	if		( key[KEY_LEFT] )	{ presedLeftKey(anim);	hasInput = true;}
	else if	( key[KEY_RIGHT] )	{ presedRightKey(anim);	hasInput = true; }
	else if	( key[KEY_P] )		{ presedPKey(anim);		hasInput = true; }
	else if	( key[KEY_PAUSE])	{ presedPauseKey(anim); hasInput = true; }
	else if ( oldMouseX != mouse_x ){oldMouseX = mouseMovedX(anim, oldMouseX); hasInput = true;}
	
	if( !hasInput )
		AnimatorHolder::MarkAsSuspended(anim);

	return hasInput;
}
