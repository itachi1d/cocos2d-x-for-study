#include "GameSceneManager.h"
#include "PianoLayer.h"
#include "WelcomeLayer.h"
#include "LoadLayer.h"

using namespace cocos2d;

//ʵ��GameSceneManager���е�createScene����
void GameSceneManager::createLogoScene()
{
    //����һ����������
	logoScene = Scene::create();
    //����һ����ӭ��������
	WelcomeLayer* layer = WelcomeLayer::create();
	layer->sceneManager = this;
    //����ӭ������ӵ�������
    logoScene->addChild(layer);
}

void GameSceneManager::goToLoadScene()
{
	Director::getInstance()->setDepthTest(true);
	loadScene = Scene::create();
	LoadLayer* layer = LoadLayer::create();
	loadScene->addChild(layer);
	layer->sceneManager = this;
	//�л�����
	Director::getInstance()->replaceScene(loadScene);
}

void GameSceneManager::goToGameScene()
{
	Director::getInstance()->setDepthTest(true);
	gameScene = Scene::create();
	PianoLayer* layer = PianoLayer::create();
	gameScene->addChild(layer);
	layer->sceneManager = this;
	auto ss = TransitionFade::create(1.5, gameScene);
	//�л�����
	Director::getInstance()->replaceScene(ss);
}

