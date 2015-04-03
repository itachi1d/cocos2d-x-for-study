#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include "cocos2d.h"

class Loading_Scene_2 : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void startLoading(float dt);
	void loadingGameDate();
	// implement the "static create()" method manually
	CREATE_FUNC(Loading_Scene_2);
private:
	int number;
};

#endif // __HELLOWORLD_SCENE_H__