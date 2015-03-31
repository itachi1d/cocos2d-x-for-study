#include "LoadScene.h"
#include "ResourceManager.h"
#include "Tool.h"
#include "GameLayer.h"

Scene* LoadScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	ResourceManager::Instance()->loadJson();//加载Json
	Sprite *sprite = Sprite::createWithSpriteFrameName("loading_0.png");
	this->addChild(sprite, 5);
	sprite->setPosition(240, 160);
	loadingbar = ProgressTimer::create(Sprite::create("pic/tool/loadingbar.png"));
	loadingbar->setBarChangeRate(Point(1, 0));//设置进度条的变化方向（横）
	loadingbar->setType(ProgressTimer::Type::BAR);
	loadingbar->setMidpoint(Point(0, 0));//设置增长中心 
	loadingbar->setPercentage(0);
	loadingbar->setPosition(240, 100);
	addChild(loadingbar, 10);
	MaxFiles = 12;
	sum = 0;
	loadResource();
	scheduleUpdate();
	return true;
}

void LoadScene::update(float dt)
{
	if(loadingbar->getPercentage() >= sum)
		loadingbar->setPercentage(sum);
	else if(loadingbar->getPercentage() >= 100)
	{
		unscheduleUpdate();
		returnToGameLayer();
	}
	else
		loadingbar->setPercentage(loadingbar->getPercentage()+0.8f);
}

void LoadScene::loadResource()
{
	i = 1;
	j = 1;
	int x = 1;
	while(true)
	{
		std::string name;
		name = "res/map" + Tool::toString(x) +".png";
		if(!FileUtils::getInstance()->isFileExist(name))
			break;
		ResourceManager::Instance()->texture->addImageAsync(name, CC_CALLBACK_1(LoadScene::plistImageAsyncCallback1, this));
		x += 1;
	}
	int y = 1;
	while(true)
	{
		std::string name;
		name = "res/map" + Tool::toString(y) +"_1.png";
		if(!FileUtils::getInstance()->isFileExist(name))
			break;
		ResourceManager::Instance()->texture->addImageAsync(name, CC_CALLBACK_1(LoadScene::plistImageAsyncCallback2, this));
		y += 1;
	}
}

void LoadScene::plistImageAsyncCallback1(cocos2d::Texture2D* texture)
{
	std::string name;
	name = "res/map" + Tool::toString(i) +".plist";
	ResourceManager::Instance()->frameCache->addSpriteFramesWithFile(name, texture);
	sum += (1.0f/(float)MaxFiles)*100;
	i += 1;
}

void LoadScene::plistImageAsyncCallback2(cocos2d::Texture2D* texture)
{
	std::string name;
	name = "res/map" + Tool::toString(j) +"_1.plist";
	ResourceManager::Instance()->frameCache->addSpriteFramesWithFile(name, texture);
	sum += (1.0f/(float)MaxFiles)*100;
	j += 1;
}

void LoadScene::returnToGameLayer()
{
	auto scene = GameLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}