#include "GameScene.h"
#include "CanShu.h"
#include "MainMenuScene.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;
USING_NS_CC;



Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	layer->setTag(0);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::init() )
    {
        return false;
    }
	playerImage = TextureCache::getInstance()->addImage("Images/runImages.png");
	itemsImage = TextureCache::getInstance()->addImage("Images/items.png");	

	MaxPlayerVelocity = (float)HCRSPEED;
	initMap();//初始化地图
	initPhysics();//初始化世界
	runAction();
	jumpAction();
	initPlay();//初始化主角
	
	setTouchListener();
	gameState = ready;
	layerMoveLen = 0;
	isThough = false;
	layerVelocity = (float)LAYERSPEED;
	ciSpeed = (float)CISPEED;
	downTime = 0;
	buttonDowning = false;
	buttonUping = false;
	isSlow = false;
	
	backButtonListener();
	scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{
	if(gameState == end)
	{
		if(isThough)
			initToughMenus();
		else
			initEndMenus();
		unscheduleUpdate();
	}
	else if(gameState == stop)
	{
		initStopMenus();
		unscheduleUpdate();
	}
	else
	{
		int velocityIterations = 8;
		int positionIterations = 1;
		world->Step(dt, velocityIterations, positionIterations);
		//更新所有Body的位置
		for(b2Body *b = world->GetBodyList(); b; b = b->GetNext())
		{
			if(b->GetType() == b2_dynamicBody | b->GetFixtureList()->GetFilterData().groupIndex == -2)
			{
				if(b->GetUserData() != nullptr){
					Sprite * sprite = (Sprite *)b->GetUserData();
					sprite->setPosition(Point(b->GetPosition().x*PTM_RATIO, b->GetPosition().y*PTM_RATIO));
					sprite->setRotation(-1*CC_RADIANS_TO_DEGREES(b->GetAngle()));
				}
			}
		}
		updatePlayer(dt);
		if(gameState == running)
		{
			updateLayer(dt);
			isCanThoughDown();
		}
	}
}

void GameScene::initMap()
{
	std::stringstream ss;
	ss<<guanKa;
	std::string str;
	ss>>str;
	std::string mapName = "map"+str+".tmx";
	experimental::TMXTiledMap *map = experimental::TMXTiledMap::create(mapName);
	addChild(map, 10);
	map->setAnchorPoint(Point::ZERO);
	map->setPosition(Point::ZERO);
	map->setTag(0);
	playerVelocity = MaxPlayerVelocity;
}
void GameScene::initPlay()
{
	auto *map = (TMXTiledMap*)getChildByTag(0);
	auto *start = map->getObjectGroup("start");
	ValueMap startPoint = start->getObject("sp");
	Sprite *player = Sprite::createWithTexture(playerImage, Rect(114, 104, 110, 117));
	player->setPosition(startPoint["x"].asFloat(), startPoint["y"].asFloat());
	addChild(player, 20);
	player->setTag(2);
	b2BodyDef lkrBodyDef;
	lkrBodyDef.type = b2_dynamicBody;
	lkrBodyDef.position.Set(player->getPosition().x/PTM_RATIO, player->getPosition().y/PTM_RATIO);
	hcrBody = world->CreateBody(&lkrBodyDef);
	b2PolygonShape lkrBox; 
	lkrBox.SetAsBox((player->getContentSize().width - 30)/2/PTM_RATIO, 
		player->getContentSize().height/2/PTM_RATIO);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &lkrBox;
	fixtureDef.density = 5;
	fixtureDef.restitution = 0;
	fixtureDef.friction = 0;
	fixtureDef.filter.groupIndex = 1;

	hcrBody->CreateFixture(&fixtureDef);
	hcrBody->SetUserData(player);
	hcrBody->SetFixedRotation(true);

	gojumpAction();
	//map = 0;
}

