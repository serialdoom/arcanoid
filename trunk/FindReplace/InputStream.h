/*
 * InputStream.h
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */

#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H


#include <string>


class InputStream{
public:

	struct Pos {
		unsigned row;
		unsigned col;
	};
	//********************************************************


	struct Block {
		Pos start;
		Pos end;
		std::string path;
	};
	//********************************************************

	virtual bool	Open (std::string path) = 0;
	virtual bool	Close (void) = 0;
	virtual bool	IsEof(void) const = 0;
	virtual char	GetNext() = 0;
	virtual bool	Unput(void) = 0;
	virtual bool	Unmark (unsigned) = 0;
	
	virtual unsigned	Mark (void) = 0;
	virtual bool		Retract(unsigned) = 0;
	virtual const Pos	GetPos (void) const = 0;
	virtual const std::string GetPath(void) const = 0;


	virtual ~InputStream(){}

	//virtual void	Bookmark(unsigned row) = 0;
	//virtual void	Select(int row1, int col1, int row2, int col2) = 0;
	//virtual Block	Replace(int row1, int col1, int row2, int col2) = 0;
};

#endif //INPUTSTREAM_H