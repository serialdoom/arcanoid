#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility.hpp>

using namespace boost::spirit;

namespace {
	void	do_regex(char const*, char const*)	{std::cout<< "rule Regex\n";}
	void	do_reg(char const*, char const*)	{std::cout<< "rule R\n";}
	void	do_regs(char const*, char const*)	{std::cout<< "rule Rs\n";}
	void	do_brace(char const*, char const*)	{std::cout<< "Brace\n";}
	void	do_lessGreater(char const*, char const*)	{std::cout<< "LessGreater\n";}
	void	do_parenthesis(char const*, char const*)	{std::cout<< "Parenthesis\n";}
	void	do_str(char const*, char const*)	{std::cout<< "STRING\n";}
	void	do_num(char const*, char const*)	{std::cout<< "Num\n";}
}


namespace RegexParser{
	
	struct GrammarFind : public boost::spirit::grammar<GrammarFind>
	{
		template <typename ScannerT>
		struct definition 
		{
			definition(GrammarFind const& self)
			{		
				regex 
					=	R[&do_regex]
					;

				R 
					=	(Rs >> R )[&do_reg]
					|	epsilon_p[&do_reg]
					;	

				Rs
					=	brace		[&do_regs]
					|	lessGreater	[&do_regs]
					|	parenthesis	[&do_regs]
					|	REGEXSTRING [&do_str]
					;

				brace
					=	(LEFT_CURLY_BRANCE >> R >> RIGHT_CURLY_BRANCE >> ASTERICK)[&do_brace]
					;

				lessGreater
					=	(LESS_THAN>> R >> GREATER_THAN)[&do_lessGreater]
					;

				parenthesis
					=	(LEFT_PARARETHESIS >> R >> VERTICAL_BAR >> R >> RIGHT_PARARETHESIS)[&do_parenthesis]
					;

				REGEXSTRING
					=	lexeme_d[ +( anychar_p &
									 ~chlit<>('*') &
									 ~chlit<>('{') &
									 ~chlit<>('}') &
									 ~chlit<>('<') &
									 ~chlit<>('>') &
									 ~chlit<>('(') &
									 ~chlit<>(')') &
									 ~chlit<>('|') &
									 ~chlit<>('\\')
									) 
								]
					;

				
				ASTERICK			= chlit<>('*');
				LEFT_CURLY_BRANCE	= chlit<>('{');
				RIGHT_CURLY_BRANCE	= chlit<>('}');
				LESS_THAN			= chlit<>('<');
				GREATER_THAN		= chlit<>('>');
				LEFT_PARARETHESIS	= chlit<>('(');
				RIGHT_PARARETHESIS	= chlit<>(')');
				VERTICAL_BAR		= chlit<>('|');
			}//End of definition

			// no terminals
			boost::spirit::rule<ScannerT> regex, Rs, R,
				brace, parenthesis, lessGreater; 

			// terminals
			boost::spirit::rule<ScannerT>
				ASTERICK, LEFT_CURLY_BRANCE, RIGHT_CURLY_BRANCE, LESS_THAN, GREATER_THAN, 
				LEFT_PARARETHESIS, RIGHT_PARARETHESIS, VERTICAL_BAR, REGEXSTRING;

			rule<ScannerT> const& start() const { return regex; }
		};//END OF struct definition
	};//end os GrammarFind

	struct GrammarFindReplace : public boost::spirit::grammar<GrammarFindReplace>
	{
		template <typename ScannerT>
		struct definition 
		{
			definition(GrammarFindReplace const& self)
			{
				/*
				regex
					=	reg
					;

				reg
					=	reg >> regc
					|	epsilon_p
					;

				regc
					=	BACKSLASH >> NUM[&do_num]
					|	(REGEXSTRING)[&do_str]
					;
					*/

				regex 
					=	BACKSLASH >> NUM >> regex
					|	REGEXSTRING >> regex
					|	epsilon_p
					;

				//regc 
				//	=	regex >> regc
				//	|	epsilon_p
				//	;

				REGEXSTRING
					=	lexeme_d[ +( anychar_p &
									 ~chlit<>('*') &
									 ~chlit<>('{') &
									 ~chlit<>('}') &
									 ~chlit<>('<') &
									 ~chlit<>('>') &
									 ~chlit<>('(') &
									 ~chlit<>(')') &
									 ~chlit<>('|') &
									 ~chlit<>('\\')
									) 
								]
					;


				NUM
					=	lexeme_d[+digit_p]
					;
				BACKSLASH		= chlit<>('\\');

				//R: 	string | ‘\’num | R Rc | å
				//Rc:	R Rc | å

			}//end of definition

			// no terminal
			boost::spirit::rule<ScannerT> regex, regc, reg;

			// terminals
			boost::spirit::rule<ScannerT> REGEXSTRING, NUM, BACKSLASH;

			rule<ScannerT> const& start() const { return regex; }
		};//END OF struct definition
	};//end os GrammarFind


}//RegexParser

#endif