/*
 * author: koutsop
 */
//Na diagrayw thn PrintSpriteHolder
#ifndef SPRITEHOLDER_H
#define SPRITEHOLDER_H

#include <map>
#include <list>
#include <string>

#include "KeyLogger.h"
#include "Sprite.h"

typedef std::map<string, Sprite *> SpriteMap;


class SpriteHolder {
private:
	std::list<Sprite *> deleted;
	SpriteMap sprites;
	
	/* @target: Na diagrafei mesa apo to map ena sugkekrimeno sprite.
	 * @param : To onoma tou sprite pou prokite na diagrafei.
	 */
	void EraseSprite(string name);

public:
	SpriteHolder(void){}
	~SpriteHolder(void);

	/* @target: Na epustrefei to sunolo ton sprites pou uparxoun ston holder.
	 * @return: To sunolo ton sprites.
	 */
	size_t Size(void);
	
	/* @target: Na diagrafei ola ta sprites.
	 */
	void Clear(void);
	
	/* @target: Na elegxei an uparxoun stoixia sto holder h' oxi.
	 * @return: True an den exei stoixeia alios false.
	 */
	bool IsEmpty(void);
	
	/* @target: Na 8etei ena sigkekrimeno sprite pou uparxei ston holder.
	 * @param : name einai to onoma tou sprite pou 8eloume na kanoume thn alagh
	 *		  :sptire einai to eno sprite.
	 */
	void SetSprite(string name, Sprite * sprite);
	

	/* @target: Na epistrefei to prwto stoikxeio tou holder.
	 * @return: To prwto stoixio tou holder.
	 */
	SpriteMap::iterator	GetFirst(void);
	
	/* @target: Na epistrefei ena stoixeio meta apo to teleuteo stoixeio tou holder.
	 * @return: Ena stoixeio meta to teleuteo stoixeio tou holder
	 */
	SpriteMap::iterator	GetEnd(void);
	
	/* @target: Na briskei ena sprite mesa sto holder me ena sigkekrimeno name.
	 * @parma : name to onoma tou sprite pros anazitish.
	 * @return: Enan ptr sto sugkekrimeno sprite.
	 */
	Sprite * GetSprite(string name);
	
	/* @target: Na isagh ena kenourio sprite ston holder me ena kainourio onoma.
	 * @parma : name to onoma tou sprite pros isagwgh, sprite to sprite pou 8a 
	 *		  :eisagoume ston holder.
	 */
	void Insert(string name, Sprite * sprite);

	/* @target: Na bazei ena sprite sthn lista pou einai pros diagrafh
	 */
	void MarkAsDeleted(string name);

	void DeleteFromList(Sprite * sprite) { deleted.remove(sprite); } 
	std::list<Sprite *>::iterator GetEndDeleded(void);
	std::list<Sprite *>::iterator GetFirstDeleded(void);

	//gia debug skopous xrisimeuei mono
	void PrintSpriteHolder();
};

#endif