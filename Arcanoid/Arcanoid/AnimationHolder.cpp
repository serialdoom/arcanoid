/*
 * author: koutsop
 */
#include <cassert>
#include "AnimationHolder.h"

AnimationHolder::~AnimationHolder(void){
	animations.clear();
}
/////////////////////////////////////////////////////////////////////



size_t AnimationHolder::Size(void) const{
	return animations.size();
}
/////////////////////////////////////////////////////////////////////



bool AnimationHolder::IsEmpty(void) const{
	return animations.empty();
}
/////////////////////////////////////////////////////////////////////


	
void AnimationHolder::Insert(string name, Animation * animation){
	animations.insert(make_pair(name, animation));
	return;
}
/////////////////////////////////////////////////////////////////////



bool AnimationHolder::SetSprite(string name, Animation * animation){
	assert(animation);
	Animation * anim = GetAnimation(name);
	
	if( !anim ) { return false; }
	
	anim = animation;
	return true;
}
/////////////////////////////////////////////////////////////////////



AnimationMap::iterator	AnimationHolder::GetFirst(void){
	return animations.begin();
}
/////////////////////////////////////////////////////////////////////



AnimationMap::iterator	AnimationHolder::GetEnd(void){
	return animations.end();
}
/////////////////////////////////////////////////////////////////////



Animation * AnimationHolder::GetAnimation(string name) const{
	AnimationMap::const_iterator animation = animations.find(name);
	return (animation != animations.end())? animation->second:(Animation*)0;
}
/////////////////////////////////////////////////////////////////////



void AnimationHolder::Clear(void){
	animations.clear();
	return;
}
/////////////////////////////////////////////////////////////////////



void AnimationHolder::EraseSprite(string name){
	AnimationMap::iterator animation = animations.find(name);

	if(animation == animations.end()) { assert(0); }
	animations.erase(animation);
	return;
}
/////////////////////////////////////////////////////////////////////
