#pragma once
#include "cocos2d.h"
#include "GameSceneManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class RankLayer : public Layer
{
public:
	std::string scores[5];
	Label* labels;
	Sprite* labelSprite;
	Button* m_next_button;
	Button* m_menu_button;
	GameSceneManager* sceneManager;
	//区分水果还是小鸟的排行
	enum TYPE
	{
		FRUIT,
		BIRD
	};
public:
	virtual bool init();
	void save(int);
	void load();
	void initTile(TYPE);
	void menuCallBack0(Ref*pSender, Widget::TouchEventType type);
	CREATE_FUNC(RankLayer);
private:
	TYPE m_id;
};