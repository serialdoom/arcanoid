/*
 * author: koutsop
 */

#ifndef LOADFILMSINFO_H
#define LOADFIMLSINFO_H

#include <map>
#include <string>
#include <cassert>

using std::map;
using std::string;
using std::make_pair;

typedef map< string, std::pair<string, string> > FilmsInfoMap;

class LoadFilmsInfo
{
private:
	FilmsInfoMap filmsInfo;
	int filmsNo;
	
	/* @target: Na diavazei ena config file
	 */
	void LoadInfo(void);

public:
	
	/* @return: Twn ari8mo twn films
	 */
	int GetFilmsNo(void) const { return filmsNo; }

	/* @return: Na epistrfei thn domh pou exoume fila3ei thn pliroforia gia ta films
	 */
	const FilmsInfoMap GetFilmsInfo(void) const { return filmsInfo; }
	
	//to path gia to config file me ta data giata films
	LoadFilmsInfo(const char* path);
	~LoadFilmsInfo(void);
};

#endif