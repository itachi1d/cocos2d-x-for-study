#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::ui;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void show();

	void onBtnClickHander(Ref*pSender, Widget::TouchEventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	Button* startBtn;
};

#endif // __HELLOWORLD_SCENE_H__
