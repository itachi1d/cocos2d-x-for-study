#ifndef _DIJI_
#define _DIJI_

#include "cocos2d.h"

USING_NS_CC;

class DiJiSprite : public Sprite
{
public:
	DiJiSprite():level(0),shutMode(0),life(level*30 + 20),addAngle(-1),isBoom(false),isChange(false),flag(true)
		,changeAngleRect(0, 0, 0, 0),shutTimeCout(0),shutTimeSum(0),startShutTime(4),isCanShut(false)
		,shutFrame1(nullptr),shutFrame2(nullptr),everyShutTime(0),changeShutTime(0)
	{}
	~DiJiSprite();
	static DiJiSprite* create(int type);
	static DiJiSprite* createWithSpriteFrameName(const std::string& spriteFrameName);
	static DiJiSprite* createWithSpriteFrame(SpriteFrame *spriteFrame);

	void setLevel(int _level);
	void setAddAngle(float _addAngle);
	void beAttackAction();
	void beComeColor(float time);
	void showShut(Layer *layer, int pointNumber);
	void hideShut(float dt);
	void updateShutPoint();
	void shut_Bullet(float dt);
	void shutBullet(int mode);//射击子弹
	void shutBullet_type0(int mode);//类型为0的敌机射子弹
	void shutBullet_type1(int mode);
	void shutBullet_type2(int mode);
	void shutBullet_type3(int mode);
	void shutBullet_type4(int mode);

	void createBullet(Layer *layer,Point shutPos, int bullet_type, float angle, float vec);

	int level;
	int shutMode;
	float life;
	float veclecty;
	Rect changeAngleRect;
	bool isChange;
	bool flag;
	bool angleFlag;
	bool isRightShut;//判断是否是又枪管射击,用来左右变换射击
	float changeShutTime;//换枪管射击的持续时间
	bool isBoom;
	float addAngle;
	float shutTimeCout;//射出子弹的时间间隔累积变量
	float shutTimeSum;//从飞机创建开始到现在累加的时间
	float startShutTime;//什么时候可以开始射击
	float everyShutTime;//连续射击的子弹间隔时间
	bool isCanShut;//是否可以射击
	Point shutPoint1;//射击子弹的位置1
	Point shutPoint2;//射击子弹的位置2

	float shutAngle1;//射击角度
	float shutAngle2;//射击角度

	Sprite* shutFrame1;
	Sprite* shutFrame2;

	CREATE_FUNC(DiJiSprite);

private:
	Color3B color;
	
};

#endif