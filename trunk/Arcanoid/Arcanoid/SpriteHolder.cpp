/*
 * author: koutsop
 */

#include <iostream>
#include <cassert>
#include "SpriteHolder.h"

using std::cout;
using std::endl;


SpriteHolder::~SpriteHolder(void){
	sprites.clear();
}
/////////////////////////////////////////////////////////////////////


//To sinolo twn stixiwn
size_t SpriteHolder::Size(void){
	return sprites.size();
}
/////////////////////////////////////////////////////////////////////


//delete all
void SpriteHolder::Clear(void){
	sprites.clear();
	return;
}
/////////////////////////////////////////////////////////////////////


//an exei stixoia
bool SpriteHolder::IsEmpty(void){
	return sprites.empty();
}
/////////////////////////////////////////////////////////////////////


//return specific sprite or null
Sprite * SpriteHolder::GetSprite(string name){
	SpriteMap::iterator sprite = sprites.find(name);
	return (sprite != sprites.end())? sprite->second:(Sprite*)0;
}
/////////////////////////////////////////////////////////////////////



SpriteMap::iterator	SpriteHolder::GetFirst(void){
	return sprites.begin();
}
/////////////////////////////////////////////////////////////////////



SpriteMap::iterator	SpriteHolder::GetEnd(void){
	return sprites.end();
}
/////////////////////////////////////////////////////////////////////



//update sprite
//an olla kala true alios false
bool SpriteHolder::SetSprite(string name, Sprite * sprite){
	assert(sprite);
	Sprite * tmp = GetSprite(name);

	if( !tmp )
		return false;

	tmp = sprite;
	return true;
}
/////////////////////////////////////////////////////////////////////



//add sprite
void SpriteHolder::Insert(string name, Sprite * sprite){
	sprites.insert(make_pair(name, sprite));
	return;
}
/////////////////////////////////////////////////////////////////////


void SpriteHolder::EraseSprite(string name){
	SpriteMap::iterator sprite = sprites.find(name);

	if( sprite == sprites.end() ) { assert(0); }

	sprites.erase(sprite);
	return;
}


void SpriteHolder::PrintSpriteHolder(){
	SpriteMap::iterator start = sprites.begin();
	SpriteMap::iterator end = sprites.end();
	int cnt = 0;
	while( start != end){
		if( start->second->GetType() == SPRITE_BRICK )
			cout<<start->first<<"    "<<start->second->GetPosition().ToString()<<endl;
		start++;
	}
}