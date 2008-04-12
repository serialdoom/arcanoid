#if 0
#include <iostream>
#include <list>
#include <string>


#include "InputStream.h"
#include "FileInputStream.h"
#include "SearchAndReplaceManager.h"


using namespace std;

int main(){
    cout << "/////////////////////////////////////////////////////////\n\n";

	//Firts file
	FileInputStream file1;
	//file1.SetPath("test.txt");

	//Second file
	FileInputStream file2;
	//file2.SetPath("test2.txt");


	//Create list
	list<InputStream *> streamList;
	streamList.push_back(&file1);
	streamList.push_back(&file2);


	//Cretae Manager
	SearchAndReplaceManager manager;
	manager.Set(streamList);

	for (;;)
    {
        char buffer[256];

		std::cout<<"Pres:"<<std::endl;
		std::cout<<"1) to exit"<<std::endl;
		std::cout<<"2) searchUp"<<std::endl;
		std::cout<<"3) regex"<<std::endl;
		std::cout<<"4) string"<<std::endl;
		std::cout<<"5) find next"<<std::endl;
		std::cout<<"6) print all"<<std::endl;
		std::cout<<">:";
        
		cin.getline(buffer, 256);
		
		switch(buffer[0]){
			case '1': std::cout<<"successed"<<std::endl; return 0;
			case '2':{	std::cout<<"successed"<<std::endl; 
						if( manager.settings.searchUp )
							manager.settings.searchUp = false;
						else
							manager.settings.searchUp = true;
						break;
					 }

			case '3':{	std::cout<<"Enter regex: ";
						std::cin.getline(buffer, 256);

						manager.SetFindParam((string)buffer, true);
						if( manager.Find() )
							cout<<"Found\n";
						else
							cout<<"Not Found\n";
						std::cout<<"successed"<<std::endl;
						break;
					 }

			case '4':{	std::cout<<"Enter string: ";
						std::cin.getline(buffer, 256);

						manager.SetFindParam((string)buffer, false);
						if( manager.Find() )
							cout<<"Found\n";
						else
							cout<<"Not Found\n";

						std::cout<<"successed"<<std::endl;
						break;
					 }

			case '5': manager.WriteResults( manager.FindNext() ); break;
			case '6': manager.DumpResults(); break;
			default: std::cout<< "wrong choice try again"<<std::endl; break;
		}//end of switch
		std::cout<<"\n\n\n\n"<<std::endl;

    }//end of for
    return 0;
}
#endif


#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "MyTemplates.h"
#include "RegExpr.h"
#include "InputStream.h"
#include "FileInputStream.h"
#include "RDParserFind.h"
#include "RDParserFindReplace.h"
#include "LexicalAnalyser.h"


using namespace parser;
using namespace std;



unsigned mark = 0;
void TestingFileInputStrem(FileInputStream &file, char c);
void TestingParsers(string str);



int main() {
    cout << "/////////////////////////////////////////////////////////\n\n";
	

static std::string	tokenClasses[] = 
 { "Start Symbol", "*", "{", "}", "<", ">","(",")","|","Number","String","Delte id","Any Character", "White Space" };
	//FileInputStream test;
	//test.SetPath("test.txt");
	//if ( !test.Open() )
	//	return 0;

    for (;;)
    {
        char str[256];
        cin.getline(str, 256);
        if ( !((string)str).compare("quit") )
            break;

		//TestingFileInputStrem(test, str[0]);
		TestingParsers((string)str);
    }

	//test.Close();
    cout << "Bye... :-) \n\n";
    return 0;
}




/////////////////////////////////////////////////////////////////
void TestingParsers(string str){
	LexicalAnalyser* LA = new LexicalAnalyser();
	RDParserFind * rdp	= new RDParserFind();
	RegExpr * rege		= (RegExpr *)0;

	//RDParserFindReplace * rdp = new RDParserFindReplace();

	if( LA->Analyse(((string)str)) ){
		LA->DumpTokens(stderr);

		if( rege = rdp->Analyse( LA->GetTokens() ) ){
			cout<<"Parsing succeeded\n";
		}
		else{
			cout<<rdp->GetError();
			cout<<"Parsing failed\n";
		}
	}
	else
		std::cout<<LA->GetError();
	delete LA;
	delete rdp;
	
	return;
}





/////////////////////////////////////////////////////////////////
void TestingFileInputStrem(FileInputStream &file, char c){
	if( c == '1' )
		cout << "'"<<file.GetNext() <<"'"<< std::endl;

	else if( c == '2' ){
		file.Unput();
	}
	
	else if( c == '3' ){
		cout << (mark = file.Mark()) <<endl;
	}
	
	else if( c == '4' ){
		cout << file.Retract(mark) <<endl;
	}
	
	else if( c == '5' ){
		cout << file.IsEof() << endl;
	}
	return;
}


