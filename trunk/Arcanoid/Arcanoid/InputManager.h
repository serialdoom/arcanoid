/*
 * author: koutsop
 */
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Sprite.h"
class InputManager {

public:

	void CheckInput(Sprite * sp);
	InputManager(void);
	~InputManager(void);
};

#endif