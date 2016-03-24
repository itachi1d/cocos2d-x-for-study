#pragma once
#include "cocos2d.h"

using namespace cocos2d;
class GameSceneManager
{
public:
	GameSceneManager();
	~GameSceneManager();
public:
	Scene* mainScene;
	Scene* gameScene;
	Scene* birdScene;
	Scene* fruitScene;
	Scene* musicScene;
	static GameSceneManager *manager;
public:
	void createMainScene();
	void goToGameScene();
	void goToFruitScene();
	void goToBirdScene();
	void goToMusicScene();
	static GameSceneManager* getInstance();
};