void GameScene::initPhysics()
{
	b2Vec2 gravity(0.0f, -80.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	contactlistener = new MyContactListener();
	contactFilter = new MyContactFiler();
	world->SetContactListener(contactlistener);
	world->SetContactFilter(contactFilter);
	b2BodyDef groundBodyDef;  
	groundBodyDef.type = b2_staticBody;
    
	b2PolygonShape groundBox;                                               
    // 底部  

	
	auto *map = (TMXTiledMap*)getChildByTag(0);
	auto *lu1 = map->getObjectGroup("lu");

	
	if(lu1)
	{
		ValueVector vector = lu1->getObjects();
		for(ValueVector::iterator itr = vector.begin(); itr != vector.end(); ++itr)
		{
			ValueMap tile = itr->asValueMap();
			float x = tile["x"].asFloat();
			float y = tile["y"].asFloat(); 
			float width = tile["width"].asFloat();
			float height = tile["height"].asFloat();
			groundBodyDef.position.Set((x+width/2)/PTM_RATIO, (y+height/2)/PTM_RATIO); 
			b2Body* groundBody = world->CreateBody(&groundBodyDef);
			groundBox.SetAsBox(width/PTM_RATIO/2, height/PTM_RATIO/2);
			Sprite *sprite = Sprite::create();
			sprite->setContentSize(Size(width, height));
			addChild(sprite);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &groundBox;
			fixtureDef.restitution = 0;
			fixtureDef.friction = 0;
			fixtureDef.filter.groupIndex = -1;

			groundBody->CreateFixture(&fixtureDef);
			groundBody->SetUserData(sprite);
		}
	}
	auto *jumpLu = map->getObjectGroup("jumpLu");
	if(jumpLu)
	{
		ValueVector vector = jumpLu->getObjects();
		for(ValueVector::iterator itr = vector.begin(); itr != vector.end(); ++itr)
		{
			ValueMap tile = itr->asValueMap();
			float x = tile["x"].asFloat();
			float y = tile["y"].asFloat(); 
			float width = tile["width"].asFloat();
			float height = tile["height"].asFloat();
			groundBodyDef.position.Set((x+width/2)/PTM_RATIO, (y+height/2)/PTM_RATIO); 
			b2Body* groundBody = world->CreateBody(&groundBodyDef);
			groundBox.SetAsBox(width/PTM_RATIO/2, height/PTM_RATIO/2);
			Sprite *sprite = Sprite::create();
			sprite->setContentSize(Size(width, height));
			addChild(sprite);
			sprite->setTag(1);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &groundBox;
			fixtureDef.restitution = 0;
			fixtureDef.friction = 0;
			fixtureDef.filter.groupIndex = -1;
			groundBody->CreateFixture(&fixtureDef);
			groundBody->SetUserData(sprite);
		}
	}
	jumpLu = 0;
	auto *si = map->getObjectGroup("si");
	if(si)
	{
		ValueVector vector = si->getObjects();
		for(ValueVector::iterator itr = vector.begin(); itr != vector.end(); ++itr)
		{
			ValueMap tile = itr->asValueMap();
			float x = tile["x"].asFloat();
			float y = tile["y"].asFloat(); 
			float width = tile["width"].asFloat();
			float height = tile["height"].asFloat();
			groundBodyDef.position.Set((x+width/2)/PTM_RATIO, (y+height/2)/PTM_RATIO); 
			b2Body* groundBody = world->CreateBody(&groundBodyDef);
			groundBox.SetAsBox(width/PTM_RATIO/2, height/PTM_RATIO/2);
			Sprite *sprite = Sprite::create();
			sprite->setContentSize(Size(width, height));
			addChild(sprite);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &groundBox;
			fixtureDef.restitution = 0;
			fixtureDef.friction = 0;
			fixtureDef.filter.groupIndex = -2;

			groundBody->CreateFixture(&fixtureDef);
			groundBody->SetUserData(sprite);
		}
	}
	si = 0;
	map = 0;
	Sprite *ci = Sprite::createWithTexture(itemsImage, Rect(2, 2, 30, 640));
	ci->setPosition(0, 320);
	addChild(ci, 15);
	b2BodyDef ciBodyDef;  
	ciBodyDef.type = b2_dynamicBody;
	ciBodyDef.position.Set(ci->getPosition().x/PTM_RATIO, ci->getPosition().y/PTM_RATIO);
	ciBody = world->CreateBody(&ciBodyDef);

	b2PolygonShape lkrBox; 
	lkrBox.SetAsBox((ci->getContentSize().width - 15)/2/PTM_RATIO, 
		ci->getContentSize().height/2/PTM_RATIO);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &lkrBox;
	fixtureDef.density = 5;
	fixtureDef.restitution = 0;
	fixtureDef.friction = 0;
	fixtureDef.filter.groupIndex = -2;

	ciBody->CreateFixture(&fixtureDef);
	ciBody->SetFixedRotation(true);
	ciBody->SetUserData(ci);
	ciBody->SetGravityScale(0);//取消重力
   
}

void GameScene::initButton()
{
	Texture2D *buttons = TextureCache::getInstance()->getTextureForKey("Images/buttons.png");
	Sprite *buttonDown = Sprite::createWithTexture(buttons, Rect(2, 2, 160, 160));
	Sprite *buttonUp = Sprite::createWithTexture(buttons, Rect(326, 2, 160, 160));
	Sprite *slowButton = Sprite::createWithTexture(buttons, Rect(168, 164, 160, 160));
	buttonDown->setPosition(700, 110);
	buttonUp->setPosition(870, 110);
	slowButton->setPosition(90, 110);
	addChild(slowButton, 30);
	addChild(buttonDown, 30);
	addChild(buttonUp, 30);
	buttonDown->setTag(5);
	buttonUp->setTag(6);
	slowButton->setTag(7);

	EventListenerTouchAllAtOnce *listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event){
		for(int i = 0; i < touches.size(); ++i)
		{
			Point touPoint = this->convertToNodeSpace(touches.at(i)->getLocation());
			Size downSize = buttonDown->getContentSize();
			Size upSize = buttonUp->getContentSize();
			Size slowSize = slowButton->getContentSize();
			Rect rectDown(buttonDown->getPosition().x - downSize.width/2,
				buttonDown->getPosition().y - downSize.height/2 ,downSize.width ,downSize.height );
			Rect rectUp(buttonUp->getPosition().x - upSize.width/2,
				buttonUp->getPosition().y - upSize.height/2 ,upSize.width ,upSize.height );
			Rect rectSlow(slowButton->getPosition().x - slowSize.width/2,
				slowButton->getPosition().y - slowSize.height/2 ,slowSize.width ,slowSize.height );
			if(rectDown.containsPoint(touPoint))
			{
				touchDownPoint = touches.at(i)->getStartLocationInView();
				buttonDown->setTextureRect(Rect(164, 2, 160, 160));
				buttonDowning = true;
			}
			if(rectUp.containsPoint(touPoint))
			{
				touchUpPoint = touches.at(i)->getStartLocationInView();
				buttonUp->setTextureRect(Rect(2, 164, 160, 160));
				buttonUping = true;
			}
			if(rectSlow.containsPoint(touPoint))
			{
				touchSlowPoint = touches.at(i)->getStartLocationInView();//用一个全局变量记录住按下慢按钮的touch的point
				slowButton->setTextureRect(Rect(330, 164, 160, 160));
				playerVelocity *= (float)LOWERSPEED;
				isSlow = true;
			}
		}
	};
	listener->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event){
		for(int i = 0; i < touches.size(); ++i)
		{
			if(touches.at(i)->getStartLocationInView() == touchSlowPoint)//在这里遍历判断每个抬起的touch的point是否有一个等于上面的全局变量point
			{
				slowButton->setTextureRect(Rect(168, 164, 160, 160));
				playerVelocity = MaxPlayerVelocity;
				isSlow = false;
				break;
			}
			if(touches.at(i)->getStartLocationInView() == touchDownPoint)//在这里遍历判断每个抬起的touch的point是否有一个等于上面的全局变量point
			{
				buttonDown->setTextureRect(Rect(2, 2, 160, 160));
				buttonDowning = false;
				break;
			}
			if(touches.at(i)->getStartLocationInView() == touchUpPoint)//在这里遍历判断每个抬起的touch的point是否有一个等于上面的全局变量point
			{
				buttonUp->setTextureRect(Rect(326, 2, 160, 160));
				buttonUping = false;
				break;
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	stopButton = 
		MenuItemSprite::create(Sprite::createWithTexture(itemsImage, Rect(770, 644, 90, 89)),
		Sprite::createWithTexture(itemsImage, Rect(677, 644, 90, 89)),
		CC_CALLBACK_1(GameScene::stopGame, this));
	Menu *menu = Menu::create(stopButton, NULL);
	stopButton->setPosition(880 - layerMoveLen, 560);
	menu->setAnchorPoint(Point::ZERO);
	menu->setPosition(Point::ZERO);
	addChild(menu, 40);

	
}
void GameScene::playerDown()
{
	if(playState == run && !contactsWithPlayer.empty())
	{
		playState = down;
	}
}
bool GameScene::isCanDown()
{
	if(contactsWithPlayer.size() > 0)
		return true;
	else
		return false;
}

void GameScene::playerJump()
{
	if(isCanJump())
	{
		hcrBody->SetLinearVelocity(b2Vec2(hcrBody->GetLinearVelocity().x, (float)JUMPHIGHT));
		if(isSoundOpen)
			SimpleAudioEngine::getInstance()->playEffect("music/jump.OGG");		
	}
}
void GameScene::playerHighJump(float VeclocityY)
{
	if(VeclocityY < 0)
	{
		hcrBody->SetLinearVelocity(b2Vec2(hcrBody->GetLinearVelocity().x, -(float)JUMPHIGHSPEED*VeclocityY));
		if(isSoundOpen)
				SimpleAudioEngine::getInstance()->playEffect("music/jump.OGG");	
	}

}
bool GameScene::isCanJump()
{
	if(contactsWithPlayer.size() > 0 && isCanUp && playState!=PlayerState::jump)
		return true;
	else
		return false;
}

void GameScene::isCanThoughDown()
{
	if(playState == run)
	{
		bool flag = true;
		float _x = 0;
		auto *map = (TMXTiledMap*)getChildByTag(0);
		auto *start = map->getObjectGroup("down");
		ValueVector vector = start->getObjects();
		for(ValueVector::iterator itr = vector.begin(); itr != vector.end(); ++itr)
		{
			ValueMap tile = itr->asValueMap();
			float x1 = tile["x"].asFloat(); 
			float y1 = tile["y"].asFloat();
			float width = tile["width"].asFloat();
			float height = tile["height"].asFloat();
			float x2 = x1 + width;
			float y2 = y1 + height;
			if((hcrBody->GetPosition().x*PTM_RATIO) >= (x1-55) 
				&& (hcrBody->GetPosition().x*PTM_RATIO) < (x2+40)
				&&(hcrBody->GetPosition().y*PTM_RATIO) < y2 &&
				(hcrBody->GetPosition().y*PTM_RATIO) > y1)
			{
				_x = x1;
				flag = false;
				break;
			}
		}
		if(!flag)
			hcrBody->SetTransform(b2Vec2((_x-55)/PTM_RATIO, hcrBody->GetPosition().y)
			,hcrBody->GetAngle());
	}
}

void GameScene::runAction()
{
	SpriteFrame *frame0, *frame1, *frame2, *frame3;

	frame0 = SpriteFrame::createWithTexture(playerImage, Rect(250, 2, 110, 117));
	frame1 = SpriteFrame::createWithTexture(playerImage, Rect(362, 2, 110, 117));
	frame2 = SpriteFrame::createWithTexture(playerImage, Rect(2, 121, 110, 117));
	frame3 = SpriteFrame::createWithTexture(playerImage, Rect(362, 2, 110, 117));
	
	runs.pushBack(frame0);
	runs.pushBack(frame1);
	runs.pushBack(frame2);
	runs.pushBack(frame3);

}
void GameScene::jumpAction()
{
	SpriteFrame *frame0, *frame1, *frame2, *frame3;

	frame0 = SpriteFrame::createWithTexture(playerImage, Rect(188, 2, 60, 60));
	frame1 = SpriteFrame::createWithTexture(playerImage, Rect(126, 2, 60, 60));
	frame2 = SpriteFrame::createWithTexture(playerImage, Rect(64, 2, 60, 60));
	frame3 = SpriteFrame::createWithTexture(playerImage, Rect(2, 2, 60, 60));
	
	jumps.pushBack(frame0);
	jumps.pushBack(frame1);
	jumps.pushBack(frame2);
	jumps.pushBack(frame3);

	
}

void GameScene::goRunAction()
{
	Sprite *player = (Sprite*)getChildByTag(2);
	Animation *animation = Animation::createWithSpriteFrames(runs, 0.05f);
	animation->setLoops(-1);
	Animate *anima = Animate::create(animation);
	anima->setTag(1);
	player->runAction(anima);
}
void GameScene::gojumpAction()
{
	Sprite *player = (Sprite*)getChildByTag(2);
	Animation *animation = Animation::createWithSpriteFrames(jumps, 0.05f);
	animation->setLoops(-1);
	Animate *anima = Animate::create(animation);
	anima->setTag(0);
	player->runAction(anima);
}
void GameScene::goDownAction()
{
	Sprite *player = (Sprite*)getChildByTag(2);
	Animation *animation = Animation::createWithSpriteFrames(jumps, 0.05f);
	animation->setLoops(-1);
	Animate *anima = Animate::create(animation);
	anima->setTag(2);
	player->runAction(anima);
}

void GameScene::stopRunAction()
{
	Sprite *player = (Sprite*)getChildByTag(2);
	player->stopActionByTag(1);
}
void GameScene::stopjumpAction()
{
	Sprite *player = (Sprite*)getChildByTag(2);
	player->stopActionByTag(0);
}
void GameScene::stopDownAction()
{
	Sprite *player = (Sprite*)getChildByTag(2);
	player->stopActionByTag(2);
}

int GameScene::getGameState()
{
	return gameState;
}

void GameScene::updatePlayer(float dt)
{
	if(buttonUping)
		playerJump();
	else if(buttonDowning)
		playerDown();
	Sprite *player = (Sprite*)getChildByTag(2);
	bool isRunning = true;
	switch (playState)
	{
	case GameScene::run:		
		if(player->getActionByTag(1))
			isRunning = !player->getActionByTag(1)->isDone();
		else
			isRunning = false;
		if(getGameState() == GameScene::GameState::ready && !isRunning)
		{
			player->stopAllActions();
			player->setTextureRect(Rect(114, 121, 73, 149));
			Size s = player->getContentSize();
			((b2PolygonShape*)hcrBody->GetFixtureList()->GetShape())
				->SetAsBox(s.width/2/PTM_RATIO, s.height/2/PTM_RATIO);
		}
		else if(getGameState() == GameScene::GameState::running && !isRunning)
		{
			downTime = 0;
			player->stopAllActions();
			Size s1 = player->getContentSize();
			player->setTextureRect(Rect(2, 121, 110, 117));
			Size s2 = player->getContentSize();
			float lenth = (s1.height - s2.height)/2/PTM_RATIO;
			((b2PolygonShape*)hcrBody->GetFixtureList()->GetShape())
				->SetAsBox((s2.width - 30)/2/PTM_RATIO, s2.height/2/PTM_RATIO);
			hcrBody->SetTransform(b2Vec2(hcrBody->GetPosition().x, 
				hcrBody->GetPosition().y - lenth), hcrBody->GetAngle());
			goRunAction();
		}
		break;
	case GameScene::jump:
		if(hcrBody->GetLinearVelocity().y < (float)DOWNMAXSPEED)
			hcrBody->SetLinearVelocity(b2Vec2(hcrBody->GetLinearVelocity().x, (float)DOWNMAXSPEED));
		if(player->getActionByTag(0))
			isRunning = !player->getActionByTag(0)->isDone();
		else
			isRunning = false;
		if(!isRunning)
		{
			downTime = 0;
			player->stopAllActions();
			player->setTextureRect(Rect(2, 2, 60, 60));
			Size s = player->getContentSize();
			((b2PolygonShape*)hcrBody->GetFixtureList()->GetShape())
				->SetAsBox((s.width - 20)/2/PTM_RATIO, (s.height - 20)/2/PTM_RATIO);
			gojumpAction();
		}
		break;
	case GameScene::down:
		if(player->getActionByTag(2))
			isRunning = !player->getActionByTag(2)->isDone();
		else
			isRunning = false;
		if(!isRunning)
		{
			player->stopAllActions();
			Size s1 = player->getContentSize();
			player->setTextureRect(Rect(2, 2, 60, 60));
			Size s2 = player->getContentSize();
			float lenth = (s1.height - s2.height)/2/PTM_RATIO;
			((b2PolygonShape*)hcrBody->GetFixtureList()->GetShape())
				->SetAsBox(s2.width/2/PTM_RATIO, s2.height/2/PTM_RATIO);
			hcrBody->SetTransform(b2Vec2(hcrBody->GetPosition().x, 
				hcrBody->GetPosition().y - lenth), hcrBody->GetAngle());
			goDownAction();
		}
		hasUpBody(dt);	
		break;
	default:
		break;
	}
	if(gameState == running)
	{
		hcrBody->SetLinearVelocity(b2Vec2(playerVelocity, hcrBody->GetLinearVelocity().y));
		TMXTiledMap *map = (TMXTiledMap*)getChildByTag(0);
		if(hcrBody->GetPosition().x*32 >= map->getContentSize().width)
		{
			if(guanKa > yiGuoGK)
			{
				yiGuoGK = yiGuoGK+1;
				UserDefault::getInstance()->setIntegerForKey("yiGuoGK", yiGuoGK);
				UserDefault::getInstance()->flush();
			}
			isThough = true;
			gameState = end;
			
		}
		if(hcrBody->GetPosition().y*32 < -200)
		{
			isThough = false;
			gameState = end;
		}
	}

	
		
}

void GameScene::hasUpBody(float dt)
{
	bool flag = true;
	auto *map = (TMXTiledMap*)getChildByTag(0);
	auto *start = map->getObjectGroup("down");
	ValueVector vector = start->getObjects();
	for(ValueVector::iterator itr = vector.begin(); itr != vector.end(); ++itr)
	{
		ValueMap tile = itr->asValueMap();
		float x1 = tile["x"].asFloat(); 
		float width = tile["width"].asFloat();
		float x2 = x1 + width;
		if((hcrBody->GetPosition().x*PTM_RATIO) >= (x1-60) 
			&& (hcrBody->GetPosition().x*PTM_RATIO) <= (x2+40))
		{
			flag = false;
			break;
		}
	}
	start = 0;
	map = 0;
	isCanUp = flag;
	downTime+=dt;
	if(downTime >= (float)DOWNTIME)
	{			
		if(isCanUp && playState == down)
		{
			isCanUp = true;
			playState = run;
			downTime = 0;
		}
	}
}

void GameScene::updateLayer(float dt)
{
	float playerPoint = ((Sprite*)hcrBody->GetUserData())->getPosition().x;

	TMXTiledMap *map = (TMXTiledMap*)getChildByTag(0);
	if(map->getContentSize().width - 960 > -layerMoveLen)
	{
		if(playerPoint > (500 - layerMoveLen))
		{
			layerVelocity =  -playerVelocity;
		}
		else
			layerVelocity = (float)LAYERSPEED;
	}
	else
		layerVelocity = 0;
	layerMoveLen+=dt*layerVelocity*PTM_RATIO;
	this->setPositionX(this->getPositionX() + dt*layerVelocity*PTM_RATIO);

	if((ciBody->GetPosition().x*PTM_RATIO) < (-layerMoveLen+10) && ciSpeed < playerVelocity)
		ciBody->SetLinearVelocity(b2Vec2(playerVelocity, 0));
	else
		ciBody->SetLinearVelocity(b2Vec2(ciSpeed, 0));
	map = 0;

	

	Sprite *buttonDown = (Sprite*)getChildByTag(5);
	buttonDown->setPosition(700 - layerMoveLen, 80);
	Sprite *buttonUp = (Sprite*)getChildByTag(6);
	buttonUp->setPosition(870 - layerMoveLen, 80);
	Sprite *slowButton = (Sprite*)getChildByTag(7);
	slowButton->setPosition(90 - layerMoveLen, 80);
	stopButton->setPosition(880 - layerMoveLen, 560);
}

void GameScene::setTouchListener()
{
	Sprite *readyButton = Sprite::createWithTexture(itemsImage, Rect(2, 644, 253, 167));
	readyButton->setPosition(480, 320);
	addChild(readyButton, 15);
	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event){
		if(gameState == ready)
		{
			gameState = running;
			initButton();//初始化按钮
			_eventDispatcher->removeEventListener(listener);
			readyButton->removeFromParentAndCleanup(true);
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::comeBackMain(Ref* p)
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	auto scene = MainMenuScene::createScene();
	auto sceneAction = TransitionFadeTR::create(1, scene);

	//替换方式切换场景

	Director::getInstance()->replaceScene(sceneAction);
}
void GameScene::resetGame(Ref* p)
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	auto scene = GameScene::createScene();
	//auto sceneAction = TransitionFadeTR::create(1, scene);
	Director::getInstance()->replaceScene(scene);
}
void GameScene::nextGame(Ref* p)
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	guanKa++;
	auto scene = GameScene::createScene();
	//auto sceneAction = TransitionFadeTR::create(1, scene);
	Director::getInstance()->replaceScene(scene);
}
void GameScene::goOnGame(Ref* p)
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	gameState = running;
	stopMenu->removeFromParentAndCleanup(true);
	getChildByTag(22)->removeFromParentAndCleanup(true);
	scheduleUpdate();
}

