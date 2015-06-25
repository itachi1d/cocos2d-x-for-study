#ifndef _DIJI_UPDATE_
#define _DIJI_UPDATE_
//#include "GameScene.h"
#include "cocos2d.h"
#include <Box2D\Box2D.h>
USING_NS_CC;
class DijiUpdate : public Node
{
public:
	DijiUpdate():timeSum(0),number(0),coutTime(6){};
	void diJiUpdate(float dt, cocos2d::Layer* layer);
	void updateDiji(float dt, cocos2d::Layer* layer);
	void update1(float dt, cocos2d::Layer* layer);
	void update2(float dt, cocos2d::Layer* layer);
	void update3(float dt, cocos2d::Layer* layer);
	void update4(float dt, cocos2d::Layer* layer);
	bool hasDji(std::list<b2Body*>);
	void randomCreateDiJi(cocos2d::Layer* _layer);//����ڲ�ͬ�ص�ˢ���ȼ�0�л�
	CREATE_FUNC(DijiUpdate);
private:
	float timeSum;//��ʱ�����
	float coutTime;//����ɻ����ּ�ʱ��
	int number;//�л�����
};

#endif