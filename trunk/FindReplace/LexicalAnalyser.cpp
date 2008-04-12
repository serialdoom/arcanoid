/*
 * LexicalAnalyser.cpp
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */


#include <cassert>
#include <ctype.h>
#include <memory.h>
#include <algorithm>

#include "LexicalAnalyser.h"


parser::LexicalAnalyser::LexicalAnalyser(void){
	hasError		= false;
	errorMsg		= (char *)0;
	totalLookAhead	= 0;
	ptrInputStr		= 0;
	tokenList		= (TokenList*) 0;
}


parser::LexicalAnalyser::~LexicalAnalyser(void){
	Clear();
}


/////////////////////////////////////////////////////////////////
void parser::LexicalAnalyser::Clear(void){
	if (tokenList) {
		std::for_each( tokenList->begin(), tokenList->end(), Token::ClearFunctor() );
		delete tokenList;
	}

	if( HasError() ){
		delete []errorMsg;
	}
	hasError		= false;
	errorMsg		= (char *)0;
	totalLookAhead	= 0;
	ptrInputStr		= 0;
	tokenList		= (TokenList*) 0;
	return;
}



/////////////////////////////////////////////////////////////////
void parser::LexicalAnalyser::SetError(char * msg){
	hasError = true;
	errorMsg = _strdup(msg);
	return;
}



/////////////////////////////////////////////////////////////////
void parser::LexicalAnalyser::Unput (void) {
	if ( ptrInputStr < 0 )
		SetError("Max Unput exceeded!");
	else {
		ptrInputStr--;
	}
	return;
}



/////////////////////////////////////////////////////////////////
char parser::LexicalAnalyser::Input (void) {
	char c;

	if( ptrInputStr > totalLookAhead)
		c = '\0';
	else{
		c = inputStr[ptrInputStr];
		ptrInputStr++;
	}
	
	return c;
}



/////////////////////////////////////////////////////////////////
void parser::LexicalAnalyser::IgnoreWhiteSpace (void) {
	while ( ptrInputStr < totalLookAhead) {
		char c = Input();
		if (c==' ')
			continue;
		
		else {
			if (isprint(c))
				Unput();
			return;
		}
	}//end of while
	return;
}




/////////////////////////////////////////////////////////////////
bool parser::LexicalAnalyser::IsSingleCharToken (char token) {
	char c = Input();
	
	if (c == token) 
		return true;
	
	else {
		Unput();
		return false;
	}
}



/////////////////////////////////////////////////////////////////
bool parser::LexicalAnalyser::IsINT (unsigned int* val) {
	*val = 0;
	char c = Input();
	if (!isdigit(c)) {
		Unput();
		return false;
	}
	do {
		*val = *val * 10 + c - '0';
		c = Input();
	} while (isdigit(c));
	
	Unput();
	return true;
}



/////////////////////////////////////////////////////////////////
bool parser::LexicalAnalyser::IsSTRING (char** val) {

	char * cmp = "{}<>*()|:";
	std::list<char> str;
	char c = Input();
	
	while ( true) 
	{
		if( c == '\\' ){
			c = Input();
			if( !strchr(cmp, c) ){	//den einai char opos: \{, \} ...
				Unput();			//Unput curr C
				Unput();			//Unput '\\'
				break;
			}
		}
		else if( strchr(cmp, c) || (c == '\0') )
		{
			Unput();
			break;
		}
		str.push_back(c);		
		c = Input();
	}//end of while
	
	if( !str.size() )
		return false;
	else{
		char* p = *val = new char[ str.size() + 1 ];
	
		for ( std::list<char>::iterator charIter = str.begin();
			charIter != str.end();
			++charIter, ++p )
		{
			*p = *charIter;
		}

		*p = '\0';
		return true;
	}
}//end of IsSTRING



/////////////////////////////////////////////////////////////////
bool parser::LexicalAnalyser::IsWhiteSpace (void){
	if( IsSingleCharToken(':') ){
		if( IsSingleCharToken('w') ) { return true; }
		Unput(); //unput chaacher ':'
	}
	return false;
}



/////////////////////////////////////////////////////////////////
bool parser::LexicalAnalyser::IsDeltaId (void){
	if( IsSingleCharToken(':') ){
		if( IsSingleCharToken('i') ) { return true; }
		Unput(); //unput chaacher ':'
	}
	return false;
}



