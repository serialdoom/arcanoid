/*
 * author: koutsop
 */

#ifndef ANIMATION_H
#define ANIMATION_H

typedef signed char		offset_t;
typedef unsigned short	delay_t;
typedef unsigned short	animid_t;

class Animation  {
private:
	animid_t id;

public:
	
	/* @return: To id tou Animation*/
	animid_t GetId (void) { return id; }
	
	/* @target: Na dimiourgri ena deep clone tou animation me new id.
	 * @param : To to new id pou 8a exei to clone Animation pou 8a dimiourgi8ei
	 * @return: To newClone Animation
	 */
	virtual Animation* Clone (animid_t newId) const = 0;
	
	Animation (animid_t _id) : id(_id){}
	virtual ~Animation(){}
};


#endif