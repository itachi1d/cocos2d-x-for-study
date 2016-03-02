#ifndef __GameSceneManager_H__
#define __GameSceneManager_H__

#include "cocos2d.h"

using namespace cocos2d;

//���ڴ�����������
class GameSceneManager
{
public:
	Scene* logoScene;
	Scene* loadScene;
	Scene* gameScene;
public:
	//������������ķ���
	void createLogoScene();
	//�л���������
	void goToGameScene();
	void goToLoadScene();
};

#endif