/////////////////////////////////////////////////////////////////
bool parser::LexicalAnalyser::Analyse (std::string & str) {
	inputStr = str;
	totalLookAhead = str.length();

	tokenList	= new TokenList;
	Token token;
	
	token.type = TokenSTART_SYMBOL;
	tokenList->push_back( token );

	while ( (ptrInputStr < inputStr.length()) ) {
		IgnoreWhiteSpace();

		if ( ptrInputStr >= inputStr.length() ) { break; }

		if ( !HasError() && IsSingleCharToken('.') )
			token.type = TokenANY_CHARACTER;

		else if( !HasError() && IsWhiteSpace() )
			token.type = TokenWHITE_SPACE;

		else if( !HasError() && IsDeltaId() )
			token.type = TokenDELTA_ID;


		else if ( !HasError() && IsINT(&token.value.intVal))
			token.type = TokenNUM;
		
		else if ( !HasError() && IsSTRING(&token.value.strVal))//panta prhn apo ton elegxo gia single '\\'
			token.type = TokenREGEX_STRING;

		else if ( !HasError() && IsSingleCharToken('*'))
			token.type = TokenASTERICK;
		
		else if ( !HasError() && IsSingleCharToken('{'))
			token.type = TokenLEFT_CURLY_BRACE;
		
		else if ( !HasError() && IsSingleCharToken('}'))
			token.type = TokenRIGHT_CURLY_BRACE;
		
		else if ( !HasError() && IsSingleCharToken('<'))
			token.type = TokenLESS_THAN;

		else if ( !HasError() && IsSingleCharToken('>'))
			token.type = TokenGREATER_THAN;
		
		else if ( !HasError() && IsSingleCharToken('('))
			token.type = TokenLEFT_PARENTHESIS;
		
		else if ( !HasError() && IsSingleCharToken(')'))
			token.type = TokenRIGHT_PARENTHESIS;

		else if ( !HasError() && IsSingleCharToken('|'))
			token.type = TokenVERTICAL_BAR;

		else if ( !HasError() && IsSingleCharToken('\\'))
			token.type = TokenBACKSLASH;
		
		else{ 
			if( !HasError() )
				SetError("Unrecognised token!");
			break; 
		}
		tokenList->push_back(token);
	}//end of while
	
	//mark the end of file
	token.type = TokenEOF;
	tokenList->push_back(token);
	
	return !hasError;
}//end of Analyse



/////////////////////////////////////////////////////////////////
void parser::LexicalAnalyser::Token::Write (FILE* fp) {
	switch (type) {
		case TokenSTART_SYMBOL		: fprintf(fp, "Start symbol\n");	break;
		case TokenASTERICK			: fprintf(fp, "*\n");	break;
		case TokenLEFT_CURLY_BRACE	: fprintf(fp, "{\n");	break;
		case TokenRIGHT_CURLY_BRACE : fprintf(fp, "}\n");	break;
		case TokenLESS_THAN			: fprintf(fp, "<\n");	break;
		case TokenGREATER_THAN		: fprintf(fp, ">\n");	break;
		case TokenLEFT_PARENTHESIS	: fprintf(fp, "(\n");	break;
		case TokenRIGHT_PARENTHESIS : fprintf(fp, ")\n");	break;
		case TokenVERTICAL_BAR		: fprintf(fp, "|\n");	break;
		case TokenBACKSLASH			: fprintf(fp, "\\\n"); break;
		case TokenDELTA_ID			: fprintf(fp, "Delta identifire\n"); break;
		case TokenANY_CHARACTER		: fprintf(fp, "Any character\n"); break;
		case TokenWHITE_SPACE		: fprintf(fp, "White Space\n"); break;
		case TokenNUM				: fprintf(fp, "%d\n", value.intVal); break;
		case TokenREGEX_STRING		: fprintf(fp, "'%s'\n", value.strVal); break;
		case TokenEOF				: fprintf(fp, "EOF\n"); break;
	}//end of switch
	return;
}



/////////////////////////////////////////////////////////////////
void parser::LexicalAnalyser::DumpTokens (FILE* fp) {

	if (tokenList){
		for (	TokenList::iterator tokenIter = tokenList->begin();
				tokenIter != tokenList->end();
				++tokenIter )
		{
			tokenIter->Write(fp);
		}//end of for
	}//end of if
	
	return;
}