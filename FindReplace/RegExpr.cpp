/*
 * RegExpr.cpp
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */

#include <ctype.h>
#include <assert.h>

#include "RegExpr.h"

#define MARK() unsigned marker = s.Mark()
#define FAIL() s.Retract(marker); return false




bool WhiteSpace_e::Match(InputStream &s) {
	MARK();
	char c[2] = { ' ', '\0' };
	l.clear();

	while (true) {	// (isspace)*
		c[0] = s.GetNext();
		if (isspace(c[0]) && !s.IsEof() )
			l.append(c);
		else
			break;
	}

	if ( !s.IsEof() ) { s.Unput(); } // Non-space returned back.
	if (l.compare("")!=0) return true;
	FAIL();
}
        

//////////////////////////////////////////////////////////////////////
bool DeltaIdent_e::Match(InputStream &s){
	MARK();
	l.clear();
	char c[2] = { s.GetNext(), '\0' };

	if (!s.IsEof() && isalpha(c[0])) { // letter(letter|digit)*
		while (true) {
			l.append(c);
			c[0] = s.GetNext();

			if (!s.IsEof() && isalnum(c[0]))
				l.append(c);
			else
				break;
		}
		if (!s.IsEof()) s.Unput();
		if (l.compare("")!=0) return true;
	}//end of while

	else { FAIL(); }
	return false;
}


//////////////////////////////////////////////////////////////////////
bool AnyChar_e::Match(InputStream &s) {
	char c[2] = { s.GetNext(), '\0' };
	
	if (!s.IsEof()){ 
		l = c; 
		return true; 
	}
	return false;
}


//////////////////////////////////////////////////////////////////////
bool String_e::Match(InputStream &s){
	MARK();
	std::string::iterator i;
	
	if ( text.begin() == text.end() ) { assert(0); }

	for (i = text.begin(); i != text.end() && !s.IsEof() && *i == s.GetNext(); ++i)
		;
	if (i == text.end())
		return true;
	
	FAIL();
}


//////////////////////////////////////////////////////////////////////
bool OR_e::Match(InputStream &s){
	MARK();
	l.clear();
	
	if (e1->Match(s)) 
		{ l = e1->Lexeme(); return true; }
	
	else if (e2->Match(s)) 
		{ l = e2->Lexeme(); return true; }

	FAIL();
}


//////////////////////////////////////////////////////////////////////
bool Concat_e::Match(InputStream &s){
	MARK();
	l.clear();
	if (e1->Match(s)) {	
		l.append(e1->Lexeme());
		if (e2->Match(s)) { 
			l.append(e2->Lexeme()); 
			return true; 
		}//second if
	}//first if
	FAIL();
}


//////////////////////////////////////////////////////////////////////
bool Tag_e::Match(InputStream &s){
	MARK();
	if (e->Match(s)) {
		// produce 'Lexeme' from marked to current
		return true;
	}
	FAIL();
}



//////////////////////////////////////////////////////////////////////
bool ZeroOrMore_e::Match(InputStream &s){
	while(e->Match(s)){
		l.append( e->Lexeme() );
	}
	return l.compare("") != 0;
}