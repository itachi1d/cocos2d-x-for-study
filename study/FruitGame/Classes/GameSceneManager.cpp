#include "GameSceneManager.h"
#include "MainLayer.h"

GameSceneManager::GameSceneManager()
{
}


GameSceneManager::~GameSceneManager()
{
}

GameSceneManager * GameSceneManager::manager;

void GameSceneManager::createMainScene()
{
	mainScene = Scene::create();
	MainLayer *layer = MainLayer::create();
	mainScene->addChild(layer);
	layer->sceneManager = this;
	Director::getInstance()->replaceScene(mainScene);
}

void GameSceneManager::goToGameScene()
{

}

void GameSceneManager::goToFruitScene()
{

}

void GameSceneManager::goToBirdScene()
{

}

void GameSceneManager::goToMusicScene()
{

}

GameSceneManager* GameSceneManager::getInstance()
{
	if (!manager)
	{
		manager = new GameSceneManager();
	}
	return manager;
}
