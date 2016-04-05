#pragma once
#include "cocos2d.h"
#include "GameSceneManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class MainLayer : public Layer
{
public:
	Sprite* bg;
	NodeGrid* effectNode;
	GameSceneManager* sceneManager;
	static bool musicFlag;
	static bool soundFlag;
	
public:
	virtual bool init();
	void initBtns(Node* rootNode);
	int random();
	CREATE_FUNC(MainLayer);
private:
	Button* m_start_button;
	Button* m_setting_button;
	Button* m_rank_button;
	Button* m_help_button;
	Button* m_exit_button;
private:
	void onBtnClickHander(Ref*pSender, Widget::TouchEventType type);
};