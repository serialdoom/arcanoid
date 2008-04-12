/*
 * RDPParserFind.cpp
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */

/*	Grammar
 *	Regex:	Regexs Regex 
 *		|	epsilon
 *		;
 *
 *	Regexs:	'{' Regex '}'
 *		|	'(' Regex ')' '*'
 *		|	'<' Regex | Regex '>'
 *		|	String
 *		|	DeltaId
 *		|	WhtiteSpace
 *		|	AnyChar
 *		|	Num //Like string
 *		;
 */


#include <assert.h>
#include <iostream>
#include <algorithm>

#include "MyTemplates.h"
#include "RDParserFind.h"


//#define MARK()	TokenList::iterator t = marck_input_position();
//#define FALL()	retruct_input_till_position(t); return (RegExpr *)0;



parser::RDParserFind::RDParserFind(){
	hasError		= false;
	lookAhead.type	= TokenSTART_SYMBOL;
}

parser::RDParserFind::~RDParserFind(void){
	Clear();
}
//////////////////////////////////////////////////////////////////////
void parser::RDParserFind::Clear(void){
	hasError = false;
	std::for_each(toDelete.begin(), toDelete.end(), ClearFunctor());
	toDelete.clear();
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::Analyse (TokenList* _tokens) {
	assert(_tokens);
	tokens				= _tokens;
	tokenListIter		= tokens->begin();
	Match(TokenSTART_SYMBOL);
	RegExpr * tmp = Regex();

	if( !dynamic_cast<Epsilon_e *>(tmp) && //To e einai la8os
		!HasError()						&&
		(lookAhead == TokenEOF) )

	{
		return tmp;
	}
	else
		return (RegExpr *)0;
}



//Grammar implementation
//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::Regex(void){
	RegExpr * e  = (RegExpr *)0;
	RegExpr * e1 = (RegExpr *)0;
	RegExpr * e2 = (RegExpr *)0;

	if( ( (e1 = Regexs()) && (e2 = Regex()) ) || ( e = Epsilon()) ){		
		if( e1 && e2 ){
			Concat_e * concat = new Concat_e();
			concat->e1 = e1;
			concat->e2 = e2;
			return concat;
		}
		else{
			if(e1) { delete e1; }				//petixe to e1 alla oxi to e2
			return e; 
		}
	}
	return (RegExpr *)0;
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::Regexs(void){
	RegExpr * e = (RegExpr *)0;

	if( lookAhead == TokenLEFT_PARENTHESIS ){
		e = ZeroOrMore();
	}
	else if( lookAhead == TokenLEFT_CURLY_BRACE ){
		e = Tag();
	}

	else if( lookAhead == TokenLESS_THAN ){
		e = OR();
	}

	else if( lookAhead == TokenREGEX_STRING ){
		e = String();
	}

	else if( lookAhead == TokenANY_CHARACTER ){
		e = AnyCharacter();
	}

	else if( lookAhead == TokenDELTA_ID ){
		e = DeltaId();
	}

	else if( lookAhead == TokenWHITE_SPACE ){
		e = WhiteSpace();
	}

	else if( lookAhead == TokenNUM ){
		e = Number();
	}
	

	if( e ){
		toDelete.push_back(e);
		return e;
	}

	return (RegExpr *)0;
} 



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::ZeroOrMore(void){
	ZeroOrMore_e * e = new ZeroOrMore_e();

	if( lookAhead == TokenLEFT_PARENTHESIS ){
		Match(TokenLEFT_PARENTHESIS);
		e->e = Regex();
		Match(TokenRIGHT_PARENTHESIS);
		Match(TokenASTERICK);

		if( !HasError() )
			return e;
		else{
			if(e->e) { delete e->e; }
			delete e;
			return (RegExpr *)0;
		}
	}
	else
		assert(0);
	return (RegExpr *)0;
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::OR(void){
	OR_e * or = new OR_e();

	if( lookAhead == TokenLESS_THAN ){
		Match(TokenLESS_THAN);
		or->e1 = Regex();
		Match(TokenVERTICAL_BAR);
		or->e2 = Regex();
		Match(TokenGREATER_THAN);
		
		if( !HasError() )
			return or;
		else{
			if(or->e1) { delete or->e1; }
			if(or->e2) { delete or->e2; }
			delete or;
			return (RegExpr *)0;
		}
	}
	else
		assert(0);
	return (RegExpr *)0;
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::Tag(void){
	Tag_e * tag = new Tag_e();

	if( lookAhead == TokenLEFT_CURLY_BRACE ){
		Match(TokenLEFT_CURLY_BRACE);
		tag->e = Regex();
		Match(TokenRIGHT_CURLY_BRACE);
		
		if( !HasError() )
			return tag;
		else{
			if(tag->e) { delete tag->e; }
			delete tag;
			return (RegExpr *)0;
		}
	}

	else 
		assert(0);
	return (RegExpr *)0;
}


//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::String(void){
	if( lookAhead == TokenREGEX_STRING ){
		Match(TokenREGEX_STRING);
		String_e * str = new String_e();
		str->text = GetCurrToken().value.strVal;
		return str;
	}
	else 
		assert(0);
	return (RegExpr *)0;
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::DeltaId(void){
	if( lookAhead == TokenDELTA_ID ){
		Match(TokenDELTA_ID);
		return new DeltaIdent_e();
	}
	else 
		assert(0);	
	return (RegExpr *)0;
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::AnyCharacter(void){
	if( lookAhead == TokenANY_CHARACTER ){
		Match(TokenANY_CHARACTER);
		return new AnyChar_e();
	}
	else 
		assert(0);
	return (RegExpr *)0;
}



//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::WhiteSpace(void){
	if( lookAhead == TokenWHITE_SPACE ){
		Match(TokenWHITE_SPACE);
		return new WhiteSpace_e();
	}
	else 
		assert(0);
	return (RegExpr *)0;
}


//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::Number(void){
	if( lookAhead == TokenNUM ){
		Match(TokenNUM);
		String_e * str = new String_e();
		str->text = lexical_cast<int>(GetCurrToken().value.intVal);
		return str;
	}
	else 
		assert(0);
	return (RegExpr *)0;
}


//////////////////////////////////////////////////////////////////////
RegExpr * parser::RDParserFind::Epsilon(void){
	return new Epsilon_e();
}