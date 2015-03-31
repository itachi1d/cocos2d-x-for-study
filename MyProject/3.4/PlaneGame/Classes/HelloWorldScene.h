#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocostudio\CocoStudio.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void update(float dt);
    
	void startButtonCallBack(cocos2d::Ref* pSender,ui::TouchEventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	ProgressTimer *jindutiao;
	float sum;
};

#endif // __HELLOWORLD_SCENE_H__
