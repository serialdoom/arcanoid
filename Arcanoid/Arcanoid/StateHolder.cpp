/*
 * author: koutsop
 */

/* StateHolder implementation file*/
#include "StateHolder.h"

KEY StateHolder::stateKey;
StateHolder::state_t StateHolder::theState;
StateHolder::boardstate_t StateHolder::boardState;


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
	theState					= STATE_RUNNING;
	return;
}
/////////////////////////////////////////////////////////////////////



bool StateHolder::IsRunning(void){
	return theState == STATE_RUNNING;
}
/////////////////////////////////////////////////////////////////////



bool StateHolder::IsPaused(void){
	return theState == STATE_PAUSED;
}
/////////////////////////////////////////////////////////////////////



bool StateHolder::IsFinished(void){
	return theState == STATE_FINISHED;
}
/////////////////////////////////////////////////////////////////////



bool StateHolder::IsGoLeft(void){
	return boardState == STATE_GO_LEFT;
}
/////////////////////////////////////////////////////////////////////



bool StateHolder::IsGoRight(void){
	return boardState == STATE_GO_RIGHT;
}
/////////////////////////////////////////////////////////////////////



bool StateHolder::IsStoped(void){
	return boardState == STATE_STOP;
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
/////////////////////////////////////////////////////////////////////



void StateHolder::GoLeft(void){
	boardState = STATE_GO_LEFT;
	return;
}
/////////////////////////////////////////////////////////////////////



void StateHolder::GoRight(void){
	boardState = STATE_GO_RIGHT;
	return;
}
/////////////////////////////////////////////////////////////////////



void StateHolder::Stop(void){
	boardState = STATE_STOP;
}
/////////////////////////////////////////////////////////////////////
