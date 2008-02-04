/*
 * author: koutsop
 */
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

//#include "Animator.h"

typedef struct KEY {	
	bool Key_None; 
	bool Key_Left;
	bool Key_Right;
	bool Key_Up;
	bool Key_Down;
	bool Key_P;
	bool Key_Pause;
	bool Key_Mouse_Left;
	bool Key_Mouse_Right;
	bool Key_A;
	bool Key_D;
	bool Key_F1;
	bool Key_Space;
	bool Key_Enter;
}KEY;

class InputManager {
private:
	static int oldMouseX, oldMouseY;

public:
	static KEY inputKey;

	static int GetOldMouseX(void) { return oldMouseX; }
	static int GetOldMouseY(void) { return oldMouseY; }

	static void SetOldMouseX(int dx) { oldMouseX = dx; }
	static void SetOldMouseY(int dy) { oldMouseY = dy; }
	static void Clear(void);

	/* @target: Elegxei an uparxei kapoia eisodos apo tos keyboard h' to muse. An uparxei
	 *		  :tote 8etei thn katastasei tou StateHolder gia to key.
	 * @return: Ti eidos isodo exoume alios to Key_None.
	 */
	static bool CheckInput(void);

};

#endif