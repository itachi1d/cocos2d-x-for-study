#include "GameSceneManager.h"
#include "MainLayer.h"
#include "RankLayer.h"

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

void GameSceneManager::goToMainScene()
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

void GameSceneManager::goToRankScene()
{
	mainScene = Scene::create();
	RankLayer *layer = RankLayer::create();
	mainScene->addChild(layer);
	layer->sceneManager = this;
	Director::getInstance()->replaceScene(mainScene);
}

GameSceneManager* GameSceneManager::getInstance()
{
	if (!manager)
	{
		manager = new GameSceneManager();
	}
	return manager;
}
