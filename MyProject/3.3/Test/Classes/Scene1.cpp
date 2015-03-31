#include "Scene1.h"
#include "SceneSelect.h"
Scene1::Scene1(void)
{
}


Scene1::~Scene1(void)
{
}
void Scene1::pushThisScene()
{
	CCLayer* p_display=new TimeLayer();
	p_display->autorelease();

	CCLayer* p_display2=new OhterLayer();
	p_display2->autorelease();
	
	addChild(p_display);
	addChild(p_display2);
	CCDirector::sharedDirector()->replaceScene(this);
}

TimeLayer::TimeLayer():Seconds(0), Minute(0), Hour(0)
{
	this->setContentSize(Size(240, 320));
	this->setPosition(0, 0);
	this->setColor(Color3B::RED);
	this->setAnchorPoint(Point::ZERO);
	timeLabel = LabelTTF::create("0:0:0", "Arial", 20);
	timeLabel->setPosition(100, 300);
	addChild(timeLabel, 10);
	MenuItemSprite *menuItem = MenuItemSprite::create(Sprite::create("CloseNormal.png"),
		Sprite::create("CloseNormal.png"),
		CC_CALLBACK_0(TimeLayer::back, this));
	MenuItemSprite *open = MenuItemSprite::create(Sprite::create("CloseNormal.png"),
		Sprite::create("CloseNormal.png"),
		CC_CALLBACK_0(TimeLayer::startTime, this));
	MenuItemSprite *close = MenuItemSprite::create(Sprite::create("CloseNormal.png"),
		Sprite::create("CloseNormal.png"),
		CC_CALLBACK_0(TimeLayer::stopTime, this));
	Menu *menu = Menu::create();
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 10);
	menu->addChild(menuItem);
	menu->addChild(open);
	menu->addChild(close);
	menuItem->setPosition(50, 500);
	open->setPosition(50, 100);
	close->setPosition(100, 100);
}
TimeLayer::~TimeLayer()
{
	
}

void TimeLayer::stopTime()
{
	unschedule(schedule_selector(TimeLayer::showTime));
}

void TimeLayer::startTime()
{
	schedule(schedule_selector(TimeLayer::showTime), 1.0f);
}

void TimeLayer::showTime(float dt)
{
	Seconds += 1;
	if(Seconds > 59)
	{
		Seconds = 0;
		Minute ++;
		if(Minute > 59)
		{
			Minute = 0;
			Hour ++;
		}
	}
	std::stringstream ss1;
	ss1<<Seconds;
	std::string str3;
	ss1>>str3;
	std::stringstream ss2;
	ss2<<Minute;
	std::string str2;
	ss2>>str2;
	std::stringstream ss3;
	ss3<<Hour;
	std::string str1;
	ss3>>str1;
	std::string str = str1+":"+str2+":"+str3;
	timeLabel->setString(str);
}

void TimeLayer::back()
{
	CCScene* pScene = CCScene::create();
	CCLayer* pLayer=SceneSelect::create();

	pScene->addChild(pLayer);
	Director::getInstance()->replaceScene(pScene);
}

OhterLayer::OhterLayer()
{
	this->setContentSize(Size(240, 320));
	this->setPosition(240, 0);
	this->setColor(Color3B::BLUE);
	this->setAnchorPoint(Point::ZERO);
	sprite = Sprite::create("CloseNormal.png");
	addChild(sprite);
	sprite->setPosition(500, 200);
	setTouchListener();
}
OhterLayer::~OhterLayer()
{
	
}

void OhterLayer::setTouchListener()
{
	EventListenerTouchAllAtOnce* touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event){
		for(int i = 0; i < touches.size(); ++i)
		{
			sprite->stopAllActions();
			Point touPoint = this->convertToNodeSpace(touches.at(i)->getLocation());
			MoveTo *action = MoveTo::create(1, touPoint);
			sprite->runAction(action);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}