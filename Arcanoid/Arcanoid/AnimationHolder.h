/*
 * author: koutsop
 */

#ifndef ANIMATIONHOLDER_H
#define ANIMATIONHOLDER_H


#include <map>
#include <string>

#include "Animation.h"

using namespace std;
typedef map<string, Animation *> AnimationMap;


class AnimationHolder {
private:
	AnimationMap animations;

public:	
	AnimationHolder(void){}
	~AnimationHolder(void);


	size_t Size(void) const;
	bool IsEmpty(void) const;

	
	void Insert(string name, Animation * animation);
	bool SetSprite(string name, Animation * animation);


	AnimationMap::iterator	GetFirst(void);
	AnimationMap::iterator	GetEnd(void);
	Animation * GetAnimation(string name) const;


	void Clear(void);
	void EraseSprite(string name);
};

#endif