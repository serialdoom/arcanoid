/*
 * RDParserFindReplace.cpp
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */

/*	Old Grammar
 *	Regex:	'\' Num Regex
 *		|	String Regex
 *		|	DeltaId
 *		|	WhtiteSpace
 *		|	AnyChar
 *		|	epsilon
 *		;
 */

/*	New Grammar
 *	Regex: Reg 
 *		;
 *	
 *	Reg:	Regs Reg 
 *		|	epsilon
 *		;
 *
 *	Reg:	'\' Num Reg
 *		|	String Reg
 *		|	DeltaId
 *		|	WhtiteSpace
 *		|	AnyChar
 *		;
 */


#include <assert.h>
#include <iostream>
#include <algorithm>
#include "RDParserFindReplace.h"

#define MARK()	TokenList::iterator t = marck_input_position();
#define FALL()	retruct_input_till_position(t); return false;
#define EPSILON true


parser::RDParserFindReplace::RDParserFindReplace(void){}

parser::RDParserFindReplace::~RDParserFindReplace(void){
	Clear();
}


//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFindReplace::Analyse (TokenList* _tokens) {
	assert(_tokens);
	tokens				= _tokens;
	tokenListIter		= tokens->begin();
	return Regex();
}



//////////////////////////////////////////////////////////////////////
void parser::RDParserFindReplace::Clear(void){
	std::for_each(toDelete.begin(), toDelete.end(), ClearFunctor());
}


//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFindReplace::Regex(void){
	MARK();
	RegExpr * e;
/*
	if( e = Reg() ){
		if ( GetNextToken() == TokenEOF )
			return e;
		else
			return (RegExpr *)0;
	}
	*/
	FALL();
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFindReplace::Reg(void){
	MARK();
/*	RegExpr * e  = (RegExpr *)0;
	RegExpr * e1 = (RegExpr *)0;
	RegExpr * e2 = (RegExpr *)0;

	if( ( (e1 = Regs()) && (e2 = Reg()) ) || ( e = Epsilon()) ){
		
		if( dynamic_cast<Epsilon_e *>(e) )	{ 
			if(e1) { delete e1; }
			return e; 
		}	
		else {
			Concat_e * concat = new Concat_e();
			concat->e1 = e1;
			concat->e2 = e2;
			return concat;
		}
	}*/
	FALL();
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFindReplace::Regs(void){
	MARK();
/*	RegExpr * e;

	if( ( e = BackslashNum() )	||
		( e = String() )		||
		( e = AnyCharacter() )	||
		( e = DeltaId()	)		||
		( e = WhiteSpace() ) )
	{
		toDelete.push_back(e);
		return e;
	}*/
	FALL();
}


//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFindReplace::BackslashNum(void){
	MARK();
	/*if( Match(TokenBACKSLASH)	&& 
		Match(TokenNUM)			&& 
		Reg() )
	{
		return new Epsilon_e();
	}*/
	FALL();
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFindReplace::String(void){
	MARK();
	/*if( Match(TokenREGEX_STRING) ){
		String_e * str = new String_e();
		str->text = currToken.value.strVal;
		return str;
	}*/
	FALL();
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFindReplace::DeltaId(void){
	MARK();
	/*if( Match(TokenDELTA_ID) ){
		return new DeltaIdent_e();
	}*/
	FALL();
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFindReplace::AnyCharacter(void){
	MARK();
	/*if( Match(TokenANY_CHARACTER) ){
		return new AnyChar_e();
	}*/
	FALL();
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFindReplace::WhiteSpace(void){
	MARK();
	/*if( Match(TokenWHITE_SPACE) ){
		return new WhiteSpace_e();
	}*/
	FALL();
}


//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFindReplace::Epsilon(void){
	return new Epsilon_e();
}