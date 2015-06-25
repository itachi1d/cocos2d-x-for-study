#include "HelloWorldScene.h"
#include "LoadingScene.h"
#include "SelectScene.h"
#include "ui/CocosGUI.h"
#include "SettingScene.h"

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Widget *scene = static_cast<Widget*>(CSLoader::createNode ("MainScene.csb"));
	Node *title = static_cast<Widget*>(CSLoader::createNode ("TitleScene.csb"));
	timeline::ActionTimeline* action = CSLoader::createTimeline("MainScene.csb");
	timeline::ActionTimeline* titleAction = CSLoader::createTimeline("TitleScene.csb");
	addChild(scene);
	addChild(title);
	scene->runAction(action);
	title->runAction(titleAction);

	action->gotoFrameAndPlay(0, 0);
	titleAction->gotoFrameAndPlay(0, -1);
	
	Button *start_button = scene->getChildByName<Button*>("start_button");
	start_button->addTouchEventListener(this, toucheventselector(HelloWorld::startButtonCallBack));

	Button *set_button = scene->getChildByName<Button*>("set_button");
	set_button->addTouchEventListener(this, toucheventselector(HelloWorld::setButtonCallBack));
	//scheduleUpdate();

    return true;
}

void HelloWorld::update(float dt)
{
	if(jindutiao->getPercentage() >= sum)
		jindutiao->setPercentage(sum);
	else if(jindutiao->getPercentage() >= 100)
		unscheduleUpdate();
	else
		jindutiao->setPercentage(jindutiao->getPercentage()+0.8f);
}

void HelloWorld::startButtonCallBack(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	Scene* scene;
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		//scene = LoadingScene::createScene();
		scene = SelectScene::createScene();
		cocos2d::Director::getInstance()->replaceScene(scene);
		break;
	default:
		break;
	}
}

void HelloWorld::setButtonCallBack(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	Scene* scene;
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		//scene = LoadingScene::createScene();
		scene = SettingScene::createScene();
		cocos2d::Director::getInstance()->replaceScene(scene);
		break;
	default:
		break;
	}
}





