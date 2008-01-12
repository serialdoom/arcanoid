/*
 * author: koutsop
 */
#include "SpriteHolder.h"


//SpriteMap SpriteHolder::sprites;

SpriteHolder::SpriteHolder(void){}

SpriteHolder::~SpriteHolder(void){}


//void SpriteHolder::Move();			//kanei tis kuniseis

//To sinolo twn stixiwn
size_t SpriteHolder::Size(void){
	return sprites.size();
}

//delete all
void SpriteHolder::Clear(void){
	sprites.clear();
	return;
}

//an exei stixoia
bool SpriteHolder::IsEmpty(void){
	if( sprites.size() == 0 )
		return true;
	else
		return false;
}

//return specific sprite or null
SpriteMap::iterator SpriteHolder::GetSprite(string name){	
	return sprites.find(name);
}



SpriteMap::iterator	SpriteHolder::GetFirst(void){
	return sprites.begin();
}

SpriteMap::iterator	SpriteHolder::GetEnd(void){
	return sprites.end();
}


//update sprite
//an olla kala true alios false
bool SpriteHolder::SetSprite(string name, Sprite * sprite){
	SpriteMap::iterator iter = GetSprite(name);

	if(iter == sprites.end())
		return false;

	iter->second = sprite;
	return true;
}


//add sprite
void SpriteHolder::Insert(string name, Sprite * sprite){
	sprites.insert(make_pair(name, sprite));
	return;
}