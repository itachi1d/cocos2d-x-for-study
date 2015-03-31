// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2015-03-15 16:37:22 by jiangtao> */

/* @file Main_Layer.cpp
 * $Id: Main_Layer.cpp 2015-03-15 08:30:23 jiangtao Exp $
 *
 * @author:Stone Jiang<jiangtao@tao-studio.net>
 */
//===========================================================================


#include "MainMenuLayer.h"
#include "LoadScene.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "ui/CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "Tool.h"
using namespace cocostudio; 
using namespace cocos2d::ui;

MainMenuLayer::MainMenuLayer()
{
}
MainMenuLayer::~MainMenuLayer()
{
}

std::string MainMenuLayer::get_csb_filename()
{
	return "MainScene.csb";
}

void MainMenuLayer::set_callback(Node *root)
{
  {
    std::string node_name ="Button_1";
    auto bt = root->getChildByName<Button*> (node_name);
    if (bt)
    {
      bt->addTouchEventListener(this, toucheventselector(MainMenuLayer::highScore));
    }
  }
  
  {
    std::string node_name ="Button_2";
    auto bt = root->getChildByName<Button*> (node_name);
    if (bt)
    {
      bt->addTouchEventListener(this, toucheventselector(MainMenuLayer::gameStart));
    }
  }
  {
    std::string node_name ="Button_4";
    auto bt = root->getChildByName<Button*> (node_name);
    if (bt)
    {
      bt->addTouchEventListener(this, toucheventselector(MainMenuLayer::shop));
    }
  }
	timeline::ActionTimeline* action = CSLoader::createTimeline(get_csb_filename());
	root->runAction(action);
	action->gotoFrameAndPlay(0, -1);

}

void MainMenuLayer::highScore(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	Widget* HighMenu;
	TextField* highScoreText;
	Button*button1;
	timeline::ActionTimeline* action;
	 switch (type)
	{
	 case ui::TouchEventType::TOUCH_EVENT_ENDED:
		//最高分界面
		HighMenu = static_cast<Widget*>(CSLoader::createNode ("HighScoreScene.csb"));
		this->addChild(HighMenu, 10);
		HighMenu->setTag(1);
		action = CSLoader::createTimeline("HighScoreScene.csb");
		HighMenu->runAction(action);
		action->gotoFrameAndPlay(0, -1);
		highScoreText = HighMenu->getChildByName<TextField*>("highScoreText");
		highScoreText->setText(Tool::toString(UserDefault::getInstance()->getIntegerForKey("highScore", 1)));
		button1 = HighMenu->getChildByName<Button*>("Button_1");
		button1->addTouchEventListener(this, toucheventselector(MainMenuLayer::returnMain));
		break;
	default:
		break;
	}
}

void MainMenuLayer::gameStart(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	Scene *scene;
	  switch (type)
		{
		 case ui::TouchEventType::TOUCH_EVENT_ENDED:
			//游戏开始界面
			scene = LoadScene::createScene();
			Director::getInstance()->replaceScene(scene);
			break;
		default:
			break;
		}

}

void MainMenuLayer::returnMain(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	  switch (type)
		{
		 case ui::TouchEventType::TOUCH_EVENT_ENDED:
			 this->removeChildByTag(1);
			break;
		default:
			break;
		}
}

void MainMenuLayer::shop(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	Widget* shopMenu;
	Button* closeButton;
	Button* buyButton1;
	Button* buyButton2;
	Text* goldText;
	Text* starText;
	switch (type)
	{
		case ui::TouchEventType::TOUCH_EVENT_ENDED:
			shopMenu = static_cast<Widget*>(CSLoader::createNode ("ShopScene.csb"));
			this->addChild(shopMenu, 10);
			shopMenu->setTag(1);
			closeButton = shopMenu->getChildByName<Button*>("close_Button");
			buyButton1 = shopMenu->getChildByName<Button*>("buy_Button_1");
			buyButton2 = shopMenu->getChildByName<Button*>("buy_Button_2");
			buyButton1->setTag(1);
			buyButton2->setTag(2);
			closeButton->addTouchEventListener(this, toucheventselector(MainMenuLayer::returnMain));
			buyButton1->addTouchEventListener(this, toucheventselector(MainMenuLayer::buy));
			buyButton2->addTouchEventListener(this, toucheventselector(MainMenuLayer::buy));

			goldText = (Text*)shopMenu->getChildByName("goldText");
			starText = (Text*)shopMenu->getChildByName("starText");
			goldText->setText(Tool::toString(UserDefault::getInstance()->getIntegerForKey("gold", 0)));
			starText->setText(Tool::toString(UserDefault::getInstance()->getIntegerForKey("star", 3)));
		break;
	default:
		break;
	}
}

void MainMenuLayer::buy(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	int goldNumber;
	Sprite* gold;
	Text* goldText;
	Text* starText;
	int needGold;
	int addStar;
	switch (type)
	{
		case ui::TouchEventType::TOUCH_EVENT_ENDED:
			goldNumber = UserDefault::getInstance()->getIntegerForKey("gold", 0);
			if(((Node*)pSender)->getTag() == 1)
			{
				needGold = 100;
				addStar = 1;
			}
			else
			{
				needGold = 400;
				addStar = 5;
			}
			if(goldNumber >= needGold)
			{
				goldNumber -= needGold;
				UserDefault::getInstance()->setIntegerForKey("gold", goldNumber);
				UserDefault::getInstance()->setIntegerForKey("star", UserDefault::getInstance()->getIntegerForKey("star", 3)+addStar);
				goldText = (Text*)this->getChildByTag(1)->getChildByName("goldText");
				starText = (Text*)this->getChildByTag(1)->getChildByName("starText");
				goldText->setText(Tool::toString(goldNumber));
				starText->setText(Tool::toString(UserDefault::getInstance()->getIntegerForKey("star", 3)));
				
			}
			else
			{
				gold = (Sprite*)this->getChildByTag(1)->getChildByName("gold");
				gold->runAction(Sequence::create(ScaleTo::create(0.1f, 2.0f), ScaleTo::create(0.1f, 0.5f), ScaleTo::create(0.1f, 1), NULL));
			}
		break;
	default:
		break;
	}
}
