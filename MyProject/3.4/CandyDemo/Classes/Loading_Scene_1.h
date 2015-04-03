#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class Loading_Scene_1 : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	void loadResource();
	void returnToGameLayer();
	void plistImageAsyncCallback1(cocos2d::Texture2D* texture);
	CREATE_FUNC(Loading_Scene_1);
private:
	ProgressTimer *loadingbar;
	int i;
	float sum;
	int MaxFiles;
};

#endif // __HELLOWORLD_SCENE_H__