#ifndef SEARCHANDREPLACEMANAGER_H
#define SEARCHANDREPLACEMANAGER_H

#include <list>
#include <vector>
#include <string>
#include <functional>

#include "RegExpr.h"
#include "RDParser.h"
#include "InputStream.h"
#include "LexicalAnalyser.h"


using namespace parser;

class SearchAndReplaceManager {
private:
	struct ClearFunctor : public std::unary_function<InputStream::Block *, void> {
		void operator()(const InputStream::Block * block) const {
			delete block;
			block = (InputStream::Block *)0;
		}
	};

	//variables
	//********************************************************
	bool		hasError;
	char *		errorMsg;
	std::list<InputStream *>  stream;


	//Find - Replace param
	bool		reg;
	long int	currFind;	//Kuklikh anazhthsh
	std::string	what;
	std::string with;
	


	//Analyser - Parsers
	RDParser *		find;
	RDParser *		replace;
	LexicalAnalyser analyser;
	
	//Results 
	std::vector<InputStream::Block *> results;


	//private functions
	//********************************************************
	void Clear(void);
	void SetError(char * msg);
	bool FindRegEx(RegExpr * e);
	bool Find ( RegExpr* e, InputStream& s, InputStream::Pos& from, InputStream::Pos& to );

	//used from FindNext(void)
	InputStream::Block * GetNext (void);
	InputStream::Block * GetPrev (void);
	unsigned  CalculatePos(void);

	
	

public:

	struct FindSettings{
		bool		isCaseSensitive;
		bool		searchUp;
		bool		wholeWord;
	}settings;


	//Ta arxeia sthn lista einai me thn shra pou 8a ginete h anazhthsh
	void	Set(std::list<InputStream *> & _stream)	{ stream = _stream; }

	bool	Find(void);
	bool	Replace( struct block area );	
	char*	GetError(void) { return errorMsg; }
	bool	HasError(void) { return hasError; }
	void	SetFindParam(std::string _what, bool _reg);
	void	SetReplaceParam(std::string _what, std::string _with, bool _reg);



	InputStream::Block * FindNext(void);




	//To delete after testing
	void	WriteResults( InputStream::Block * r);
	void	DumpResults(void);
	
	SearchAndReplaceManager(void);
	~SearchAndReplaceManager(void);
};


#endif

