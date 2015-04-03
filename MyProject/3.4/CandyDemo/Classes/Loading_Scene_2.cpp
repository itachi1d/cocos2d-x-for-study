#include "Loading_Scene_2.h"
#include "Manager/Manager.h"
#include "GameLayer.h"

USING_NS_CC;

Scene* Loading_Scene_2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Loading_Scene_2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Loading_Scene_2::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	number = 0;

	this->scheduleOnce(schedule_selector(Loading_Scene_2::startLoading), 0.5f);
	return true;
}
void Loading_Scene_2::startLoading(float dt)
{
	loadingGameDate();
}
void Loading_Scene_2::loadingGameDate()
{

	Manager::Instance()->init_obstacle();
	auto scene = GameLayer::createScene();
	Director::getInstance()->replaceScene(scene);

}