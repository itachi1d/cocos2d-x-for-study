#ifndef _FRUIT_
#define _FRUIT_
#include "cocos2d.h"
#include "MyPoint.h"

using namespace cocos2d;

class Fruit : public Sprite
{
public:
	Fruit();
	static Fruit* create(int type);
	void set_world_point(int _x, int _y);
	void run_to_point(MyPoint, bool isback);//使水果运动到一个指定的点
	void removeAnima();//水果消失以及消失的动画
	void updatePoint();//更新世界坐标与真实坐标的位置
	void updatePoint_with_xc();
	void remove();
	std::string getFileName();
private:
	static Fruit* createWithSpriteFrame(SpriteFrame *spriteFrame, int type);
	static Fruit* createWithSpriteFrameName(const std::string& spriteFrameName, int type);

public:
	int type;
	MyPoint world_point;
	bool is_user_contact;
private:
	std::string file_name;
};

#endif