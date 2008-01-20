/*
 * author: koutsop
 */
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Animator.h"
class InputManager {

public:

	void CheckInput(Animator* anim,  timestamp_t t);
	InputManager(void);
	~InputManager(void);
};

#endif