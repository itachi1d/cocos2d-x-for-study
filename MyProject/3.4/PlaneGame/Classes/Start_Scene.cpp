#include "Start_Scene.h"
#include "cocostudio\CocoStudio.h"
#include "HelloWorldScene.h"
using namespace cocos2d::ui;
using namespace cocostudio;
Scene* StartScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool StartScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	number = 0;
	Node *scene = static_cast<Widget*>(CSLoader::createNode ("StartLoading.csb"));
	timeline::ActionTimeline* action = CSLoader::createTimeline("StartLoading.csb");
	addChild(scene);
	scene->runAction(action);
	action->gotoFrameAndPlay(0, -1);
	this->scheduleOnce(schedule_selector(StartScene::startLoading), 1);
	return true;
}

void StartScene::startLoading(float dt)
{
	loadingGameDate();
}
void StartScene::loadingGameDate()
{
	switch (number)
	{
	case 0:
		TextureCache::getInstance()->addImageAsync("res/title.png",CC_CALLBACK_0(StartScene::loadingGameDate, this));
		break;
	case 1:
		TextureCache::getInstance()->addImageAsync("res/UI.png", CC_CALLBACK_0(StartScene::loadingGameDate, this));
		break;
	case 2:
		TextureCache::getInstance()->addImageAsync("lizi/stars.png", CC_CALLBACK_0(StartScene::loadingGameDate, this));
		break;
	case 3:
		TextureCache::getInstance()->addImageAsync("lizi/fire.png", CC_CALLBACK_0(StartScene::loadingGameDate, this));
		break;
	case 4:
		TextureCache::getInstance()->addImageAsync("lizi/penshe.png", CC_CALLBACK_0(StartScene::loadingGameDate, this));
		break;
	case 5:
		TextureCache::getInstance()->addImageAsync("res/Players.png", CC_CALLBACK_0(StartScene::loadingGameDate, this));
		break;
	case 6:
		TextureCache::getInstance()->addImageAsync("pic/jiGBullet.png", CC_CALLBACK_0(StartScene::loadingGameDate, this));
		break;
	default:
		
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Players.plist");
		auto scene = HelloWorld::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	}
	number++;
}