void GameScene::stopGame(Ref* p)
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playEffect("music/click.OGG");
	gameState = stop;
}

void GameScene::initToughMenus()
{
	Sprite *MenuImage = Sprite::createWithTexture(itemsImage, Rect(956, 2, 523, 292));
	MenuImage->setPosition(480 - layerMoveLen, 320);
	addChild(MenuImage, 30);
	MenuImage->setTag(20);

	Sprite *mainMenu1 = Sprite::createWithTexture(itemsImage, Rect(754, 864, 96, 49));
	Sprite *mainMenu2 = Sprite::createWithTexture(itemsImage, Rect(852, 864, 96, 49));
	MenuItemSprite *mainMenu = MenuItemSprite::create(mainMenu1,
														mainMenu2,
														CC_CALLBACK_1(GameScene::comeBackMain, this));
	Sprite *resetGame1 = Sprite::createWithTexture(itemsImage, Rect(257, 644, 96, 49));
	Sprite *resetGame2 = Sprite::createWithTexture(itemsImage, Rect(355, 644, 96, 49));
	MenuItemSprite *resetGame = MenuItemSprite::create(resetGame1,
														resetGame2,
														CC_CALLBACK_1(GameScene::resetGame, this));
	Sprite *nextGame1 = Sprite::createWithTexture(itemsImage, Rect(1705, 2, 96, 49));
	Sprite *nextGame2 = Sprite::createWithTexture(itemsImage, Rect(1803, 2, 96, 49));
	MenuItemSprite *nextGame = MenuItemSprite::create(nextGame1,
														nextGame2,
														CC_CALLBACK_1(GameScene::nextGame, this));
	if(guanKa != MaxGuanKa)
	{
		thoughMenu = Menu::create(mainMenu, resetGame, nextGame, NULL);
		mainMenu->setPosition(320 - layerMoveLen, 210);
		resetGame->setPosition(480 - layerMoveLen, 210);
		nextGame->setPosition(640 - layerMoveLen, 210);
		
		
	}
	else
	{
		thoughMenu = Menu::create(mainMenu, resetGame, NULL);
		mainMenu->setPosition(320 - layerMoveLen, 210);
		resetGame->setPosition(640 - layerMoveLen, 210);
	}
	thoughMenu->setAnchorPoint(Point::ZERO);
	thoughMenu->setPosition(Point::ZERO);			
	thoughMenu->setTag(7);
	addChild(thoughMenu, 40);
}

