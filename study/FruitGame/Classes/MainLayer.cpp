#include "MainLayer.h"
#include "GameTitle.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool MainLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("MainLayer.csb");
	addChild(rootNode);
	initBtns(rootNode);

	GameTitle *effect = GameTitle::create();
	this->addChild(effect);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/playscene.mp3", true);

	Sprite* floor = static_cast<Sprite*>(rootNode->getChildByName("floor"));
	Sprite* bg = static_cast<Sprite*>(rootNode->getChildByName("bg"));
	float nummm = bg->getContentSize().width - floor->getContentSize().width;
	floor->runAction(RepeatForever::create(
			Sequence::create(
			MoveTo::create(0.9, Point(bg->getContentSize().width - floor->getContentSize().width, floor->getPositionY())),
			MoveTo::create(0, Point(0, floor->getPositionY())),
			NULL
			)
		));
	
	return true;
}

void MainLayer::initBtns(Node* rootNode)
{
	m_start_button = static_cast<Button*>(rootNode->getChildByName("m_start_button"));
	m_help_button = static_cast<Button*>(rootNode->getChildByName("m_help_button"));
	m_exit_button = static_cast<Button*>(rootNode->getChildByName("m_exit_button"));
	m_rank_button = static_cast<Button*>(rootNode->getChildByName("m_rank_button"));
	m_setting_button = static_cast<Button*>(rootNode->getChildByName("m_setting_button"));

	m_start_button->addTouchEventListener(CC_CALLBACK_2(MainLayer::onBtnClickHander, this));
	m_help_button->addTouchEventListener(CC_CALLBACK_2(MainLayer::onBtnClickHander, this));
	m_exit_button->addTouchEventListener(CC_CALLBACK_2(MainLayer::onBtnClickHander, this));
	m_rank_button->addTouchEventListener(CC_CALLBACK_2(MainLayer::onBtnClickHander, this));
	m_setting_button->addTouchEventListener(CC_CALLBACK_2(MainLayer::onBtnClickHander, this));
}

void MainLayer::onBtnClickHander(Ref*pSender, Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
		return;
	if (pSender == m_start_button)
	{
		GameSceneManager::getInstance()->goToGameScene();
	}
	else if (pSender == m_start_button)
	{

	}
	else if (pSender == m_help_button)
	{

	}
	else if (pSender == m_exit_button)
	{
		Director::getInstance()->end();
	}
	else if (pSender == m_setting_button)
	{
		GameSceneManager::getInstance()->goToSetScene();
	}
	else if (pSender == m_rank_button)
	{
		GameSceneManager::getInstance()->goToRankScene();
	}
}
