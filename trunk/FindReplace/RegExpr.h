/*
 * RegExpr.h
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */

#ifndef REGEXPR_H
#define REGEXPR_H

#include <vector>
#include <string>
#include "InputStream.h"

struct RegExpr {
	virtual bool Match (InputStream& ) = 0;
	virtual const std::string Lexeme (void) const = 0;
	virtual const std::string ToString(void) const = 0;
};



//********************************************************
struct WhiteSpace_e : public RegExpr { // Logic hard-coding.
	std::string l;
	bool Match (InputStream& s);
	const std::string Lexeme (void) const { return l; }
	const std::string ToString(void) const { return "WhiteSpace_e"; }
};



//********************************************************
struct DeltaIdent_e : public RegExpr { // a Delta identifier, logic hard-coding style
	std::string l;
	bool Match (InputStream& s);
	const std::string Lexeme (void) const { return l; }
	const std::string ToString(void) const { return "DeltaIdent_e"; }
};



//********************************************************
struct AnyChar_e : public RegExpr { // ? macthes any character (except EOF).
	std::string l;
	bool Match (InputStream& s);
	const std::string Lexeme (void) const { return l; }
	const std::string ToString(void) const { return "AnyChar_e"; }
};



//********************************************************
struct String_e : public RegExpr {
	std::string text;	// to  Match against
	bool Match (InputStream& s);
	const std::string Lexeme (void) const { return text; }
	const std::string ToString(void) const { return "String_e"; }
};



//********************************************************
struct OR_e : public RegExpr {
	RegExpr* e1;
	RegExpr* e2;
	std::string l;
	bool Match (InputStream& s);
	const std::string Lexeme (void) const { return l; }
	const std::string ToString(void) const { return "OR_e";}

	OR_e(void){
		e1 = (RegExpr*)0;
		e2 = (RegExpr*)0;
	}
};



//********************************************************
struct Concat_e : public RegExpr {
	RegExpr* e1;
	RegExpr* e2;
	std::string l;
	bool Match (InputStream& s);
	const std::string Lexeme (void) const { return l; }
	const std::string ToString(void) const { return "Concat_e"; }

	Concat_e(void){
		e1 = (RegExpr*)0;
		e2 = (RegExpr*)0;
	}
};



//********************************************************
struct Tag_e : public RegExpr {
	RegExpr* e;
	bool Match (InputStream& s);
	const std::string Lexeme (void) const { return e->Lexeme(); }
	const std::string ToString(void) const { return "Tag_e"; }

	Tag_e(void){ 
		e = (RegExpr*)0; 
	}
};




//********************************************************
struct ZeroOrMore_e : public RegExpr {
	RegExpr* e;
	std::string l;
	bool Match (InputStream& s);
	const std::string Lexeme (void) const { return l; }
	const std::string ToString(void) const { return "ZeroOrMore_e"; }

	ZeroOrMore_e(void){ 
		e = (RegExpr*)0;
		l = "";
	}
};




//********************************************************
struct Epsilon_e : public RegExpr {
	bool Match(InputStream& s){ return true; }
	const std::string Lexeme (void) const { return ""; }
	const std::string ToString(void) const { return "Epsilon_e"; }
};


#endif