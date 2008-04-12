#ifndef MYTEMPLATES_H
#define MYTEMPLATES_H

#include <string>

template<class T>
std::string lexical_cast(T a){
	std::ostringstream os;
	os<<a;
	return os.str();
}

#endif