#ifndef __LOAD_H__
#define __LOAD_H__
#include "cocos2d.h"
using namespace cocos2d;

class LoadScene : public Layer
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init();
	void update(float dt);
	void loadResource();
	void returnToGameLayer();
	void plistImageAsyncCallback1(cocos2d::Texture2D* texture);
	void plistImageAsyncCallback2(cocos2d::Texture2D* texture);
	CREATE_FUNC(LoadScene);
private:
	ProgressTimer *loadingbar;
	int i;
	int j;
	float sum;
	int MaxFiles;
};

#endif