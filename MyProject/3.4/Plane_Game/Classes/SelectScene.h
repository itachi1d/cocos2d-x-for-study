#ifndef _SELECT_SCENE_
#define _SELECT_SCENE_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
class SelectScene : public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();  

	void setTouchListener();
	void stopAllButton();
	void show_plane(int type);
	void normal_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void boss_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void back_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void update(float dt);

	CREATE_FUNC(SelectScene);
private:
	int select_plane;
	float stateTime;
	float shutTime;
	Layer* plane_show_layer;
	ClippingRectangleNode* cliping;

	Sprite *plane1;
	Sprite *plane2;
	Sprite *plane3;
	Sprite *plane1_share;
	Sprite *plane2_share;
	Sprite *plane3_share;
	Sprite *plane1_button;
	Sprite *plane2_button;
	Sprite *plane3_button;
};


#endif