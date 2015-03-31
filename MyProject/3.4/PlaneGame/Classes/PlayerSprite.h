#pragma once
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
	static PlayerSprite* createWithTexture(Texture2D *texture, const Rect& rect, bool rotated=false)
	{
		PlayerSprite *sprite = new PlayerSprite();
		if (sprite && sprite->initWithTexture(texture, rect, rotated))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	void dead();
	b2Body* getBody();
	void setBody(b2Body* body);
	bool fuHuo();
	void OnWuDi();//�����޵���˸����
	void OffWuDi();//�ر��޵���˸����
	void max_open(float dt);
	void max1(float dt);
	void max2(float dt);
	void max3(float dt);

	void maxAnima_content(float dt);
	void maxAnima_finish();
	bool isProtect;//�Ƿ��б�����
	bool isWiDi;//�Ƿ��������޵�״̬
	bool isDead;//�Ƿ�������״̬
	
private:
	b2Body* body;
	float max_time;
	int maxing_sound_id;
};