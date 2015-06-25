#include "SelectScene.h"
#include "cocostudio\CocoStudio.h"

#include "Manager.h"
#include "CanShu.h"
#include "LoadingScene.h"
#include "HelloWorldScene.h"
#include "BossSelectScene.h"
#include "NormalScene.h"

using namespace cocos2d::ui;
using namespace cocostudio;

cocos2d::Scene* SelectScene::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SelectScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool SelectScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	select_plane = 1;
	plane_type = 0;
	stateTime = (float)BULLET_ONCE_TIME;
	shutTime = (float)BULLET_ONCE_TIME;
	plane_show_layer = Layer::create();
	cliping = ClippingRectangleNode::create(Rect(200, 248, 420, 680));
	//cliping->setContentSize()
	
	Node *scene = static_cast<Widget*>(CSLoader::createNode ("SelectScene.csb"));
	addChild(scene);
	addChild(plane_show_layer);
	plane_show_layer:addChild(cliping);
	plane1 = scene->getChildByName<Sprite*>("plane1");
	plane2 = scene->getChildByName<Sprite*>("plane2");
	plane3 = scene->getChildByName<Sprite*>("plane3");
	plane1_share = scene->getChildByName<Sprite*>("plane1_share");
	plane2_share = scene->getChildByName<Sprite*>("plane2_share");
	plane3_share = scene->getChildByName<Sprite*>("plane3_share");
	plane1_button = scene->getChildByName<Sprite*>("plane1_button");
	plane2_button = scene->getChildByName<Sprite*>("plane2_button");
	plane3_button = scene->getChildByName<Sprite*>("plane3_button");

	Button* normal_button = scene->getChildByName<Button*>("Normal_Button");
	Button* boss_button = scene->getChildByName<Button*>("Boss_Button");
	Button* back_button = scene->getChildByName<Button*>("back_Button");
	normal_button->addTouchEventListener(this, toucheventselector(SelectScene::normal_button));
	boss_button->addTouchEventListener(this, toucheventselector(SelectScene::boss_button));
	back_button->addTouchEventListener(this, toucheventselector(SelectScene::back_button));

	Animation * animation = Animation::createWithSpriteFrames(Manager::Instance()->player1, 0.1f, -1);
	Animate *anima = Animate::create(animation);
	plane1->runAction(anima);

	plane1_button->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 1.1f), ScaleTo::create(0.5f, 1.0f), NULL)));
	show_plane(1);
	setTouchListener();
	this->scheduleUpdate();
	return true;
}

void SelectScene::setTouchListener()
{
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event){
		Point touchPoint = this->convertToNodeSpace(touch->getLocation());
		Rect plane1_rect = Rect(plane1_button->getPosition().x - plane1_button->getContentSize().width/2, plane1_button->getPosition().y - plane1_button->getContentSize().height/2,
			plane1_button->getContentSize().width, plane1_button->getContentSize().height);
		Rect plane2_rect = Rect(plane2_button->getPosition().x - plane2_button->getContentSize().width/2, plane2_button->getPosition().y - plane2_button->getContentSize().height/2,
			plane2_button->getContentSize().width, plane2_button->getContentSize().height);
		Rect plane3_rect = Rect(plane3_button->getPosition().x - plane3_button->getContentSize().width/2, plane3_button->getPosition().y - plane3_button->getContentSize().height/2,
			plane3_button->getContentSize().width, plane3_button->getContentSize().height);
		if (plane1_rect.containsPoint(touchPoint))//点击第一个飞机
		{
			if(select_plane == 1)
				return false;
			select_plane = 1;
			cliping->removeAllChildrenWithCleanup(true);
			show_plane(1);
			stopAllButton();
			plane1_share->setVisible(false);
			plane1_button->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane_button_down.png"));
			Animation * animation = Animation::createWithSpriteFrames(Manager::Instance()->player1, 0.1f, -1);
			Animate *anima = Animate::create(animation);
			plane1->runAction(anima);

			plane1_button->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 1.1f), ScaleTo::create(0.5f, 1.0f), NULL)));
		}
		if (plane2_rect.containsPoint(touchPoint))//点击第二个飞机
		{
			if(select_plane == 2)
				return false;
			select_plane = 2;
			cliping->removeAllChildrenWithCleanup(true);
			show_plane(2);
			stopAllButton();
			plane2_share->setVisible(false);
			plane2_button->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane_button_down.png"));
			Animation * animation = Animation::createWithSpriteFrames(Manager::Instance()->player2, 0.1f, -1);
			Animate *anima = Animate::create(animation);
			plane2->runAction(anima);

			plane2_button->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 1.1f), ScaleTo::create(0.5f, 1.0f), NULL)));
		}
		if (plane3_rect.containsPoint(touchPoint))//点击第三个飞机
		{
			if(select_plane == 3)
				return false;
			select_plane = 3;
			cliping->removeAllChildrenWithCleanup(true);
			show_plane(3);
			stopAllButton();
			plane3_share->setVisible(false);
			plane3_button->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane_button_down.png"));
			Animation * animation = Animation::createWithSpriteFrames(Manager::Instance()->player3, 0.1f, -1);
			Animate *anima = Animate::create(animation);
			plane3->runAction(anima);

			plane3_button->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 1.1f), ScaleTo::create(0.5f, 1.0f), NULL)));
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void SelectScene::stopAllButton()
{
	plane1->stopAllActions();
	plane2->stopAllActions();
	plane3->stopAllActions();
	plane1_button->stopAllActions();
	plane2_button->stopAllActions();
	plane3_button->stopAllActions();
	plane1_share->setVisible(true);
	plane2_share->setVisible(true);
	plane3_share->setVisible(true);

	plane1->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("A_player01_1.png"));
	plane2->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("A_player02_1.png"));
	plane3->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("A_player03_1.png"));

	plane1_button->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane_button_up.png"));
	plane2_button->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane_button_up.png"));
	plane3_button->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane_button_up.png"));

	plane1_button->setScale(1);
	plane2_button->setScale(1);
	plane3_button->setScale(1);
}

