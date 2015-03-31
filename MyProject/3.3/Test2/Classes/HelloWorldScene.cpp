#include "HelloWorldScene.h"
#include "MyClassReader.h"
#include <cocostudio\CocoStudio.h>
USING_NS_CC;
//实现coco2.0新出的控件绑定方法的功能
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
	layer->setTag(0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    srand(unsigned(time(0)));
    Size visibleSize = Director::getInstance()->getVisibleSize();
	CSLoader* instance = CSLoader::getInstance();
	//注意第一个参数必须是第一步填写的自定义类名加“Reader ”如上述的"MyClassReader"
	instance->registReaderObject("MyClassReader",(ObjectFactory::Instance)MyClassReader::getInstance);
	auto _node = instance->createNode("MainScene.csb");
	addChild(_node , 1);
    return true;
}



