#include "BossSelectScene.h"


#include "CanShu.h"
#include "Tool.h"
#include "LoadingScene.h"
#include "SelectScene.h"


cocos2d::Scene* BossSelectScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BossSelectScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool BossSelectScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Node *scene = static_cast<Widget*>(CSLoader::createNode ("BossScene.csb"));
	addChild(scene);
	scroll = scene->getChildByName<ScrollView*>("ScrollView");
	for (int i = 1; i <= through_gq; ++i)
	{
		scroll->getChildByName("BOSS_"+Tool::toString(i)+"_share")->setVisible(false);
	}
	boss1 = (Button*)scroll->getChildByName("BOSS_1");
	boss2 = (Button*)scroll->getChildByName("BOSS_2");
	boss3 = (Button*)scroll->getChildByName("BOSS_3");
	boss4 = (Button*)scroll->getChildByName("BOSS_4");
	boss1->addTouchEventListener(this, toucheventselector(BossSelectScene::boss1_button));
	boss2->addTouchEventListener(this, toucheventselector(BossSelectScene::boss2_button));
	boss3->addTouchEventListener(this, toucheventselector(BossSelectScene::boss3_button));
	boss4->addTouchEventListener(this, toucheventselector(BossSelectScene::boss4_button));
	Button* back_button = scene->getChildByName<Button*>("back_Button");
	back_button->addTouchEventListener(this, toucheventselector(BossSelectScene::back_button));
	touchlayer = Layer::create();
	addChild(touchlayer);
	return true;
}
void BossSelectScene::back_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		{
			_eventDispatcher->removeAllEventListeners();
			Scene* scene = SelectScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}		
		break;
	default:
		break;
	}
}
void BossSelectScene::boss1_button(cocos2d::Ref* pSender,ui::TouchEventType type)
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
void BossSelectScene::boss2_button(cocos2d::Ref* pSender,ui::TouchEventType type)
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
void BossSelectScene::boss3_button(cocos2d::Ref* pSender,ui::TouchEventType type)
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

void BossSelectScene::boss4_button(cocos2d::Ref* pSender,ui::TouchEventType type)
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

