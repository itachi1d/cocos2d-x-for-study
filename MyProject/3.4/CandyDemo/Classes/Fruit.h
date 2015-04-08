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
	void change_x_pos(MyPoint);
	void updatePointandopenmove();
	void updatePoint_with_xc();
	void updatePoint_with_noxc();
	void remove();
	std::string getFileName();
	void level_up(int _level);
	void open_move();
	void off_move();
private:
	static Fruit* createWithSpriteFrame(SpriteFrame *spriteFrame, int type);
	static Fruit* createWithSpriteFrameName(const std::string& spriteFrameName, int type);

public:
	int type;
	int level;
	MyPoint world_point;
	bool is_user_contact;
	bool isMove;
	float speed;
	bool is_change_pos;
private:
	std::string file_name;
};

#endif