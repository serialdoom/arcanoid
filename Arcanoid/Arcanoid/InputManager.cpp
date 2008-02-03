#include "InputManager.h"

#include <allegro.h>
#include <iostream>
#include "KeyLogger.h"
static bool lock = false;

InputManager::InputManager(void){
	oldMouseX = mouse_x;
	oldMouseY = mouse_y;
}
/////////////////////////////////////////////////////////////////////



static void presedPKey(){

	//Gia na katanalosoume to baffer tou keyboard
	if(lock) { StateHolder::stateKey.Key_P = false; return; }
	lock = true;
	StateHolder::stateKey.Key_P = true;
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
	StateHolder::stateKey.Key_Mouse_Left	= false;
	StateHolder::stateKey.Key_Mouse_Right	= false;
	StateHolder::stateKey.Key_A				= false;
	StateHolder::stateKey.Key_D				= false;
	return;
}
/////////////////////////////////////////////////////////////////////



bool InputManager::CheckInput(void){

	bool hasInput		= false;

	
	/*
	if (key[KEY_A])		{ StateHolder::stateKey.Key_A = true; hasInput = true; }
	else				{ StateHolder::stateKey.Key_A = false;}

	if (key[KEY_D])		{ StateHolder::stateKey.Key_D = true; hasInput = true; }
	else				{ StateHolder::stateKey.Key_D = false;}*/

	if (key[KEY_LEFT])	{ StateHolder::stateKey.Key_Left = true;  hasInput = true; }
	else				{ StateHolder::stateKey.Key_Left = false; }

	if (key[KEY_RIGHT])	{ StateHolder::stateKey.Key_Right = true;  hasInput = true; }
	else				{ StateHolder::stateKey.Key_Right = false;}

	if (key[KEY_F1])	{ StateHolder::stateKey.Key_F1 = true; }
	else				{ StateHolder::stateKey.Key_F1 = false; }

	if (key[KEY_P])		{ presedPKey(); hasInput = true; }
	else				{ StateHolder::stateKey.Key_P = false; lock = false;}

	if (oldMouseX != mouse_x){ oldMouseX = mouseMovedX(oldMouseX); hasInput = true;}
	if (!hasInput)		{ noneInput(); }	//None input
	
	return hasInput;
}