/*
 * RDParser.h
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */

#ifndef RDPARSER_H	
#define RDPARSER_H


#include "RegExpr.h"
#include "Lexicalanalyser.h"


namespace parser{
	
	class RDParser {
	protected:
		typedef LexicalAnalyser::TokenList	TokenList;
		typedef LexicalAnalyser::Token		Token;
		
		TokenList::iterator tokenListIter;
		TokenList* tokens;
		Token lookAhead;

		bool hasError;
		std::string errorMsg;

		Token GetNextToken (void);
		//Token GetPrevToken (void);

		TokenList::iterator marck_input_position(void) {return tokenListIter;}

		void RetractCurrToken (void);
		void retruct_input_till_position(TokenList::iterator t) { tokenListIter = t; }
		Token & GetCurrToken(void);

		bool HasMoreTokens (void){ return tokenListIter != tokens->end(); }
		void Match(TokenType t);
		void Error(TokenType t);


	public:
		
		bool HasError(void) const { return hasError; }
		const std::string GetError(void) const { return errorMsg; }

		virtual RegExpr * Analyse (TokenList* _tokens) = 0;
		virtual void Clear(void) = 0;

		//virtual RDParser(void) { lookAhead = TokenSTART_SYMBOL; }
		virtual ~RDParser(void){}

	};
}


#endif
