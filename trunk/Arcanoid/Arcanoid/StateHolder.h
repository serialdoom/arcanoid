/*
 * author: koutsop
 */

/* StateHolder header file */

#ifndef __STATE_HOLDER_H__
#define __STATE_HOLDER_H__

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

class StateHolder {
	typedef enum state  {
		STATE_RUNNING	= 0, 
		STATE_PAUSED	= 1,	
		STATE_FINISHED	= 2,
	}state_t;

	typedef enum boardState {
		STATE_GO_LEFT	= 0,
		STATE_GO_RIGHT	= 1,
		STATE_STOP		= 2
	}boardstate_t;

	static state_t		theState;
	static boardstate_t boardState;
public:
	static KEY	stateKey;
	
	static void Run(void);
	static void Stop(void);
	static void Init(void);
	static void Pause(void);
	static void GoLeft(void);
	static void Finish(void);
	static void GoRight(void);
	static bool IsStoped(void);
	static bool IsPaused(void);
	static bool IsGoLeft(void);
	static bool IsRunning(void);
	static bool IsGoRight(void);
	static bool IsFinished(void);

};

#endif