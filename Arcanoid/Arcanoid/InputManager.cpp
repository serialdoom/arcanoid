#include "InputManager.h"

#include <allegro.h>
#include <iostream>
#include "KeyLogger.h"
static bool lock = false;

KEY InputManager::inputKey;
int InputManager::oldMouseX;
int InputManager::oldMouseY;


/////////////////////////////////////////////////////////////////////



static void presedPKey(){
	
	//Gia na katanalosoume to baffer tou keyboard
	if(lock) { InputManager::inputKey.Key_P = false; return; }
	lock = true;
	InputManager::inputKey.Key_P = true;
}
/////////////////////////////////////////////////////////////////////



static int mouseMovedX(int oldMouseX){
	if( oldMouseX - mouse_x <= 0){ 
		InputManager::inputKey.Key_Mouse_Right = true; 
	}	//mouse moved right
	
	else{ 
		InputManager::inputKey.Key_Mouse_Left = true;
	}	//mouse moved left
	return mouse_x;
}


/////////////////////////////////////////////////////////////////////



bool InputManager::CheckInput(void){

	bool hasInput		= false;

	if (key[KEY_A])		{ inputKey.Key_A = true; hasInput = true; }
	else				{ inputKey.Key_A = false;}

	if (key[KEY_D])		{ inputKey.Key_D = true; hasInput = true; }
	else				{ inputKey.Key_D = false;}

	if (key[KEY_ENTER])	{ inputKey.Key_Enter = true;  hasInput = true;}
	else				{ inputKey.Key_Enter = false;}

	if (key[KEY_SPACE])	{ inputKey.Key_Space = true;  hasInput = true;}
	else				{ inputKey.Key_Space = false;}

	if (key[KEY_LEFT])	{ inputKey.Key_Left = true;  hasInput = true; }
	else				{ inputKey.Key_Left = false; }

	if (key[KEY_RIGHT])	{ inputKey.Key_Right = true;  hasInput = true; }
	else				{ inputKey.Key_Right = false;}

	if (key[KEY_F1])	{ inputKey.Key_F1 = true; }
	else				{ inputKey.Key_F1 = false; }

	if (key[KEY_P])		{ presedPKey(); hasInput = true; }
	else				{ inputKey.Key_P = false; lock = false;}

	if (oldMouseX != mouse_x){ oldMouseX = mouseMovedX(oldMouseX); hasInput = true;}
	if (!hasInput)		{ Clear(); }	//None input
	
	return hasInput;
}


void InputManager::Clear(void){
	inputKey.Key_None			= true; 
	inputKey.Key_Left			= false;
	inputKey.Key_Right			= false;
	inputKey.Key_Up				= false;
	inputKey.Key_Down			= false;
	inputKey.Key_P				= false;
	inputKey.Key_Pause			= false;
	inputKey.Key_Mouse_Left		= false;
	inputKey.Key_Mouse_Right	= false;
	inputKey.Key_A				= false;
	inputKey.Key_D				= false;
	inputKey.Key_F1				= false;
	inputKey.Key_Space			= false;
	inputKey.Key_Enter			= false;
	return;
}
