#include "HelloWorldScene.h"
#include "MyClassReader.h"
#include <cocostudio\CocoStudio.h>
USING_NS_CC;
//ʵ��coco2.0�³��Ŀؼ��󶨷����Ĺ���
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
	//ע���һ�����������ǵ�һ����д���Զ��������ӡ�Reader ����������"MyClassReader"
	instance->registReaderObject("MyClassReader",(ObjectFactory::Instance)MyClassReader::getInstance);
	auto _node = instance->createNode("MainScene.csb");
	addChild(_node , 1);
    return true;
}



