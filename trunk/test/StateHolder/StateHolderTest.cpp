/* Testing main for StateHolder class */


#include "StateHolder.h"
#include <iostream>

int main(){
	StateHolder::Init();

	std::cout << "0. Are you running ? " << StateHolder::isRunning() << std::endl;
	std::cout << "0. Are you paused ? " << StateHolder::isPaused() << std::endl;
	std::cout << "0. Are you finished ? " << StateHolder::isFinished() << std::endl;

	StateHolder::Run();
	std::cout << std::endl;

	std::cout << "1. Are you running ? " << StateHolder::isRunning() << std::endl;
	std::cout << "1. Are you paused ? " << StateHolder::isPaused() << std::endl;
	std::cout << "1. Are you finished ? " << StateHolder::isFinished() << std::endl;

	StateHolder::Finish();
	std::cout << std::endl;

	std::cout << "2. Are you running ? " << StateHolder::isRunning() << std::endl;
	std::cout << "2. Are you paused ? " << StateHolder::isPaused() << std::endl;
	std::cout << "2. Are you finished ? " << StateHolder::isFinished() << std::endl;

	system("pause");
	return 0;
}