#include "SetLayer.h"
#include "MainDataMgr.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool SetLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto node = CSLoader::createNode("SetLayer.csb");
	this->addChild(node);
	music_btn = static_cast<CheckBox*>(node->getChildByName("music_btn"));
	sound_btn = static_cast<CheckBox*>(node->getChildByName("sound_btn"));
	menu_btn = static_cast<Button*>(node->getChildByName("menu_btn"));
	music_btn->addEventListenerCheckBox(this, checkboxselectedeventselector(SetLayer::selectedEvent));
	menu_btn->addClickEventListener(CC_CALLBACK_1(SetLayer::menuCallBack0, this));
	return true;
}

void SetLayer::selectedEvent(Ref* pSender, CheckBox::EventType type)
{
	if (pSender == music_btn)
	{
		switch (type)
		{
		case cocos2d::ui::CheckBox::EventType::SELECTED:
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			MainDataMgr::getInstance()->musicFlag = false;
			break;
		case cocos2d::ui::CheckBox::EventType::UNSELECTED:
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			MainDataMgr::getInstance()->musicFlag = true;
			break;
		default:
			break;
		}
	}
	else if (pSender == sound_btn)
	{
		switch (type)
		{
		case cocos2d::ui::CheckBox::EventType::SELECTED:
			MainDataMgr::getInstance()->soundFlag = false;
			break;
		case cocos2d::ui::CheckBox::EventType::UNSELECTED:
			MainDataMgr::getInstance()->soundFlag = true;
			break;
		default:
			break;
		}
	}
}

void SetLayer::menuCallBack0(Ref*pSender)
{
	GameSceneManager::getInstance()->goToMainScene();
}
