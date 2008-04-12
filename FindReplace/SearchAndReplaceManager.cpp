#include <stdio.h>
#include <assert.h>
#include <algorithm>

#include "RDParserFind.h"
#include "RDParserFindReplace.h"
#include "SearchAndReplaceManager.h"

SearchAndReplaceManager::SearchAndReplaceManager(void)
{
	reg			= false;
	hasError	= false;
	errorMsg	= (char *)0;
	currFind	= -1;
	find		= new RDParserFind();
	replace		= new RDParserFindReplace();
	
	settings.wholeWord			= false;
	settings.searchUp			= false;
	settings.isCaseSensitive	= false;

}

SearchAndReplaceManager::~SearchAndReplaceManager(void)
{
	Clear();
	delete find;
	delete replace;
}



/////////////////////////////////////////////////////////////////
void SearchAndReplaceManager::Clear(void){
	
	find->Clear();
	replace->Clear();
	analyser.Clear();
	
	for_each( results.begin(), results.end(), ClearFunctor() ); //delete results
	results.clear();

	hasError = false;
	if( errorMsg ){
		delete []errorMsg;
		errorMsg = (char *)0;
	}

	return;
}



/////////////////////////////////////////////////////////////////
void SearchAndReplaceManager::SetError(char * msg){
	hasError = true;
	errorMsg = _strdup(msg);
	return;
}


/////////////////////////////////////////////////////////////////
bool SearchAndReplaceManager::Find ( RegExpr* e, 
									 InputStream& s, 
									 InputStream::Pos& from, 
									 InputStream::Pos& to) 
{
	from  = s.GetPos();
	bool result = e->Match(s);
	to = s.GetPos();
	return result;
}



//////////////////////////////////////////////////////////////////////
bool SearchAndReplaceManager::FindRegEx(RegExpr * e){
	assert(e && ( dynamic_cast<Epsilon_e *>(e)!= e) );
	
	for(std::list<InputStream *>::iterator s = stream.begin(); 
		s != stream.end(); s++ )
	{
		if ( (*s)->Open("test") ){
			while( !(*s)->IsEof() ){
				InputStream::Block * tmp = new InputStream::Block();
				tmp->path = (*s)->GetPath();

				if ( Find(e, *(*s), tmp->start, tmp->end) )
				{
					results.push_back(tmp);
				}
				else { 
					delete tmp; 
					(*s)->GetNext();
				}
			}//end of while

			(*s)->Close();
		}//first if
	}
		
	return results.size() != 0;
}



//////////////////////////////////////////////////////////////////////
bool SearchAndReplaceManager::Find(void){
	bool r = false;
	Clear();

	if(reg){		//Use regex for searching
		if( analyser.Analyse(what) ){ 
			if (RegExpr * e = find->Analyse( analyser.GetTokens() )){
				r = FindRegEx(e);
			}
			else {
				SetError("Pars error");
				return false;
			}
		}//first if
		else {
			SetError( analyser.GetError() );
			return false; 
		}
	}
	else{			//Use string for searching
		String_e str;
		str.text = what;
		r = FindRegEx(&str);
	}
	currFind = -1;
	return r;
}


//////////////////////////////////////////////////////////////////////
void SearchAndReplaceManager::SetFindParam(std::string _what, bool _reg){
	what	= _what;
	reg		= _reg;
	return;
}



//////////////////////////////////////////////////////////////////////
void SearchAndReplaceManager::SetReplaceParam(std::string _what, std::string _with, bool _reg){
	what	= _what;
	with	= _with;
	reg		= _reg;
	return;
}



//////////////////////////////////////////////////////////////////////
InputStream::Block * SearchAndReplaceManager::GetNext (void){
	assert(results.size());
	currFind++;
	if( currFind >= (long)results.size() )
		currFind = 0;
	return results.at( currFind % results.size() );
}



//////////////////////////////////////////////////////////////////////
InputStream::Block * SearchAndReplaceManager::GetPrev (void){
	assert(results.size());
	currFind--;
	if( currFind < 0 ){
		currFind = (long)results.size() -1 ;
	}
	return results.at( currFind % results.size() );
}



//if f <= s return true else false'
bool cmp(const InputStream::Pos f, const InputStream::Pos s){
	if( f.row <= s.row ){		//f.row <= s.row
		if( f.col <= s.col )	//g.col <= s.col
			return true;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////
unsigned  SearchAndReplaceManager::CalculatePos(void){
	//edw 8a prepei na pernoume ola ta arxeia pou uparxoun mesa
	//sthn lista stream kai na blepoume poio einai energo.
	//An to broume tote sunexisoume opos kai parakatw. Pros to 
	//parwn auto pou 8a kanoume einai na pernoume to ptwto stream pou uparxei
	//mesa sthn lista
	currFind = 0;
	InputStream::Pos filePos = (*stream.begin())->GetPos();
	
	for( std::vector<InputStream::Block *>::iterator s = results.begin();
		 s != results.end(); s++)
	{
		if( cmp(filePos, (*s)->start) )
			return (unsigned)currFind;
		else
			currFind++;
	}
	return 0;
}



//////////////////////////////////////////////////////////////////////
InputStream::Block * SearchAndReplaceManager::FindNext(void){
	if( currFind == -1 )	//Prepei na broume apo poia 8esh 8a 3ekinisoume
		CalculatePos();		//thn prwth fora

	if( settings.searchUp )
		return GetPrev(); 
	else
		return GetNext();
}



//////////////////////////////////////////////////////////////////////
void SearchAndReplaceManager::WriteResults( InputStream::Block * r){
	std::cout<<"File Name: "<<r->path <<std::endl;
	std::cout<<"Start	Row: "<<r->start.row <<std::endl;
	std::cout<<"Start	Col: "<<r->start.col <<std::endl;
	std::cout<<"End	Row: "<<r->end.row <<std::endl;
	std::cout<<"End	Col: "<<r->end.col <<std::endl;
	std::cout<<"\n\n\n";
	return;
}



//////////////////////////////////////////////////////////////////////
void SearchAndReplaceManager::DumpResults(void){
	for (std::vector<InputStream::Block *>::iterator r = results.begin();
		 r != results.end(); r++)
	{
		WriteResults( *r );
	}
	return;
}
