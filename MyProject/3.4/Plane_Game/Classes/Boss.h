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
	float whole_mode_time;//���ڼ�¼ÿ�����ģʽ��Ҫ������ʱ��
	float mode_cout_time;//���ڼ�¼��ǰ���ģʽ�����˶೤ʱ��
	float shut_once_time;//���һ�εļ��ʱ��
	float shut_once_cout_time;//���һ�ε��ۼ�ʱ��
	float shut_once_cout_time_more;//���һ�ε��ۼ�ʱ��
	float angle1;//��¼����Ƕ�
	float angle2;//��¼����Ƕ�
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