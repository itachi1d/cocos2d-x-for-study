#ifndef _BOSS_
#define _BOSS_
#include "cocos2d.h"
using namespace cocos2d;
class Boss : public Sprite
{
public:
	Boss();
public:
	static Boss *create(int _guanqia);
	void changeMode();
	void shutBullet(float dt, int _guanqia);
	void shutBullet_1(float dt);
	void shutBullet_2(float dt);
	void shutBullet_3(float dt);
	void shutBullet_4(float dt);
	void boom();
	void beAttackAction();
	void beComeColor(float time);
	float getMaxLife();
	float getLife();
	float subLife(float cout);
	void createBullet(Point shutPos, int bullet_type, float angle, float vec);
	void setModeTime();
	void resetMode(int maxMode);
	float getAngleforPointToPoint(Point, Point);
	CREATE_FUNC(Boss);
public:
	int shut_mode;
	int mode_cout;
public:
	static Boss* createWithSpriteFrame(SpriteFrame *spriteFrame);
    static Boss* createWithSpriteFrameName(const std::string& spriteFrameName);
private:
	Color3B color;
	std::vector<Point> shut_points;
	float life;
	float max_life;
	float whole_mode_time;//用于记录每个射击模式需要持续的时间
	float mode_cout_time;//用于记录当前射击模式持续了多长时间
	float shut_once_time;//射击一次的间隔时间
	float shut_once_cout_time;//设计一次的累加时间
	float shut_once_cout_time_more;//设计一次的累加时间
	float angle1;//记录射击角度
	float angle2;//记录射击角度
	bool flag;//
public:
	std::vector<Point> move_points;
public:
	float width;
	float height;
	float move_time;
	float stand_time;
	float need_move_time;
	bool begin;

	Point next_move;

};

#endif