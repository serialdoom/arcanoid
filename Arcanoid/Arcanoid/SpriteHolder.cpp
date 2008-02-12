/*
 * author: koutsop
 */

#include <iostream>
#include <cassert>
#include "Brick.h"
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
void SpriteHolder::SetSprite(string name, Sprite * sprite){
	assert(sprite);
	Sprite * tmp = GetSprite(name);
	
	assert(tmp);	//Den bre8ike to sprite
	tmp = sprite;
	return;
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
/////////////////////////////////////////////////////////////////////


void SpriteHolder::MarkAsDeleted(string name){
	SpriteMap::iterator sprite = sprites.find(name);
	assert(sprite != sprites.end()); 

	deleted.push_back(sprite->second);
	sprites.erase(sprite);	
	return;
}
/////////////////////////////////////////////////////////////////////

/*
std::list<Sprite *>::iterator SpriteHolder::GetEndDeleded(void){
	return deleted.end();
}

std::list<Sprite *>::iterator SpriteHolder::GetFirstDeleded(void){
	return deleted.begin();
}
*/

void SpriteHolder::PrintSpriteHolder(){
	SpriteMap::iterator start = sprites.begin();
	SpriteMap::iterator end = sprites.end();
	int cnt = 0;
	while( start != end){
		if( dynamic_cast<Brick *>(start->second))
			cout<<start->first<<"    "<<start->second->GetPosition().ToString()<<endl;
		start++;
	}
}