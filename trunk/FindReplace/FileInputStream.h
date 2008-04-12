/*
 * FileInputStream.h
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */

#ifndef FILEINPUTSTREAM_H
#define FILEINPUTSTREAM_H

#include <map>
#include <vector>
#include <string>
#include "InputStream.h"


class FileInputStream : public InputStream {
private:
	bool	 E_O_F;
	unsigned currPos;		//ptr to vec
	Pos position;			//current coordinates
	std::string path;
	std::vector<char> vec;	//The file
	std::map<int, Pos> markPos;	//Marck coordinates if we call Marck()
	

public:
	bool Open (std::string path);
	bool Close (void);
	bool IsEof (void) const;
	char GetNext (void);
	bool Unput (void);
	bool Unmark (unsigned);

	

	
	unsigned	Mark (void);
	bool		Retract(unsigned);
	const Pos	GetPos (void) const { return position; }
	const std::string GetPath(void) const { return path; };
	

	FileInputStream(void);
	~FileInputStream(void);
};

#endif
