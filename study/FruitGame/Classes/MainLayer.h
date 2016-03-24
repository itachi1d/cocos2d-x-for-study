#pragma once
#include "cocos2d.h"
#include "GameSceneManager.h"

using namespace cocos2d;

class MainLayer : public Layer
{
public:
	Sprite* bg;
	NodeGrid* effectNode;
	GameSceneManager* sceneManager;
	static bool musicFlag;
	static bool soundFlag;
	
public:
	virtual bool init();
	int random();
	CREATE_FUNC(MainLayer);
};