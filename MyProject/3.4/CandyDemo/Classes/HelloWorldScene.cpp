#include "HelloWorldScene.h"

#include "Loading_Scene_2.h"
USING_NS_CC;

Scene* Game_Scene_1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game_Scene_1::create();

    // add layer as a child to scene
    scene->addChild(layer);
	layer->setTag(0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game_Scene_1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	contarl = Contarl::create();
	addChild(contarl);
	GameManager::Instance()->add_all_tiled(contarl);
	contarl->setTouchListener_game1();
    
	startItem = MenuItemImage::create(
		"pic/start_button.png",
		"pic/start_button.png",
		CC_CALLBACK_1(Game_Scene_1::menuCloseCallback, this));
	startItem->setPosition(580, 100);
	Menu * menu = Menu::create(startItem, NULL);
	this->addChild(menu);
	menu->setPosition(0, 0);
	menu->setAnchorPoint(Point(0, 0));
    return true;
}

void Game_Scene_1::menuCloseCallback(Ref* pSender)
{	
	GameManager::Instance()->init_obstacle();
	GameManager::Instance()->init_all_fruit(contarl);
	contarl->remove_touch_1();
	contarl->setTouchListener_game2();
	contarl->scheduleUpdate();
	startItem->setVisible(false);
}

