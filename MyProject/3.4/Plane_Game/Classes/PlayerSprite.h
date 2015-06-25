#ifndef _PLAYER_
#define _PLAYER_

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocos2d;

class PlayerSprite : public Sprite
{
public:
	PlayerSprite():isProtect(false),isWiDi(false),isDead(false),max_time(0){}
	static PlayerSprite* create(int type);
private:
	static PlayerSprite* createWithSpriteFrame(SpriteFrame *spriteFrame);
	static PlayerSprite* createWithSpriteFrameName(const std::string& spriteFrameName);
public:
	void dead();
	b2Body* getBody();
	void setBody(b2Body* body);
	bool fuHuo();
	void OnWuDi();//开启无敌闪烁动画
	void OffWuDi();//关闭无敌闪烁动画
	void max_open(float dt);
	void max1(float dt);
	void max2(float dt);
	void max3(float dt);

	void maxAnima_content(float dt);
	void maxAnima_finish();
	bool isProtect;//是否有保护盾
	bool isWiDi;//是否处于隐身无敌状态
	bool isDead;//是否处于死亡状态
	
private:
	b2Body* body;
	float max_time;
	unsigned int maxing_sound_id;
};
#endif