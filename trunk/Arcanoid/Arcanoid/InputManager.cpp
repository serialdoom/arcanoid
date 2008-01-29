#include "InputManager.h"

#include <allegro.h>
InputManager::InputManager(void){
	oldMouseX = mouse_x;
	oldMouseY = mouse_y;
}
/////////////////////////////////////////////////////////////////////



static void pressedAButton(void){
	StateHolder::stateKey.Key_A = true; 
	StateHolder::GoLeft();
	return;
}
/////////////////////////////////////////////////////////////////////



static void pressedDButton(void){
	StateHolder::stateKey.Key_D = true; 
	StateHolder::GoRight();
	return;
}
/////////////////////////////////////////////////////////////////////



static void pressedLeftButton(void){
	StateHolder::stateKey.Key_Left = true; 
	StateHolder::GoLeft();
	return;
}
/////////////////////////////////////////////////////////////////////



static void pressedRightButton(void){
	StateHolder::stateKey.Key_Right = true; 
	StateHolder::GoRight();
	return;
}
/////////////////////////////////////////////////////////////////////



static void presedPKey(){
	if( StateHolder::IsRunning() ){
		StateHolder::Pause();
		StateHolder::stateKey.Key_P = true;
	}
	
	else{
		StateHolder::Run();
		StateHolder::stateKey.Key_P = false;
	}
	StateHolder::Stop();
	return;
}
/////////////////////////////////////////////////////////////////////



static void presedPauseKey(){
	if( StateHolder::IsRunning() ){
		StateHolder::Pause();
		StateHolder::stateKey.Key_Pause = true;
	}

	else{
		StateHolder::Run();
		StateHolder::stateKey.Key_Pause = false;
	}
	StateHolder::Stop();	
	return;
}
/////////////////////////////////////////////////////////////////////



static int mouseMovedX(int oldMouseX){
	if( oldMouseX - mouse_x <= 0){			//mouse moved right
		StateHolder::GoRight();
		StateHolder::stateKey.Key_Mouse_Right = true;
	}
	else{									//mouse moved left
		StateHolder::GoLeft();
		StateHolder::stateKey.Key_Mouse_Left = true;
	}
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
	
	StateHolder::Stop();
	return;
}
/////////////////////////////////////////////////////////////////////



bool InputManager::CheckInput(void){

	bool hasInput = false;

	if (key[KEY_A])		{ pressedAButton(); hasInput = true; }
	else				{ StateHolder::stateKey.Key_A = false;}

	if (key[KEY_D])		{ pressedDButton(); hasInput = true; }
	else				{ StateHolder::stateKey.Key_D = false;}

	if (key[KEY_LEFT])	{ pressedLeftButton(); hasInput = true; }
	else				{ StateHolder::stateKey.Key_Left = false; }

	if (key[KEY_RIGHT])	{ pressedRightButton(); hasInput = true; }
	else				{ StateHolder::stateKey.Key_Right = false;}

	if (key[KEY_P])		{ presedPKey(); hasInput = true; }
	if (key[KEY_PAUSE])	{ presedPauseKey(); hasInput = true; }
	if (oldMouseX != mouse_x){ oldMouseX = mouseMovedX(oldMouseX); hasInput = true;}
	if (!hasInput)		{ noneInput(); }	//None input
	
	return hasInput;
}