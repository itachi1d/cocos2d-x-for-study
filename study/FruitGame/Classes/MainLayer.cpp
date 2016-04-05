#include "MainLayer.h"


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

	effectNode = NodeGrid::create();
	this->addChild(effectNode);
	Sprite* title = Sprite::create("pic/title.png");
	title->setPosition(Point(270, 600));
	effectNode->addChild(title);
	effectNode->runAction(RepeatForever::create(Ripple3D::create(2.0f, Size(32, 24), title->getPosition(), 360, 2, 5)));
	
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

	}
}
