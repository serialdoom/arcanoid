/*
 * RDParserFind.h
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */

#ifndef RDPARSERFIND_H	
#define RDPARSERFIND_H

#include <list>
#include <sstream>
#include <functional>
#include "RegExpr.h"
#include "RDParser.h"


namespace parser{

	class RDParserFind  : public parser::RDParser{
	private:
		struct ClearFunctor : public std::unary_function<void, RegExpr *> {
			void operator()(const RegExpr * reg) const{
				if(reg) { 
					delete reg; 
					reg = (RegExpr*)0;
				}
			}
		};

		//variables
		//********************************************************
		bool	notMatch;
		std::list<RegExpr *> toDelete;

		//rules
		//********************************************************
		RegExpr * Regex(void);
		RegExpr * Regexs(void);
		RegExpr * ZeroOrMore(void);
		RegExpr * OR(void);
		RegExpr * Tag(void);
		RegExpr * String(void);
		RegExpr * DeltaId(void);
		RegExpr * AnyCharacter(void);
		RegExpr * WhiteSpace(void);
		RegExpr * Number(void);
		RegExpr * Epsilon(void);
		
	public:
		RegExpr * Analyse (TokenList* _tokens);
		void Clear(void);

		RDParserFind();
		~RDParserFind(void);
	};
}


#endif
