#include "MainMenuScene.h"
#include "GKselectScene.h"
#include "CanShu.h"
#include "GameScene.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool MainMenuScene::init()
{
	if(!Layer::init())
	{
		return false;
	}
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/backgound.OGG", true);
	Texture2D *bgImage = TextureCache::getInstance()->getTextureForKey("Images/bg.png");
	Texture2D *itemsImage = TextureCache::getInstance()->getTextureForKey("Images/items.png");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *bgSprite = Sprite::createWithTexture(bgImage, Rect(2, 99, 960, 640));
	bgSprite->setPosition(visibleSize.width/2, visibleSize.height/2);
	addChild(bgSprite, 1);

	LabelTTF *banbenFont = LabelTTF::create("(1.0)", "Arial", 35);
	this->addChild(banbenFont, 2);
	banbenFont->setPosition(435, 190);

	MenuItemSprite *selectGK = MenuItemSprite::create(
		Sprite::createWithTexture(itemsImage, Rect(565, 644, 110, 48)),
		Sprite::createWithTexture(itemsImage, Rect(453, 644, 110, 48)),
		CC_CALLBACK_0(MainMenuScene::replaceSceleGKScene, this));
	MenuItemSprite *goOnGK = MenuItemSprite::create(
		Sprite::createWithTexture(itemsImage, Rect(680, 2, 110, 48)),
		Sprite::createWithTexture(itemsImage, Rect(568, 2, 110, 48)),
		CC_CALLBACK_0(MainMenuScene::goOnGame, this));
	MenuItemSprite *howToPlay = MenuItemSprite::create(
		Sprite::createWithTexture(itemsImage, Rect(1593, 2, 110, 48)),
		Sprite::createWithTexture(itemsImage, Rect(1481, 2, 110, 48)),
		CC_CALLBACK_0(MainMenuScene::replaceSceleGKScene, this));
	Sprite *button = Sprite::createWithTexture(bgImage, Rect(2, 2, 118, 95));
	MenuItemSprite *soundButton = MenuItemSprite::create(button, button,
		CC_CALLBACK_0(MainMenuScene::chickSoundButton, this, button));
	selectGK->setPosition(220, 100);
	goOnGK->setPosition(435, 100);
	howToPlay->setPosition(655, 100);
	soundButton->setPosition(900, 50);
	Menu *menu = Menu::create(selectGK, goOnGK, howToPlay,soundButton, NULL);
	menu->setAnchorPoint(Point::ZERO);
	menu->setPosition(Point::ZERO);
	addChild(menu, 2);
	backButtonListener();
	return true;
}

void MainMenuScene::replaceSceleGKScene()
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	YeMian = (int)(yiGuoGK / 15)+1;
	auto scene = GKselectScene::createScene();
	auto sceneAction = TransitionFadeTR::create(1, scene);
	Director::getInstance()->replaceScene(sceneAction);
}

void MainMenuScene::goOnGame()
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	if(yiGuoGK != MaxGuanKa)
		guanKa = yiGuoGK + 1;
	else
		guanKa = yiGuoGK;
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
void MainMenuScene::chickSoundButton(Node *node)
{
	isSoundOpen = !isSoundOpen;
	if(!isSoundOpen)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		((Sprite*)node)->setTextureRect(Rect(122, 2, 118, 95));
	}
	else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/backgound.OGG", true);
		((Sprite*)node)->setTextureRect(Rect(2, 2, 118, 95));
	}
}

void MainMenuScene::backButtonListener()
{
	auto *listener1 = EventListenerKeyboard::create();
	listener1->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event){
		if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)  //·µ»Ø
		{
			initEscMenu();
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);
}

void MainMenuScene::initEscMenu()
{
	Sprite *bg = Sprite::create("Images/Esc.png");     
	bg->setPosition(480, 320);
	addChild(bg, 50);
	Sprite *yes = Sprite::create("Images/yes.png");     
	yes->setPosition(640, 220);
	addChild(yes, 51);

	Sprite *no = Sprite::create("Images/no.png");     
	no->setPosition(300, 220);
	addChild(no, 51);
	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event *event){
		Point touPoint = this->convertToNodeSpace(touch->getLocation());
		Size s = no->getContentSize();
		Rect rect1(no->getPosition().x - s.width/2,
			no->getPosition().y - s.height/2 ,s.width ,s.height );
		if(rect1.containsPoint(touPoint))
		{
			no->removeFromParentAndCleanup(true);
			yes->removeFromParentAndCleanup(true);
			bg->removeFromParentAndCleanup(true);
			_eventDispatcher->removeEventListener(listener);
			return true;
		}

		s = yes->getContentSize();
		Rect rect2(yes->getPosition().x - s.width/2,
			yes->getPosition().y - s.height/2 ,s.width ,s.height );
		if(rect2.containsPoint(touPoint))
		{
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
				MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
				return;
			#endif
				Director::getInstance()->end();
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
			#endif
		}
		return true;
	};

	_eventDispatcher->addEventListenerWithFixedPriority(listener, -2);
		
}