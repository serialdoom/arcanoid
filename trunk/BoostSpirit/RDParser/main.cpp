 

#include "boost/spirit/core.hpp"
#include <iostream>
#include <string>

#include "Grammar.h"

using namespace std;
using namespace boost::spirit;

int main() {

    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "\t\tExpression parser...\n\n";
    cout << "/////////////////////////////////////////////////////////\n\n";
    cout << "Type an expression...or [quit] to quit\n\n";

	//RegexParser::GrammarFind rdb;    //  Our parser
	RegexParser::GrammarFindReplace rdb;

    for (;;)
    {
        char str[256];
        cin.getline(str, 256);
        //if ( !((string)str).compare("quit") )
          //  break;
        
        parse_info<> info = parse(str, rdb, space_p);

        if (info.full)
        {
            cout << "-------------------------\n";
            cout << "Parsing succeeded\n";
            cout << "-------------------------\n";
        }
        else
        {
            cout << "-------------------------\n";
            cout << "Parsing failed\n";
            cout << "stopped at: \": " << info.stop << "\"\n";
            cout << "-------------------------\n";
        }
    }

    cout << "Bye... :-) \n\n";
    return 0;
}
