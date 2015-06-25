#ifndef _LOADING_
#define _LOADING_
#include "cocos2d.h"

using namespace cocos2d;
class LoadingScene : public Layer
{
public:
	static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void loadingGameDate();
	void startLoading(float dt);
	CREATE_FUNC(LoadingScene);
private:
	int number;
};

#endif