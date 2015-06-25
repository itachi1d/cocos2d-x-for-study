#ifndef Money_h__
#define Money_h__

#include "cocos2d.h"

using namespace cocos2d;

class Money : public Sprite
{
public:
	Money();
	static Money* create(int _type);
	void updatePosition(float dt);
private:
	static Money* createWithSpriteFrameName(const std::string& spriteFrameName);
	static Money* createWithSpriteFrame(SpriteFrame *spriteFrame);
private:
	float angle;
public:
	float vec_x;
	float vec_y;
	int type;
};

#endif // Money_h__