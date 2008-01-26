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
				 }KEY;

class StateHolder {
	enum state  {
					STATE_RUNNING, 
					STATE_PAUSED, 
					STATE_FINISHED
				};
	static state	theState;

public:
	static KEY	stateKey;

	static void Init(void);
	static void Pause(void);
	static void Run(void);
	static void Finish(void);
	static bool isRunning(void);
	static bool isPaused(void);
	static bool isFinished(void);
};

#endif