void SelectScene::show_plane(int type)
{
	Point point = Point(410, 370);
	Sprite* plane_temp;
	Animation * animation;
	Animate *anima;
	Sprite* bullet;
	ParticleBatchNode *penshebatch;
	ParticleSystem *JGParticle;
	switch (type)
	{
	case 1:
		plane_temp = Sprite::createWithSpriteFrameName("A_player01_1.png");
		cliping->addChild(plane_temp, 3);
		plane_temp->setPosition(point);
		animation = Animation::createWithSpriteFrames(Manager::Instance()->player1, 0.1f, -1);
		anima = Animate::create(animation);
		plane_temp->runAction(anima);
		plane_temp->setTag(1);
		break;
	case 2:
		plane_temp = Sprite::createWithSpriteFrameName("A_player02_1.png");
		cliping->addChild(plane_temp, 3);
		plane_temp->setPosition(point);
		animation = Animation::createWithSpriteFrames(Manager::Instance()->player2, 0.1f, -1);
		anima = Animate::create(animation);
		plane_temp->runAction(anima);
		plane_temp->setTag(1);
		break;
	case 3:
		plane_temp = Sprite::createWithSpriteFrameName("A_player03_1.png");
		cliping->addChild(plane_temp, 3);
		plane_temp->setPosition(point);
		animation = Animation::createWithSpriteFrames(Manager::Instance()->player3, 0.1f, -1);
		anima = Animate::create(animation);
		plane_temp->runAction(anima);
		plane_temp->setTag(1);

		bullet = Sprite::createWithSpriteFrameName("player_bullet_3.png");
		bullet->setScale(2);
		bullet->setAnchorPoint(Point(0.5, 0));
		bullet->setPosition(point);
		cliping->addChild(bullet, 1);

		penshebatch = ParticleBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey("lizi/penshe.png"));
		cliping->addChild(penshebatch, 2);
		JGParticle = ParticleSystemQuad::create("lizi/penshe.plist");  
		JGParticle->retain();  
		JGParticle->setTexture(TextureCache::getInstance()->getTextureForKey("lizi/penshe.png"));
		JGParticle->setStartSpinVar(60);
		JGParticle->setStartSize(120+3*20);
		JGParticle->setEndSize(150+3*20);
		JGParticle->setPosition(point);
		JGParticle->setTag(1);
		penshebatch->addChild(JGParticle);	
		JGParticle->release();
		break;
	default:
		break;
	}
}

void SelectScene::update(float dt)
{
	stateTime += dt;
	Point point = Point(410, 370);
	if (select_plane == 1)
	{
		if (stateTime >= shutTime)
		{
			stateTime = 0;
			if(shutTime == (float)BULLET_ONCE_TIME)
				shutTime = (float)BULLET_TWICE_TIME;
			else
				shutTime = (float)BULLET_ONCE_TIME;

			float maxAngle = 120;
			float temp = maxAngle/11;
			for (int i = 0; i < 12; ++i)
			{
				float angle =  90 - maxAngle/2 + i*temp;
				Sprite* bullet = Sprite::createWithSpriteFrameName("player_bullet_1.png");
				bullet->setPosition(point);
				float ration = CC_DEGREES_TO_RADIANS(angle);
				bullet->setRotation(360 - angle);
				bullet->runAction(Sequence::create(MoveBy::create(0.8f, Point(1000*cos(ration), 1000*sin(ration))), RemoveSelf::create(true), NULL));
				cliping->addChild(bullet, 1);
			}
		}
	}
	else if (select_plane == 2)
	{
		if (stateTime >= shutTime)
		{
			stateTime = 0;
			if(shutTime == (float)BULLET_ONCE_TIME)
				shutTime = (float)BULLET_TWICE_TIME;
			else
				shutTime = (float)BULLET_ONCE_TIME;
			int temp_y = point.y;
			for (int i = 0; i < 9; ++i)
			{
				Sprite* bullet = Sprite::createWithSpriteFrameName("player_bullet_2.png");
				int cout_y = 10;
				if(i >= 4)
					cout_y = - cout_y;
				bullet->setPosition(point.x - 60 + i * 120/8, temp_y);
				temp_y += cout_y;
				bullet->runAction(Sequence::create(MoveBy::create(0.8f, Point(0, 1000)), RemoveSelf::create(true), NULL));
				cliping->addChild(bullet, 1);
			}
		}
	}
}

void SelectScene::normal_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	Scene* scene;
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		plane_type = select_plane - 1;
		game_mode = NORMAL_MODE;
		scene = NormalScene::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	default:
		break;
	}
}

void SelectScene::boss_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	Scene* scene;
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		plane_type = select_plane - 1;
		game_mode = BOSS_MODE;
		scene = BossSelectScene::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	default:
		break;
	}
}

void SelectScene::back_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		{
			plane_type = select_plane - 1;
			game_mode = BOSS_MODE;
			Scene* scene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(scene);
		}		
		break;
	default:
		break;
	}
}

