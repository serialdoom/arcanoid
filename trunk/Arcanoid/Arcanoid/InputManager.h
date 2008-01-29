/*
 * author: koutsop
 */
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

//#include "Animator.h"
#include "StateHolder.h"

class InputManager {
private:
	int oldMouseX, oldMouseY;

public:
	int GetOldMouseX(void) const { return oldMouseX; }
	int GetOldMouseY(void) const { return oldMouseY; }

	void SetOldMouseX(int dx) { oldMouseX = dx; }
	void SetOldMouseY(int dy) { oldMouseY = dy; }


	/* @target: Elegxei an uparxei kapoia eisodos apo tos keyboard h' to muse. An uparxei
	 *		  :tote 8etei thn katastasei tou StateHolder gia to key.
	 * @return: Ti eidos isodo exoume alios to Key_None.
	 */
	//KEY CheckInput(void);
	//bool CheckInput(Animator* anim);
	bool InputManager::CheckInput(void);
	
	InputManager(void);
	virtual ~InputManager(void){}
};

#endif