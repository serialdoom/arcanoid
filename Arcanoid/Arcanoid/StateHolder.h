/*
 * author: koutsop
 */

/* StateHolder header file */

#ifndef STATE_HOLDER_H
#define STATE_HOLDER_H

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