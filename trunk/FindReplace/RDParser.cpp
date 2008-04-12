#include <assert.h>
#include <iostream>
#include "RDParser.h"

#define MARK()	TokenList::iterator t = marck_input_position();
#define FAIL()	retruct_input_till_position(t);


//////////////////////////////////////////////////////////////////////
parser::RDParser::Token parser::RDParser::GetNextToken (void){
	if (tokenListIter != tokens->end() &&
		(*tokenListIter).type != TokenEOF) 
	{
		++tokenListIter;
	}
	return *tokenListIter;
}


//////////////////////////////////////////////////////////////////////
//parser::RDParser::Token parser::RDParser::GetPrevToken(void){
//	if( currTokenIter != tokens->begin() )
//		return *(currTokenIter);
//	else
//		return *currTokenIter;
//}



//////////////////////////////////////////////////////////////////////
void parser::RDParser::RetractCurrToken (void) {
	assert (tokenListIter != tokens->begin());
	--tokenListIter;
	return;
}



//////////////////////////////////////////////////////////////////////
void parser::RDParser::Match(TokenType t){
	if( lookAhead == TokenSTART_SYMBOL ){
		lookAhead = GetNextToken();
		return;
	}

	if( lookAhead == t )
		lookAhead = GetNextToken();
	else
		Error(t);
}


//////////////////////////////////////////////////////////////////////
void parser::RDParser::Error(TokenType t){
	hasError = true;
	std::string	tokenClasses[] = {	"Start Symbol",
									"*",
									"{",
									"}",								
									"<",
									">",
									"(",
									")",
									"|",
									"\\",
									"Number",
									"String",
									"Delte id",
									"Any Character",
									"White Space"
								};

	errorMsg += "Parse Error. Token " +
				tokenClasses[t] +
				" expected. \n";
	return;
}



//////////////////////////////////////////////////////////////////////
parser::RDParser::Token & parser::RDParser::GetCurrToken(void){

	if( tokenListIter != tokens->begin() ){
		tokenListIter--;
		Token & tmp = *tokenListIter;
		tokenListIter++;
		return tmp;
	}

	return *tokenListIter;
}