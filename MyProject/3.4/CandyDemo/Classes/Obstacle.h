#ifndef _OBSTACLE_
#define _OBSTACLE_
#include "cocos2d.h"
#include "MyPoint.h"

using namespace cocos2d;

class Obstacle : public Sprite
{
public:
	Obstacle();
	static Obstacle* create(MyPoint);
	void set_world_point(int _x, int _y);

private:
	static Obstacle* createWithSpriteFrame(SpriteFrame *spriteFrame, MyPoint);
	static Obstacle* createWithSpriteFrameName(const std::string& spriteFrameName, MyPoint);

public:
	MyPoint world_point;
};

#endif