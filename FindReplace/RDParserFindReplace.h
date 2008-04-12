/*
 * RDParserFindReplace.h
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */

#ifndef RDPARSERFINDREPLACE_H	
#define RDPARSERFINDREPLACE_H


#include <list>
#include <functional>
#include "RegExpr.h"
#include "RDParser.h"


namespace parser{
	
	class RDParserFindReplace : public parser::RDParser{
	private:

		struct ClearFunctor : public std::unary_function<void, RegExpr *> {
			void operator()(const RegExpr * reg) const{
				if(reg) { delete reg; }
			}
		};
		
		//variables
		//********************************************************
		std::list<RegExpr *> toDelete;


		//rules
		//********************************************************
		RegExpr * Regex(void);
		RegExpr * Reg(void);
		RegExpr * Regs(void);
		RegExpr * BackslashNum(void);
		RegExpr * String(void);
		RegExpr * DeltaId(void);
		RegExpr * AnyCharacter(void);
		RegExpr * WhiteSpace(void);
		RegExpr * Epsilon(void);

	public:
		

		RegExpr * Analyse (TokenList* _tokens);
		void Clear(void);


		RDParserFindReplace(void);
		~RDParserFindReplace(void);
	};
}


#endif
