/*
 * author: koutsop
 */
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Animator.h"
class InputManager {

public:

	void CheckInput(Animator* anim);
	InputManager(void);
	~InputManager(void);
};

#endif