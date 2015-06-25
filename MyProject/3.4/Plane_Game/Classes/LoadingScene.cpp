#include "LoadingScene.h"
#include "GameResource.h"
#include "GameScene.h"
#include <SimpleAudioEngine.h>
#include "cocostudio\CocoStudio.h"
#include "Manager.h"

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace CocosDenshion;
Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool LoadingScene::init()
{
	// 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Node *scene = static_cast<Widget*>(CSLoader::createNode ("StartLoading.csb"));
	timeline::ActionTimeline* action = CSLoader::createTimeline("StartLoading.csb");
	addChild(scene);
	scene->runAction(action);
	action->gotoFrameAndPlay(0, -1);
	number = -1;
	this->scheduleOnce(schedule_selector(LoadingScene::startLoading), 2);
	return true;
}
void LoadingScene::startLoading(float dt)
{
	loadingGameDate();
}
void LoadingScene::loadingGameDate()
{
	number ++;
	switch (number)
	{
	case 0:
		TextureCache::getInstance()->addImageAsync("pic/bgs1.png",CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 1:
		TextureCache::getInstance()->addImageAsync("pic/feiji.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 2:
		TextureCache::getInstance()->addImageAsync("pic/shutAnima.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 3:
		TextureCache::getInstance()->addImageAsync("pic/MAX1_1.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 4:
		TextureCache::getInstance()->addImageAsync("pic/MAX1_2.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 5:
		TextureCache::getInstance()->addImageAsync("pic/MAX1_3.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 6:
		TextureCache::getInstance()->addImageAsync("pic/MAX1_4.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 7:
		TextureCache::getInstance()->addImageAsync("pic/max.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 8:
		TextureCache::getInstance()->addImageAsync("pic/boom.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 9:
		TextureCache::getInstance()->addImageAsync("pic/jiGBullet.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 10:
		TextureCache::getInstance()->addImageAsync("pic/bgs2.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 11:
		TextureCache::getInstance()->addImageAsync("pic/bgs3.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	case 12:
		TextureCache::getInstance()->addImageAsync("pic/bgs4.png", CC_CALLBACK_0(LoadingScene::loadingGameDate, this));
		break;
	default:
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bg_sound2.c_str());
		SimpleAudioEngine::getInstance()->preloadEffect(boom_sound.c_str());
		SimpleAudioEngine::getInstance()->preloadEffect(max_sound.c_str());
		SimpleAudioEngine::getInstance()->preloadEffect(maxing1_sound.c_str());
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/max.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/feiji.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/MAX1_1.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/MAX1_2.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/MAX1_3.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/MAX1_4.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/boom.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/jiGBullet.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/bgs1.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/bgs2.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/bgs3.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/bgs4.plist");

		Manager::Instance()->init_Anima();

		auto scene = GameScene::createScene();
		//auto sceneAction = TransitionFadeTR::create(1, scene);
		//Ìæ»»·½Ê½ÇÐ»»³¡¾°
		Director::getInstance()->replaceScene(scene);
		break;
	}
	
}