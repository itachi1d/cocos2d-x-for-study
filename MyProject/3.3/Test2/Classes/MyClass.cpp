#include "MyClass.h"
#include "ui/UIText.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;
MyClass::MyClass()
{}
Widget::ccWidgetTouchCallback MyClass::onLocateTouchCallback(const string &callBackName)
{
    if (callBackName == "onTouch")//判断事件名，返回对应的函数。下同
    {
           return CC_CALLBACK_2(MyClass::onTouch, this);
    }
    return nullptr;
}
Widget::ccWidgetClickCallback MyClass::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "onClick")
    {
        return CC_CALLBACK_1(MyClass::onClick, this);
    }
    return nullptr;
}
Widget::ccWidgetEventCallback MyClass::onLocateEventCallback(const string &callBackName)
{
    if (callBackName == "onEvent")
    {
        return CC_CALLBACK_2(MyClass::onEvent, this);
    }
    return nullptr;
}
void MyClass::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
	
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Layer *layer;
		Sprite *sprite;
		layer = (Layer*)Director::getInstance()->getRunningScene()->getChildByTag(0);
		sprite = Sprite::create("blocks.png");
		layer->addChild(sprite);
		sprite->setPosition(rand()%900, rand()%500);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void MyClass::onClick(cocos2d::Ref* sender)
{
    CCLOG("onClick");
}
void MyClass::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
}