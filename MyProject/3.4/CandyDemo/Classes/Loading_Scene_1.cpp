#include "Loading_Scene_1.h"
#include "Manager/Manager.h"
#include "Tool.h"
#include "Perf.h"
#include "HelloWorldScene.h"

Scene* Loading_Scene_1::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Loading_Scene_1::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Loading_Scene_1::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	srand((unsigned)time(NULL));
	loadingbar = ProgressTimer::create(Sprite::create("pic/loadingbar.png"));
	loadingbar->setBarChangeRate(Point(1, 0));//设置进度条的变化方向（横）
	loadingbar->setType(ProgressTimer::Type::BAR);
	loadingbar->setMidpoint(Point(0, 0));//设置增长中心 
	loadingbar->setPercentage(0);
	loadingbar->setPosition(240, 100);
	addChild(loadingbar, 10);
	MaxFiles = 1;
	sum = 0;
	loadResource();
	scheduleUpdate();
	return true;
}

void Loading_Scene_1::update(float dt)
{
	if(loadingbar->getPercentage() >= sum)
		loadingbar->setPercentage(sum);
	if(loadingbar->getPercentage() >= 100)
	{
		unscheduleUpdate();
		returnToGameLayer();
	}
	else
		loadingbar->setPercentage(loadingbar->getPercentage()+0.8f);
}

void Loading_Scene_1::loadResource()
{
	i = 0;
	int x = 0;
	while(true)
	{
		std::string name;
		name = "pic/" + Tool::toString(x) +".png";
		if(!FileUtils::getInstance()->isFileExist(name))
			break;
		Manager::Instance()->texture->addImageAsync(name, CC_CALLBACK_1(Loading_Scene_1::plistImageAsyncCallback1, this));
		x += 1;
	}
}

void Loading_Scene_1::plistImageAsyncCallback1(cocos2d::Texture2D* texture)
{
	std::string name;
	name = "pic/" + Tool::toString(i) +".plist";
	Manager::Instance()->frames->addSpriteFramesWithFile(name, texture);
	sum += (1.0f/(float)MaxFiles)*100;
	i += 1;
}


void Loading_Scene_1::returnToGameLayer()
{
	Manager::Instance()->init_map();
	
	auto scene = Game_Scene_1::createScene();
	Director::getInstance()->replaceScene(scene);
}