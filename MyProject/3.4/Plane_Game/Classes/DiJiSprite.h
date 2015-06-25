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
	void shutBullet(int mode);//����ӵ�
	void shutBullet_type0(int mode);//����Ϊ0�ĵл����ӵ�
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
	bool isRightShut;//�ж��Ƿ�����ǹ�����,�������ұ任���
	float changeShutTime;//��ǹ������ĳ���ʱ��
	bool isBoom;
	float addAngle;
	float shutTimeCout;//����ӵ���ʱ�����ۻ�����
	float shutTimeSum;//�ӷɻ�������ʼ�������ۼӵ�ʱ��
	float startShutTime;//ʲôʱ����Կ�ʼ���
	float everyShutTime;//����������ӵ����ʱ��
	bool isCanShut;//�Ƿ�������
	Point shutPoint1;//����ӵ���λ��1
	Point shutPoint2;//����ӵ���λ��2

	float shutAngle1;//����Ƕ�
	float shutAngle2;//����Ƕ�

	Sprite* shutFrame1;
	Sprite* shutFrame2;

	CREATE_FUNC(DiJiSprite);

private:
	Color3B color;
	
};

#endif