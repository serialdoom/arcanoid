/* StateHolder header file */

#ifndef __STATE_HOLDER_H__
#define __STATE_HOLDER_H__

class StateHolder {
	enum state {STATE_RUNNING, STATE_PAUSED, STATE_FINISHED};
	static state theState;

public:
	static void Init(void);
	static void Pause(void);
	static void Run(void);
	static void Finish(void);
	static bool isRunning(void);
	static bool isPaused(void);
	static bool isFinished(void);
};

#endif