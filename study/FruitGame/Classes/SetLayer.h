#pragma one
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameSceneManager.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class SetLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(SetLayer);
public:
	GameSceneManager* sceneManager;
private:
	CheckBox* music_btn;
	CheckBox* sound_btn;
	Button* menu_btn;
private:
	void selectedEvent(Ref* pSender, CheckBox::EventType type);
	void menuCallBack0(Ref*pSender);
};