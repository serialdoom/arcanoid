/*
 * author: koutsop
 */

#ifndef LOADFILMSINFO_H
#define LOADFIMLSINFO_H

#include <map>
#include <cassert>
using std::map;
using std::string;


class LoadFilmsInfo
{
private:
	typedef map<string, map<string, string>> FilmsMap;
	FilmsMap filmsMap;
	int filmsNo;
	
	void LoadInfo(void);

public:
	//to path gia to config file me ta data giata films
	LoadFilmsInfo(const char* path);
	~LoadFilmsInfo(void);
};

#endif