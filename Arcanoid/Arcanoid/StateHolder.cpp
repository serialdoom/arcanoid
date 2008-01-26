/* StateHolder implementation file*/

#include "StateHolder.h"

KEY StateHolder::stateKey;
StateHolder::state StateHolder::theState;

void StateHolder::Init(void){
	stateKey.Key_None			= true; 
	stateKey.Key_Left			= false;
	stateKey.Key_Right			= false;
	stateKey.Key_Up				= false;
	stateKey.Key_Down			= false;
	stateKey.Key_P				= false;
	stateKey.Key_Pause			= false;
	stateKey.Key_Mouse_Left		= false;
	stateKey.Key_Mouse_Right	= false;
	stateKey.Key_A				= false;
	stateKey.Key_D				= false;
	theState					= STATE_PAUSED;
	return;
}
/////////////////////////////////////////////////////////////////////



bool StateHolder::isRunning(void){
	return theState == STATE_RUNNING;
}
/////////////////////////////////////////////////////////////////////



bool StateHolder::isPaused(void){
	return theState == STATE_PAUSED;
}
/////////////////////////////////////////////////////////////////////



bool StateHolder::isFinished(void){
	return theState == STATE_FINISHED;
}
/////////////////////////////////////////////////////////////////////



void StateHolder::Pause(void){
	theState = STATE_PAUSED;
	return;
}
/////////////////////////////////////////////////////////////////////



void StateHolder::Run(void){
	theState = STATE_RUNNING;
	return;
}
/////////////////////////////////////////////////////////////////////



void StateHolder::Finish(void){
	theState = STATE_FINISHED;
	return;
}