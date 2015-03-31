#include "HelloWorldScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "CanShu.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;


USING_NS_CC;

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	LabelTTF *loadingFont = LabelTTF::create("Load......", "Arial", 50);
	this->addChild(loadingFont);
	loadingFont->setPosition(visibleSize.width/2, visibleSize.height/2);
	
	//UserDefault::getInstance()->setIntegerForKey("yiGuoGK", 8);
	yiGuoGK = UserDefault::getInstance()->getIntegerForKey("yiGuoGK", 1);
	isSoundOpen = UserDefault::getInstance()->getIntegerForKey("isSoundOpen", true);
    
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/backgound.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("music/jump.OGG");
	SimpleAudioEngine::getInstance()->preloadEffect("music/click.OGG");
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
	TextureCache::getInstance()->addImageAsync("Images/runImages.png",  CC_CALLBACK_1(HelloWorld::loadComplete0, this));
	
    return true;
}

void HelloWorld::loadComplete0(Texture2D *texture)
{
	TextureCache::getInstance()->addImageAsync("Images/bg.png", CC_CALLBACK_1(HelloWorld::loadComplete1, this));	
}

void HelloWorld::loadComplete1(Texture2D *texture)
{
	TextureCache::getInstance()->addImageAsync("Images/items.png", CC_CALLBACK_1(HelloWorld::loadComplete2, this));	
}

void HelloWorld::loadComplete2(Texture2D *texture)
{
	TextureCache::getInstance()->addImageAsync("Images/buttons.png", CC_CALLBACK_1(HelloWorld::loadComplete3, this));
}

void HelloWorld::loadComplete3(Texture2D *texture)
{
	this->scheduleOnce(schedule_selector(HelloWorld::oneUpdate), 1.0f);
}

void HelloWorld::oneUpdate(float dt)
{
	auto scene = MainMenuScene::createScene();
	auto sceneAction = TransitionFadeTR::create(1, scene);
	//Ìæ»»·½Ê½ÇÐ»»³¡¾°
	Director::getInstance()->replaceScene(sceneAction);
}


