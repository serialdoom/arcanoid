/*
 * author: koutsop
 */

#ifndef LOADFIMLSINFO_H
#define LOADFIMLSINFO_H

#include <map>
#include <string>
#include <cassert>

using std::map;
using std::string;
using std::make_pair;

//to prwto string einai to id
//to deutero string einai to onoma tou arxeiou pou exei to bboxe gia auto to film
//to trito string einai to path gia to bitmap
typedef map< string, std::pair<string, string> > FilmsInfoMap;

class LoadFilmsInfo
{
private:
	int filmsNo;
	string filmIdentifire;			//Mas leei pos 8a 3exwrizoume ta apla bitmap apo ta film
	FilmsInfoMap filmsInfo;
	
	
	
	/* @target: Na diavazei ena config file
	 */
	void LoadInfo(void);

public:
	
	/* @target: Epistrefei to anagnwristiko gia an ena bitmap einai film h' oxi
	 */
	const string GetIdentifire(void) const { return filmIdentifire; } 

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