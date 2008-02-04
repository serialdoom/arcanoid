/*
 * author: koutsop
 */

#ifndef MYTIME_H
#define MYTIME_H

#include "Animator.h"

class MyTime{
private:
	static timestamp_t currTime;

public:
	static void SetGameTime(void);
	static timestamp_t GetGameTime(void);
	static timestamp_t GetSystemTime(void);

	/* @target: Na aferei apo to time1 to time2
	 * @parma : time1 ton prwto xrono, time2 ton deutero xrono
	 * @return: Thn diafora tou time1 me to time2 se sec
	 * @precoditions: Prepei time1 >= time2
	 */
	static timestamp_t GetSystemDiffTimeInSec(timestamp_t time1, timestamp_t time2);

	/* @target: Na aferei apo to time1 to time2
	 * @parma : time1 ton prwto xrono, time2 ton deutero xrono
	 * @return: Thn diafora tou time1 me to time2 se msec
	 * @precoditions: Prepei time1 >= time2
	 */
	static timestamp_t GetSystemDiffTime(timestamp_t time1, timestamp_t time2);

};
#endif