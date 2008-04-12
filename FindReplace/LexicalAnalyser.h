/*
 * LexicalAnalyser.h
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */

#ifndef LEXICALANALYSER_H
#define LEXICALANALYSER_H

#include <stdio.h>

#include <list>
#include <string>
#include <iostream>
#include <functional>


namespace parser{
	enum TokenType {
		TokenSTART_SYMBOL		= 0,
		TokenASTERICK,
		TokenLEFT_CURLY_BRACE,
		TokenRIGHT_CURLY_BRACE,
		TokenLESS_THAN,
		TokenGREATER_THAN,
		TokenLEFT_PARENTHESIS,
		TokenRIGHT_PARENTHESIS,
		TokenVERTICAL_BAR,
		TokenBACKSLASH,
		TokenNUM,
		TokenREGEX_STRING,
		TokenDELTA_ID,
		TokenANY_CHARACTER,
		TokenWHITE_SPACE,
		TokenEOF
	};


//////////////////////////////////////////////////////////////////////
	union TokenValue {
		unsigned int intVal;
		char*		 strVal;
	};



//////////////////////////////////////////////////////////////////////
	class LexicalAnalyser {
	public:
		struct Token {
			TokenType type;
			TokenValue value;
			
			struct ClearFunctor : public std::unary_function<void, Token> {
				void operator()(const Token& token) const {
					if ( (token.type == TokenREGEX_STRING) && token.value.strVal) {
						delete[] token.value.strVal;
						const_cast<Token&>(token).value.strVal =(char*) 0;
					}
				}
			};//end of ClearFunctor

			void Write(FILE *fp);
			
			void operator=(const Token& token) { new (this) Token(token); }
			
			bool operator==(const Token& token) {
				if( this->type == token.type)
					return true;
				else
					return false;
			}

			bool operator==(const TokenType& type) {
				if( this->type == type)
					return true;
				else
					return false;
			}

			//constructores
			Token (const Token& token) { memcpy(this, &token, sizeof(Token)); }
			Token (void){}
		}; //End of struct Token

		typedef std::list<Token> TokenList;



//////////////////////////////////////////////////////////////////////
	private:
		bool		hasError;
		char *		errorMsg;
		size_t		totalLookAhead;
		TokenList*	tokenList;
		size_t		ptrInputStr;		//Mas dixnei enan enan tous xaraktires apo to str
		std::string	inputStr;


		void SetError(char *msg);

		//**********************
		void Unput (void);
		char Input (void);
		void IgnoreWhiteSpace (void);
		bool IsSingleCharToken (char token);
		bool IsINT (unsigned int* val);
		bool IsSTRING (char** val);
		bool IsWhiteSpace (void);
		bool IsDeltaId (void);
		


	public:
		char *		GetError(void) { return errorMsg; }
		bool		HasError(void) { return hasError; }
		bool		Analyse (std::string & str);
		TokenList*	GetTokens (void) const { return tokenList; }
		void		DumpTokens (FILE *fp);
		void		Clear(void);

		LexicalAnalyser(void);
		~LexicalAnalyser(void);
	};//end of class LexicalAnalyser

}//end of namespace parser


#endif