/*#include "LoadingMapScene.h"
#include "MapManager.h"
#include "GameScene.h"

Scene* LoadingMapScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingMapScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool LoadingMapScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	MapManager *manager = MapManager::Instance();
	manager->createMap();

	auto scene = GameScene::createScene();
	auto sceneAction = TransitionFadeTR::create(1, scene);
	//Ìæ»»·½Ê½ÇÐ»»³¡¾°
	Director::getInstance()->replaceScene(sceneAction);
	return true;
}*/