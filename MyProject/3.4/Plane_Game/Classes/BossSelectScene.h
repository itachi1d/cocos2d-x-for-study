#ifndef BossSelectScene_h__
#define BossSelectScene_h__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio\CocoStudio.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio;
class BossSelectScene : public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();  
	void back_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void boss1_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void boss2_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void boss3_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void boss4_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	CREATE_FUNC(BossSelectScene);
private:
	Button* boss1;
	Button* boss2;
	Button* boss3;
	Button* boss4;
	ScrollView* scroll;
	Layer* touchlayer;
};
#endif // BossSelectScene_h__