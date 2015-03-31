#ifndef __ANIMAL_SPRITE_H__
#define __ANIMAL_SPRITE_H__
#include "cocos2d.h"

using namespace cocos2d;
class Anmial : public Sprite
{
public:
	Anmial();
	static Anmial* create(int type);
private:
	static Anmial* createWithSpriteFrame(SpriteFrame *spriteFrame, int type);
	static Anmial* createWithSpriteFrameName(const std::string& spriteFrameName, int type);
public:
	void playerRunAnimation();
	void initBuRu();
	int getSpeed();
	void AnimalsContact(Anmial* animal);
	void setSpeed(int _speed);
	int getType();
	bool isbuRu();
private:
	int type;//1.大象。2.猴子。3.鸵鸟。4.斑马。5.骆驼。6.狮子。7.野猪。8.犀牛。9.熊猫。10.恐龙。11.乌龟
	float speed;//基础速度
	float speedVar;//累加速度
	bool buRu;//是否是哺乳动物
		
};

#endif 