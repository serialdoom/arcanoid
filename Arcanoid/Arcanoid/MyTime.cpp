#include "MyTime.h"

#include <ctime>

timestamp_t MyTime::currTime;


void MyTime::SetGameTime(void) { 
	currTime = clock(); 
}


timestamp_t MyTime::GetGameTime(void){ 
	return currTime; 
}


timestamp_t MyTime::GetSystemTime(void){ 
	return clock(); 
}

timestamp_t MyTime::GetSystemDiffTimeInSec(timestamp_t time1, timestamp_t time2){
	return (time1-time2)/CLOCKS_PER_SEC;
}


timestamp_t MyTime::GetSystemDiffTime(timestamp_t time1, timestamp_t time2){
	return (time1-time2);
}
