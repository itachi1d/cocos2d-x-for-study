#ifndef SettingScene_h__
#define SettingScene_h__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio\CocoStudio.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio;
class SettingScene : public Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	void backButtonCallBack(cocos2d::Ref* pSender,ui::TouchEventType type);
	void setListener();
	// implement the "static create()" method manually
	CREATE_FUNC(SettingScene);
private:
	Sprite* sound;
};
#endif // SettingScene_h__
