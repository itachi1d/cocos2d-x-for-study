#ifndef NormalScene_h__
#define NormalScene_h__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio\CocoStudio.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio;
class NormalScene : public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();  
	void back_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void normal1_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void normal2_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void normal3_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void normal4_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	CREATE_FUNC(NormalScene);
};
#endif // NormalScene_h__
