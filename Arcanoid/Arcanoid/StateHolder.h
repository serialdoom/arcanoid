/* StateHolder header file */

#ifndef __STATE_HOLDER_H__
#define __STATE_HOLDER_H__

typedef enum Key	{
						Key_No		= -1, 
						Key_Left	= 0,
						Key_Right	= 1,
						Key_Up		= 2,
						Key_Down	= 3,
						Key_P		= 4,
						Key_Pause	= 5
					}Key;

class StateHolder {
	enum state  {
					STATE_RUNNING, 
					STATE_PAUSED, 
					STATE_FINISHED
				};
	static Key		theKey;
	static state	theState;

public:
	static void Init(void);
	static void Pause(void);
	static void Run(void);
	static void Finish(void);
	static bool isRunning(void);
	static bool isPaused(void);
	static bool isFinished(void);

	static void SetKey(Key _key) { theKey = _key; }
	static Key GetKey(void) { return theKey; }
};

#endif