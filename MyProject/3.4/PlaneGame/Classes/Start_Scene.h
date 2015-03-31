#ifndef _START_SCENE_
#define _START_SCENE_

#include "cocos2d.h"

using namespace cocos2d;
class StartScene : public Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();  

	void loadingGameDate();
	void startLoading(float dt);
	CREATE_FUNC(StartScene);

private:
	int number;
};

#endif // !_START_SCENE_
