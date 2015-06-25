#include "NormalScene.h"
#include "SelectScene.h"
#include "CanShu.h"
#include "LoadingScene.h"
#include "Tool.h"

cocos2d::Scene* NormalScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = NormalScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool NormalScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	Node *scene = static_cast<Widget*>(CSLoader::createNode ("NormalScene.csb"));
	addChild(scene);
	Button* back_button = scene->getChildByName<Button*>("back_Button");
	Button* button1 = scene->getChildByName<Button*>("Button_1");
	Button* button2 = scene->getChildByName<Button*>("Button_2");
	Button* button3 = scene->getChildByName<Button*>("Button_3");
	Button* button4 = scene->getChildByName<Button*>("Button_4");
	back_button->addTouchEventListener(this, toucheventselector(NormalScene::back_button));
	button1->addTouchEventListener(this, toucheventselector(NormalScene::normal1_button));
	button2->addTouchEventListener(this, toucheventselector(NormalScene::normal2_button));
	button3->addTouchEventListener(this, toucheventselector(NormalScene::normal3_button));
	button4->addTouchEventListener(this, toucheventselector(NormalScene::normal4_button));

	button1->setEnabled(false);
	button1->setBright(false);
	button2->setEnabled(false);
	button2->setBright(false);
	button3->setEnabled(false);
	button3->setBright(false);
	button4->setEnabled(false);
	button4->setBright(false);

	if(through_gq >= 0)
	{
		button1->setEnabled(true);
		button1->setBright(true);
	}
	if(through_gq >= 1)
	{
		button2->setEnabled(true);
		button2->setBright(true);
	}
	if(through_gq >= 2)
	{
		button3->setEnabled(true);
		button3->setBright(true);
	}
	if(through_gq >= 3)
	{
		button4->setEnabled(true);
		button4->setBright(true);
	}
	return true;
}

void NormalScene::back_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		{			
			Scene* scene = SelectScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}		
		break;
	default:
		break;
	}
}

void NormalScene::normal1_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		{
			guanqia = 1;
			Scene* scene = LoadingScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}		
		break;
	default:
		break;
	}
}
void NormalScene::normal2_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		{
			guanqia = 2;
			Scene* scene = LoadingScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}		
		break;
	default:
		break;
	}
}
void NormalScene::normal3_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		{
			guanqia = 3;
			Scene* scene = LoadingScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}		
		break;
	default:
		break;
	}
}
void NormalScene::normal4_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		{
			guanqia = 4;
			Scene* scene = LoadingScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}		
		break;
	default:
		break;
	}
}
