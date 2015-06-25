#include"StartScene.h"
#include "cocostudio\CocoStudio.h"
#include "ResourceManager.h"
#include "Tool.h"
#include "MainMenuLayer.h"
using namespace cocostudio; 
using namespace cocos2d::ui;

StartScene::StartScene()
{
}
StartScene::~StartScene()
{
}

std::string StartScene::get_csb_filename()
{
	return "StartScene.csb";
}

void StartScene::set_callback(Node *root)
{
	timeline::ActionTimeline* action = CSLoader::createTimeline(get_csb_filename());
	root->runAction(action);
	action->gotoFrameAndPlay(0, -1);
	std::string name;
	for(int i = 10; i <= 110; i = i+10)
	{
		name = "pic/animations/dw"+Tool::toString(i)+".png";
		ResourceManager::Instance()->texture->addImageAsync(name, CC_CALLBACK_1(StartScene::plistImageAsyncCallback, this, i));
	}
}


void StartScene::plistImageAsyncCallback(cocos2d::Texture2D* texture, int i)
{
	std::string name = "pic/animations/dw"+Tool::toString(i)+".plist";;
	ResourceManager::Instance()->frameCache->addSpriteFramesWithFile(name);
	if(i == 110)
	{
		this->scheduleOnce(schedule_selector(StartScene::changeScene), 1);
	}
}

void StartScene::changeScene(float time)
{
	auto scene = Scene::create(); 
	scene->addChild(MainMenuLayer::create());
	Director::getInstance()->replaceScene(scene);
}