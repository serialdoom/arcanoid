/*
 * FileInputStream.cpp
 * author: Koutsopoulos Nikolaos
 * mail	 : koutsop@csd.uoc.gr	
 */
//TODO: na dior8wsw to unput wte na ananeonei thn pos 

#include <stdio.h>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "FileInputStream.h"

FileInputStream::FileInputStream(void){
	E_O_F			= false;
	currPos			= 0;
	position.row	= 1;
	position.col	= 1;
}

FileInputStream::~FileInputStream(void){
	vec.clear();
	markPos.clear();
}



/////////////////////////////////////////////////////////////////
bool FileInputStream::Open (std::string path){
	std::ifstream file(path.c_str());

	if (file.is_open()) {
		currPos			= 0;
		position.row	= 1;
		position.col	= 1;
		file.unsetf(std::ios::skipws);  //Turn of white space skipping
		
		std::copy(
			std::istream_iterator<char>(file),
			std::istream_iterator<char>(),
			std::back_inserter(vec)
		);
		
		file.close();
		return true;
	}
	return false;
}




/////////////////////////////////////////////////////////////////
bool FileInputStream::Close (void){
	E_O_F			= false;
	currPos			= 0;
	position.row	= 1;
	position.col	= 1;
	
	vec.clear();
	markPos.clear();
	return true;
}



/////////////////////////////////////////////////////////////////
bool FileInputStream::IsEof(void) const{
	return E_O_F;
}



/////////////////////////////////////////////////////////////////
char FileInputStream::GetNext(){
	
	if( currPos < vec.size() ){
		char c = vec[currPos++];
		
		if( c == '\n'){
			position.row++;
			position.col = 1;
		}
		else { position.col++; }

		return c;
	}
	
	E_O_F = true;
	return EOF;
}




/////////////////////////////////////////////////////////////////
bool FileInputStream::Unput(void){
	if( currPos > 0){
		if( vec[currPos] == '\n' ){
			position.row++;
			//position.second Edw na to dior8wsw
		}
		else { position.col--; }
		currPos--;
	}
	return true;;
}




/////////////////////////////////////////////////////////////////
bool FileInputStream::Retract(unsigned marker){
	if( markPos.find(marker) != markPos.end() ){
		currPos = marker;
		position.row	= markPos[marker].row;
		position.col	= markPos[marker].col;
		return true;
	}
	return false;
}




/////////////////////////////////////////////////////////////////
unsigned FileInputStream::Mark (void){
	markPos[currPos].row = position.row;
	markPos[currPos].col = position.col;
	return currPos;
}



bool FileInputStream::Unmark (unsigned marked){
	return true;
}