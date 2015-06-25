#include "SettingScene.h"
#include "HelloWorldScene.h"
#include "CanShu.h"

Scene* SettingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SettingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	Node *scene = static_cast<Widget*>(CSLoader::createNode ("SettingScene.csb"));
	addChild(scene);
	Button* back_button = scene->getChildByName<Button*>("back_Button");
	sound = scene->getChildByName<Sprite*>("on");
	if(isSoundOpen)
	{
		sound->setTag(1);
	}
	else
	{
		sound->setTag(2);
		sound->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("off.png"));
	}
	back_button->addTouchEventListener(this, toucheventselector(SettingScene::backButtonCallBack));
	setListener();
	return true;
}

void SettingScene::backButtonCallBack(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		{
			Scene* scene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(scene);
		}
		break;
	default:
		break;
	}
}

void SettingScene::setListener()
{
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event){
		Point touchPoint = this->convertToNodeSpace(touch->getLocation());
		Rect rect = Rect(sound->getPositionX()-sound->getContentSize().width/2, sound->getPositionY()-sound->getContentSize().height/2,
			sound->getContentSize().width, sound->getContentSize().height);
		if(rect.containsPoint(touchPoint))
		{
			if(sound->getTag() == 1)
			{
				sound->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("off.png"));
				sound->setTag(2);
				isSoundOpen = false;
				
			}
			else
			{
				sound->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("on.png"));
				sound->setTag(1);
				isSoundOpen = true;
			}
			
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
