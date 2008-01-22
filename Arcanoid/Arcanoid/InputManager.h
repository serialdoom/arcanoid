/*
 * author: koutsop
 */
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Animator.h"
class InputManager {
private:
	int oldMouseX, oldMouseY;

public:
	int GetOldMouseX(void) const { return oldMouseX; }
	int GetOldMouseY(void) const { return oldMouseY; }
	bool CheckInput(Animator* anim);
	InputManager(void);
	~InputManager(void);
};

#endif