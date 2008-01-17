/* StateHolder implementation file*/

#include "StateHolder.h"

Key StateHolder::theKey;
StateHolder::state StateHolder::theState;

void StateHolder::Init(void){
	theKey		 = Key_No; 
	theState	 = STATE_PAUSED;
	return;
}

bool StateHolder::isRunning(void){
	return theState == STATE_RUNNING;
}

bool StateHolder::isPaused(void){
	return theState == STATE_PAUSED;
}

bool StateHolder::isFinished(void){
	return theState == STATE_FINISHED;
}

void StateHolder::Pause(void){
	theState = STATE_PAUSED;
	return;
}

void StateHolder::Run(void){
	theState = STATE_RUNNING;
	return;
}

void StateHolder::Finish(void){
	theState = STATE_FINISHED;
	return;
}