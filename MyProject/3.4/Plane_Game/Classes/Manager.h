#ifndef _MANAGER_
#define _MANAGER_

#include "cocos2d.h"
using namespace cocos2d;
class Manager
{
public:
	Manager();
	~Manager();
	static Manager* Instance();
public:
	void init_Anima();
	void init_max_anima1();
	void init_maxing_anima1();
	void init_boom_anim();
	void init_Player_anim();
public:
	SpriteFrameCache* frames;
	Vector<SpriteFrame*> maxing;
	Vector<SpriteFrame*> max1_start;
	Vector<SpriteFrame*> max1_content;
	Vector<SpriteFrame*> max1_end;
	Vector<SpriteFrame*> booms;
	Vector<SpriteFrame*> player1;
	Vector<SpriteFrame*> player2;
	Vector<SpriteFrame*> player3;
protected:
private:
	static Manager* manager;
};

#endif // !_MANAGER_
