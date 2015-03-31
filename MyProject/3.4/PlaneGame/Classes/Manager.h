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
	void init_max_anima1();
	void init_maxing_anima1();
public:
	SpriteFrameCache* frames;
	Vector<SpriteFrame*> maxing;
	Vector<SpriteFrame*> max1_start;
	Vector<SpriteFrame*> max1_content;
	Vector<SpriteFrame*> max1_end;
protected:
private:
	static Manager* manager;
};

#endif // !_MANAGER_
