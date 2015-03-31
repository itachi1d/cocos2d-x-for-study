#include "GKselectScene.h"
#include "CanShu.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

USING_NS_CC;

Scene* GKselectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GKselectScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GKselectScene::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Texture2D *bgImage = TextureCache::getInstance()->getTextureForKey("Images/bg.png");
	itemImage = TextureCache::getInstance()->getTextureForKey("Images/items.png");


	Sprite *kuang = Sprite::createWithTexture(itemImage, Rect(2, 864, 750, 400));
	kuang->setPosition(480, 320);
	addChild(kuang, 22);
	initTitle();
	initGuanKa();
	initButton();
	backButtonListener();
	return true;
}

void GKselectScene::initTitle()
{
	std::stringstream ss;
	ss<<YeMian;
	std::string str;
	ss>>str;
	LabelTTF *title = LabelTTF::create(str, "Arial", 40);
	addChild(title, 30);
	title->setPosition(480, 495);
}
void GKselectScene::initGuanKa()
{
	Menu *menu = Menu::create();
	menu->setAnchorPoint(Point::ZERO);
	menu->setPosition(Point::ZERO);
	int num = 0;
	if(MaxGuanKa < YeMian*15)
	{
		int cout = 15 - (YeMian*15 - MaxGuanKa);//页面中关卡总数
		int row = (int)(cout/5)+1;//总排数
		//int minCount =cout -( 5 * (row-1));//最后一排剩余的关卡数
		
		for(int i = 0; i < row; ++i)
		{
			for(int j = 0; j < 5; j++)
			{
				num++;
				if(num > cout)
					break;
				MenuItemSprite *guanKaItem = MenuItemSprite::create(
					Sprite::createWithTexture(itemImage, Rect(875, 2, 79, 80)),
					Sprite::createWithTexture(itemImage, Rect(875, 2, 79, 80)),
					Sprite::createWithTexture(itemImage, Rect(792, 2, 81, 80)),
					CC_CALLBACK_0(GKselectScene::goToGame, this, num+(YeMian-1)*15));
				int dangQianGuanKa = (YeMian - 1) * 15 + num;//当前关卡
				if(dangQianGuanKa > (yiGuoGK + 1))
					guanKaItem->setEnabled(false);
				guanKaItem->setPosition(165 + 157*j, 380 - 80*i);
				menu->addChild(guanKaItem);

				std::stringstream ss;
				ss<<num;
				std::string str;
				ss>>str;
				LabelTTF *title = LabelTTF::create(str, "Arial", 25);
				addChild(title, 50);
				title->setPosition(guanKaItem->getPosition());
				title->setColor(Color3B(0, 0, 0));
			}
			if(i == cout)
				break;
		}
	}
	else
	{
		for(int i = 0; i < 3; ++i)
		{
			for(int j = 0; j < 5; j++)
			{
				num++;
				MenuItemSprite *guanKaItem = MenuItemSprite::create(
					Sprite::createWithTexture(itemImage, Rect(875, 2, 79, 80)),
					Sprite::createWithTexture(itemImage, Rect(875, 2, 79, 80)),
					Sprite::createWithTexture(itemImage, Rect(792, 2, 81, 80)),
					CC_CALLBACK_0(GKselectScene::goToGame, this, num+(YeMian-1)*15));
				int dangQianGuanKa = (YeMian - 1) * 15 + num;//当前关卡
				if(dangQianGuanKa > (yiGuoGK + 1))
					guanKaItem->setEnabled(false);
				guanKaItem->setPosition(165 + 157*j, 380 - 80*i);
				menu->addChild(guanKaItem);

				std::stringstream ss;
				ss<<num;
				std::string str;
				ss>>str;
				LabelTTF *title = LabelTTF::create(str, "Arial", 25);
				addChild(title, 50);
				title->setPosition(guanKaItem->getPosition());
				title->setColor(Color3B(0, 0, 0));
			}
		}
	}

	addChild(menu, 30);
}

void GKselectScene::goToGame(int chickGuanka)
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	guanKa = chickGuanka;
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GKselectScene::initButton()
{
	MenuItemSprite *back = MenuItemSprite::create(
		Sprite::createWithTexture(itemImage, Rect(34, 2, 91, 90)),
		Sprite::createWithTexture(itemImage, Rect(127, 2, 91, 90)),
		CC_CALLBACK_0(GKselectScene::returnYeMian, this));
	MenuItemSprite *goOnHome = MenuItemSprite::create(
		Sprite::createWithTexture(itemImage, Rect(754, 864, 96, 49)),
		Sprite::createWithTexture(itemImage, Rect(852, 864, 96, 49)),
		CC_CALLBACK_0(GKselectScene::comeBackMain, this));
	Sprite *next1 = Sprite::createWithTexture(itemImage, Rect(34, 2, 91, 90));
	next1->setFlipX(true);
	Sprite *next2 = Sprite::createWithTexture(itemImage, Rect(127, 2, 91, 90));
	next2->setFlipX(true);
	MenuItemSprite *next = MenuItemSprite::create(next1, next2,
		CC_CALLBACK_0(GKselectScene::NextYeMian, this));
	back->setPosition(50, 50);
	goOnHome->setPosition(480, 50);
	next->setPosition(910, 50);
	Menu *menu = Menu::create(back, goOnHome, next, NULL);
	if((YeMian*15+1) > MaxGuanKa)//是否有下一页
		menu->removeChild(next, true);
	if(YeMian-1 == 0)//是否有上一页
		menu->removeChild(back, true);
	menu->setAnchorPoint(Point::ZERO);
	menu->setPosition(Point::ZERO);
	addChild(menu);
}

void GKselectScene::comeBackMain()
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	auto scene = MainMenuScene::createScene();
	auto sceneAction = TransitionFadeTR::create(1, scene);
	Director::getInstance()->replaceScene(sceneAction);
}
void GKselectScene::NextYeMian()
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	YeMian++;
	auto scene = GKselectScene::createScene();
	auto sceneAction = TransitionFadeTR::create(1, scene);
	Director::getInstance()->replaceScene(sceneAction);
}

void GKselectScene::returnYeMian()
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	YeMian--;
	auto scene = GKselectScene::createScene();
	auto sceneAction = TransitionFadeBL::create(1, scene);
	Director::getInstance()->replaceScene(sceneAction);
}

void GKselectScene::backButtonListener()
{
	auto *listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [](EventKeyboard::KeyCode keycode, cocos2d::Event *event){
		if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)  //返回
		{
			auto scene = MainMenuScene::createScene();
			auto sceneAction = TransitionFadeBL::create(1, scene);
			Director::getInstance()->replaceScene(sceneAction);        
		}
	};
	 Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}