void GameScene::initEndMenus()
{
	Sprite *MenuImage = Sprite::createWithTexture(itemsImage, Rect(220, 2, 346, 247));
	MenuImage->setPosition(480 - layerMoveLen, 320);
	addChild(MenuImage, 30);
	MenuImage->setTag(21);

	Sprite *mainMenu1 = Sprite::createWithTexture(itemsImage, Rect(754, 864, 96, 49));
	Sprite *mainMenu2 = Sprite::createWithTexture(itemsImage, Rect(852, 864, 96, 49));
	MenuItemSprite *mainMenu = MenuItemSprite::create(mainMenu1,
														mainMenu2,
														CC_CALLBACK_1(GameScene::comeBackMain, this));
	Sprite *resetGame1 = Sprite::createWithTexture(itemsImage, Rect(257, 644, 96, 49));
	Sprite *resetGame2 = Sprite::createWithTexture(itemsImage, Rect(355, 644, 96, 49));
	MenuItemSprite *resetGame = MenuItemSprite::create(resetGame1,
														resetGame2,
														CC_CALLBACK_1(GameScene::resetGame, this));

	endMenu = Menu::create(mainMenu, resetGame, NULL);
	mainMenu->setPosition(370 - layerMoveLen, 240);
	resetGame->setPosition(590 - layerMoveLen, 240);
	endMenu->setAnchorPoint(Point::ZERO);
	endMenu->setPosition(Point::ZERO);
	endMenu->setTag(8);
	addChild(endMenu, 40);
}
void GameScene::initStopMenus()
{
	Sprite *MenuImage = Sprite::createWithTexture(itemsImage, Rect(862, 644, 434, 218));
	MenuImage->setPosition(480 - layerMoveLen, 320);
	addChild(MenuImage, 30);
	MenuImage->setTag(22);

	Sprite *mainMenu1 = Sprite::createWithTexture(itemsImage, Rect(754, 864, 96, 49));
	Sprite *mainMenu2 = Sprite::createWithTexture(itemsImage, Rect(852, 864, 96, 49));
	MenuItemSprite *mainMenu = MenuItemSprite::create(mainMenu1,
															mainMenu2,
															CC_CALLBACK_1(GameScene::comeBackMain, this));
	Sprite *goOnMenu1 = Sprite::createWithTexture(itemsImage, Rect(680, 2, 110, 48));
	Sprite *goOnMenu2 = Sprite::createWithTexture(itemsImage, Rect(568, 2, 110, 48));
	MenuItemSprite *goOnMenu = MenuItemSprite::create(goOnMenu1,
														goOnMenu2,
														CC_CALLBACK_1(GameScene::goOnGame, this));
	stopMenu = Menu::create(mainMenu, goOnMenu, NULL);
	mainMenu->setPosition(330 - layerMoveLen, 250);
	goOnMenu->setPosition(630 - layerMoveLen, 250);
	stopMenu->setAnchorPoint(Point::ZERO);
	stopMenu->setPosition(Point::ZERO);
	stopMenu->setTag(9);
	addChild(stopMenu, 40);
}

void GameScene::backButtonListener()
{
	auto *listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, cocos2d::Event *event){
		if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)  //返回
		{
			if(gameState == GameState::running)
				gameState = GameState::stop;  
			else
			{
				auto scene = MainMenuScene::createScene();
				auto sceneAction = TransitionFadeBL::create(1, scene);
				Director::getInstance()->replaceScene(sceneAction); 
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}