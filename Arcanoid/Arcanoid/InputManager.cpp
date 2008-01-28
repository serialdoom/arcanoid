#include "InputManager.h"

#include <allegro.h>
InputManager::InputManager(void){
	oldMouseX = mouse_x;
	oldMouseY = mouse_y;
}
/////////////////////////////////////////////////////////////////////



static void presedPKey(){
	if( StateHolder::isRunning() ){
		StateHolder::Pause();
		StateHolder::stateKey.Key_P = true;
	}
	
	else{
		StateHolder::Run();
		StateHolder::stateKey.Key_P = false;
	}
	
	return;
}
/////////////////////////////////////////////////////////////////////



static void presedPauseKey(){
	if( StateHolder::isRunning() ){
		StateHolder::Pause();
		StateHolder::stateKey.Key_Pause = true;
	}

	else{
		StateHolder::Run();
		StateHolder::stateKey.Key_Pause = false;
	}
	
	
	return;
}
/////////////////////////////////////////////////////////////////////



static int mouseMovedX(int oldMouseX){
	if( oldMouseX - mouse_x <= 0)			//mouse moved right
		StateHolder::stateKey.Key_Mouse_Right = true;
	else									//mouse moved left
		StateHolder::stateKey.Key_Mouse_Left = true;
	return mouse_x;
}


/////////////////////////////////////////////////////////////////////



void noneInput(void){
	StateHolder::stateKey.Key_None			= true; 
	StateHolder::stateKey.Key_Left			= false;
	StateHolder::stateKey.Key_Right			= false;
	StateHolder::stateKey.Key_Up			= false;
	StateHolder::stateKey.Key_Down			= false;
	StateHolder::stateKey.Key_P				= false;
	StateHolder::stateKey.Key_Pause			= false;
	StateHolder::stateKey.Key_Mouse_Left	= false;
	StateHolder::stateKey.Key_Mouse_Right	= false;
	StateHolder::stateKey.Key_A				= false;
	StateHolder::stateKey.Key_D				= false;
	
	return;
}
/////////////////////////////////////////////////////////////////////



bool InputManager::CheckInput(void){

	bool hasInput = false;

	if (key[KEY_A])		{ StateHolder::stateKey.Key_A = true; hasInput = true; }
	else				{ StateHolder::stateKey.Key_A = false; }

	if (key[KEY_D])		{ StateHolder::stateKey.Key_D = true; hasInput = true; }
	else				{ StateHolder::stateKey.Key_D = false; }

	if (key[KEY_LEFT])  { StateHolder::stateKey.Key_Left = true; hasInput = true;}
	else				{ StateHolder::stateKey.Key_Left = false; }

	if (key[KEY_RIGHT])	{ StateHolder::stateKey.Key_Right = true; hasInput = true; }
	else				{ StateHolder::stateKey.Key_Right = false; }

	if (key[KEY_P])		{ presedPKey(); hasInput = true; }
	if (key[KEY_PAUSE])	{ presedPauseKey(); hasInput = true; }
	if (oldMouseX != mouse_x){ oldMouseX = mouseMovedX(oldMouseX); hasInput = true;}
	if (!hasInput)		{ noneInput(); }	//None input
	
	return hasInput;
}