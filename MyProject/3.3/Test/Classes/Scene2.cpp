#include "Scene2.h"
#include "A.h"
#include "SceneSelect.h"

Scene2::Scene2(void)
{
}


Scene2::~Scene2(void)
{
}

void Scene2::pushThisScene()
{
	CCLayer* p_display=new Display();
	p_display->autorelease();
	
	
	addChild(p_display);
	CCDirector::sharedDirector()->replaceScene(this);

}

Display::Display()
	:p_lable_(NULL),t(0),isTouch(false),canMove(false)
{
	texture = TextureCache::getInstance()->addImage("blocks.png");
	p_lable_=CCLabelTTF::create("Scene 2","Arial",40.0f);
	p_lable_->setPosition(CCPointMake(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
	addChild(p_lable_);
	srand((int)time(NULL));
	setTouchListener();
	MenuItemSprite *menuItem = MenuItemSprite::create(Sprite::create("CloseNormal.png"),
		Sprite::create("CloseNormal.png"),
		CC_CALLBACK_0(Display::back, this));
	Menu *menu = Menu::create();
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 10);
	menu->addChild(menuItem);
	menuItem->setPosition(50, 500);
}
Display::~Display()
{
}

void Display::back()
{
	CCScene* pScene = CCScene::create();
	CCLayer* pLayer=SceneSelect::create();

	pScene->addChild(pLayer);
	Director::getInstance()->replaceScene(pScene);
}

void Display::createPic(Point point)
{
	
	int random = rand()%100;
	Sprite *pic;
	if(random < 25)
		pic = Sprite::createWithTexture(texture, Rect1);
	else if(random < 50)
		pic = Sprite::createWithTexture(texture, Rect2);
	else if(random < 50)
		pic = Sprite::createWithTexture(texture, Rect3);
	else
		pic = Sprite::createWithTexture(texture, Rect4);
	addChild(pic, 10);
	pic->setPosition(point);
	sprites.push_back(pic);
}

void Display::setTouchListener()
{
	EventListenerTouchAllAtOnce* touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event){
		for(int i = 0; i < touches.size(); ++i)
		{
			isTouch = true;
			bool flag = false;
			Point touPoint = this->convertToNodeSpace(touches.at(i)->getLocation());
			std::list<Sprite*>::iterator itr1;
			for(itr1 = sprites.begin(); itr1 != sprites.end(); ++itr1)
			{
				scheduleOnce(schedule_selector(Display::change), 1.0f);
				Sprite *sprite = (Sprite*)*itr1;
				Size size = sprite->getContentSize();
				Point point = sprite->getPosition();
				Rect rect = Rect(point.x - size.width/2, point.y - size.height/2, size.width, size.height);
				if(rect.containsPoint(touPoint))
				{
					int random = rand()%100;
					if(random < 25)
						sprite->setTextureRect(Rect1);
					else if(random < 50)
						sprite->setTextureRect(Rect2);
					else if(random < 50)
						sprite->setTextureRect(Rect3);
					else
						sprite->setTextureRect(Rect4);
					_sprite = sprite;
					flag = true;
					break;
				}
			}
			if(!flag)
				createPic(touPoint);
		}
	};

	touchListener->onTouchesMoved = [=](const std::vector<Touch*>& touches, Event* event){
		for(int i = 0; i < touches.size(); ++i)
		{
			if(isTouch && !canMove)
				isTouch = false;
			if(canMove)
			{
				Point touPoint = this->convertToNodeSpace(touches.at(i)->getLocation());
				_sprite->setPosition(touPoint);
			}
		}
	};
	touchListener->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event){
			isTouch = false;
			canMove = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Display::change(float dt)
{
	if(isTouch)
		canMove = true;
}