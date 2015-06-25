#include "GameScene.h"
#include "CanShu.h"
#include "DiJiSprite.h"
#include "MyParticle.h"
#include "cocostudio/CocoStudio.h"
#include <SimpleAudioEngine.h>
#include "ui/CocosGUI.h"
#include "Manager.h"
#include "SelectScene.h"
#include "Tool.h"
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace cocostudio;
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

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	srand((unsigned)time(NULL));
	
	Texture2D *bgs = TextureCache::getInstance()->getTextureForKey("pic/bgs.png");
	Texture2D *playerBullets = TextureCache::getInstance()->getTextureForKey("pic/player_show_bullet.png");
	feiji = TextureCache::getInstance()->getTextureForKey("pic/feiji.png");
	bulletsTexture = TextureCache::getInstance()->getTextureForKey("pic/jiGBullet.png");
	shutAnimaTexture = TextureCache::getInstance()->getTextureForKey("pic/shutAnima.png");
	boom = TextureCache::getInstance()->getTextureForKey("lizi/fire.png");
	shot = TextureCache::getInstance()->getTextureForKey("lizi/stars.png");
	penshe = TextureCache::getInstance()->getTextureForKey("lizi/penshe.png");
	binGonplistData = FileUtils::getInstance()->getValueMapFromFile("lizi/binGon.plist");
	boomPlistData = FileUtils::getInstance()->getValueMapFromFile("lizi/boom.plist");
	jgBingoPlistData = FileUtils::getInstance()->getValueMapFromFile("lizi/JGbingo.plist");
	dijiUpdate = new DijiUpdate();
	bossUpdate = Boss_Update::create();
	addChild(bossUpdate);
	bulletBatch = SpriteBatchNode::createWithTexture(playerBullets);
	diJiBulletBatch = SpriteBatchNode::createWithTexture(bulletsTexture);
	addChild(bulletBatch, 50);
	addChild(diJiBulletBatch, 61);
	guanka = guanqia;
	bulletType = plane_type;
	bulletLevel = 0;
	isFuHuoing = false;
	isShootJGbullet = true;
	isCanCortarl = false;
	isBaozou = false;
	isBoss = false;
	isGameOver = false;
	baozou_time = 0;
	bg_vec = 4;
	UserDefault::getInstance()->setIntegerForKey("max_cout", 5);
	UserDefault::getInstance()->setIntegerForKey("life", 5);
	max_cout = UserDefault::getInstance()->getIntegerForKey("max_cout", 3);
	playerLife = UserDefault::getInstance()->getIntegerForKey("life", 3);

	initPropScene();

	initbgs();
	
	bgsVeclecty = (float)BGS_VELOCITY;
	playerVeclecty = (float)PLAYER_MAX_VELOCITY;
	shutOnceTime = 0;
	shutTime = (float)BULLET_ONCE_TIME;

	initPlayerAnima();
	initParticleBatch();
	initPhysics();
	initPlayer();
	setTouchListener();
	
	this->scheduleOnce(schedule_selector(GameScene::setCanCorcarlt), 2);
	scheduleUpdate();
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_sound2.c_str(), true);
    return true;
}
GameScene::~GameScene()
{
	delete world; delete filter; delete listener; delete dijiUpdate;
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void GameScene::update(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 1;
	world->Step(dt, velocityIterations, positionIterations);
	//更新所有Body的位置
	for(b2Body *b = world->GetBodyList(); b; b = b->GetNext())
	{
		if(b->GetType() == b2_dynamicBody)
		{
			if(b->GetUserData() != nullptr){
				Sprite * sprite = (Sprite *)b->GetUserData();
				sprite->setPosition(Point(b->GetPosition().x*PTM_RATIO, b->GetPosition().y*PTM_RATIO));
				sprite->setRotation(-1*CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}
		}
	}
	
	bgsRun(dt);	
	PlayerMove();
	updateJGbullet();
	if(isCanCortarl)
		shotBullets(dt);		
	addremoveBullets();
	addremoveDiJi();
	destoryDiJis();
	destoryBullets();
	updateMoneyMove(dt);
	if(isCanCortarl)
	{
		if(game_mode ==  NORMAL_MODE)
			if(!isBoss)
				dijiUpdate->diJiUpdate(dt, this);
			else
				bossUpdate->boss_update(dt, this);
		else
			bossUpdate->boss_update(dt, this);
	}
	
	if(player->isDead && !isGameOver)
		fuHuo();
}

void GameScene::initPhysics()
{
	
	Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	b2Vec2 gravity(0.0f, 0.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
    world->SetContinuousPhysics(true);//创建边界
	filter = new MyContactFilter();
	world->SetContactFilter(filter);
	listener = new MyContactListener();
	world->SetContactListener(listener);
	b2BodyDef groundBodyDef;                                             
    //左下角  
	groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0, 0);                                       
    //创建地面物体  
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    //定义一个有边的形状  
    b2EdgeShape groundBox;                                               
    // 底部  
    groundBox.Set(b2Vec2(0,0), b2Vec2(640/PTM_RATIO,0));                       
    //使用夹具固定形状到物体上  
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0;
	fixtureDef.filter.groupIndex = -1;
	fixtureDef.restitution = 0;

    groundBody->CreateFixture(&fixtureDef);                                    
    // 顶部  
    groundBox.Set(b2Vec2(0,960/PTM_RATIO), b2Vec2(640/PTM_RATIO,960/PTM_RATIO));                    
	fixtureDef.shape = &groundBox;
	groundBody->CreateFixture(&fixtureDef);                                    
    // 左边  
    groundBox.Set(b2Vec2(0,960/PTM_RATIO), b2Vec2(0,0));  
	fixtureDef.shape = &groundBox;
    groundBody->CreateFixture(&fixtureDef);                                    
    // 右边  
	groundBox.Set(b2Vec2(640/PTM_RATIO,960/PTM_RATIO), b2Vec2(640/PTM_RATIO,0));                                 
    fixtureDef.shape = &groundBox;
	groundBody->CreateFixture(&fixtureDef);
}

void GameScene::initPlayer()
{
	player = PlayerSprite::create(bulletType);
	playerRect = player->getTextureRect();
	player->setPosition(100, 100);
	addChild(player, 60);
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position.Set(100/PTM_RATIO, 100/PTM_RATIO);
	playerBody = world->CreateBody(&playerBodyDef);
	playerBody->SetUserData(player);
	player->setBody(playerBody);
	playerBody->SetTransform(b2Vec2(320/PTM_RATIO, 200/PTM_RATIO), playerBody->GetAngle());
	tagetTouchPoint = Point(320, 200);
	//Size size = player->getContentSize();
	/*b2Vec2 verts[] = { // 下面的这一组坐标可以从VertexHelper 这个工具获取
		b2Vec2(0, (size.height/3 - 30) / PTM_RATIO),
		b2Vec2(-(size.width/2-25) / PTM_RATIO, (-size.height/3+25) / PTM_RATIO),
		b2Vec2((size.width/2-25) / PTM_RATIO, (-size.height/3+25) / PTM_RATIO)
	};
	b2PolygonShape polygonShape;
	polygonShape.Set(verts, 3);*/

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(25/PTM_RATIO, 10/PTM_RATIO);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0;
	fixtureDef.restitution = 0;
	fixtureDef.friction = 0;
	fixtureDef.filter.groupIndex = 1;

	playerBody->CreateFixture(&fixtureDef);
	playerBody->SetFixedRotation(true);
	//playerBody->SetMassData(0);
	playPlayerAnima();
}

void GameScene::initPlayerAnima()
{
	SpriteFrame *frame0, *frame1;
	if(bulletType == 0)
	{
		frame0 = Manager::Instance()->frames->getSpriteFrameByName("A_player01_1.png");
		frame1 = Manager::Instance()->frames->getSpriteFrameByName("A_player01_2.png");
	}
	else if(bulletType == 1)
	{
		frame0 = Manager::Instance()->frames->getSpriteFrameByName("A_player02_1.png");
		frame1 = Manager::Instance()->frames->getSpriteFrameByName("A_player02_2.png");
	}
	else
	{
		frame0 = Manager::Instance()->frames->getSpriteFrameByName("A_player03_1.png");
		frame1 = Manager::Instance()->frames->getSpriteFrameByName("A_player03_2.png");
	}
	playerAnmia.pushBack(frame0);
	playerAnmia.pushBack(frame1);
	
}
void GameScene::playPlayerAnima()
{
	Animation *animation = Animation::createWithSpriteFrames(playerAnmia, 0.08f);
	animation->setLoops(-1);
	Animate *anima = Animate::create(animation);
	player->runAction(anima);
}
void GameScene::bgsRun(float dt)
{
	bg1->setPosition(320, bg1->getPosition().y - bgsVeclecty*dt);
	bg2->setPosition(320, bg2->getPosition().y - bgsVeclecty*dt);
	bg3->setPosition(320, bg3->getPosition().y - bgsVeclecty*dt);

	if(bg1->getPosition().y <= -480)
		bg1->setPosition(320, bg3->getPosition().y + 960 - bg_vec);
	if(bg2->getPosition().y <= -480)
		bg2->setPosition(320, bg1->getPosition().y + 960 - bg_vec);
	if(bg3->getPosition().y <= -480)
		bg3->setPosition(320, bg2->getPosition().y + 960 - bg_vec);
}

void GameScene::setTouchListener()
{
	touchListener = EventListenerTouchAllAtOnce::create();
	Size playerSize = player->getContentSize();
	touchListener->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event){
		for(int i = 0; i < touches.size(); ++i)
		{
			Point touPoint = this->convertToNodeSpace(touches.at(i)->getLocation());
			Rect PlayerRect(player->getPosition().x - playerSize.width/2,
				player->getPosition().y - playerSize.height/2 ,playerSize.width ,playerSize.height );
			//if(PlayerRect.containsPoint(touPoint))
			{
				tagetTouchPoint = touPoint;
				touchMovePoint = touches.at(i)->getStartLocationInView();
			}
		}
	};
	touchListener->onTouchesMoved = [=](const std::vector<Touch*>& touches, Event* event){
		for(int i = 0; i < touches.size(); ++i)
		{
			if(touches.at(i)->getStartLocationInView() == touchMovePoint)
			{
				Point touPoint = this->convertToNodeSpace(touches.at(i)->getLocation());
				tagetTouchPoint = touPoint;
			}
		}
	};
	touchListener->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event){
		for(int i = 0; i < touches.size(); ++i)
		{
			if(touches.at(i)->getStartLocationInView() == touchMovePoint)
			{
				tagetTouchPoint = player->getPosition();
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

Point GameScene::contentVeclecty(Point vecTob2Vec)
{

	if(vecTob2Vec.x > (float)PLAYER_MAX_VELOCITY | vecTob2Vec.x < -(float)PLAYER_MAX_VELOCITY)
	{
		float cout = abs(vecTob2Vec.x)/(float)PLAYER_MAX_VELOCITY;
		vecTob2Vec.y/=cout;
		if(vecTob2Vec.x > (float)PLAYER_MAX_VELOCITY)
			vecTob2Vec.x = (float)PLAYER_MAX_VELOCITY;
		if(vecTob2Vec.x < -(float)PLAYER_MAX_VELOCITY)
			vecTob2Vec.x = -(float)PLAYER_MAX_VELOCITY;
	}
	else if(vecTob2Vec.x < (float)PLAYER_MIN_VELOCITY && vecTob2Vec.x > -(float)PLAYER_MIN_VELOCITY)
	{
		if(vecTob2Vec.x != 0 && vecTob2Vec.y != 0)
		{
			float cout = (float)PLAYER_MIN_VELOCITY/abs(vecTob2Vec.x);
			if(vecTob2Vec.y*cout < (float)PLAYER_MIN_VELOCITY && vecTob2Vec.y*cout > -(float)PLAYER_MIN_VELOCITY)
			{
				float cout = (float)PLAYER_MIN_VELOCITY/abs(vecTob2Vec.x);
				vecTob2Vec.y*=cout;
				if(vecTob2Vec.x > 0)
					vecTob2Vec.x = (float)PLAYER_MIN_VELOCITY;
				else
					vecTob2Vec.x = -(float)PLAYER_MIN_VELOCITY;
			}
		}
	}
	if(vecTob2Vec.y > (float)PLAYER_MAX_VELOCITY | vecTob2Vec.y < -(float)PLAYER_MAX_VELOCITY)
	{
		float cout = abs(vecTob2Vec.y)/(float)PLAYER_MAX_VELOCITY;
		vecTob2Vec.x/=cout;
		if(vecTob2Vec.y > (float)PLAYER_MAX_VELOCITY)
			vecTob2Vec.y = (float)PLAYER_MAX_VELOCITY;
		if(vecTob2Vec.y < -(float)PLAYER_MAX_VELOCITY)
			vecTob2Vec.y = -(float)PLAYER_MAX_VELOCITY;
	}
	else if(vecTob2Vec.y < (float)PLAYER_MIN_VELOCITY && vecTob2Vec.y > -(float)PLAYER_MIN_VELOCITY)
	{
		if(vecTob2Vec.y != 0 && vecTob2Vec.x != 0)
		{
			float cout = (float)PLAYER_MIN_VELOCITY/abs(vecTob2Vec.y);
			if(vecTob2Vec.x*cout < (float)PLAYER_MIN_VELOCITY && vecTob2Vec.x*cout > -(float)PLAYER_MIN_VELOCITY)
			{
				float cout = (float)PLAYER_MIN_VELOCITY/abs(vecTob2Vec.y);
				vecTob2Vec.x*=cout;
				if(vecTob2Vec.y > 0)
					vecTob2Vec.y = (float)PLAYER_MIN_VELOCITY;
				else
					vecTob2Vec.y = -(float)PLAYER_MIN_VELOCITY;
			}
		}
	}
	return vecTob2Vec;
}

void GameScene::PlayerMove()
{
	if(isFuHuoing)
		return;
	float speedx;
	if((tagetTouchPoint.x+10) > player->getPosition().x && //当飞机坐标落在一定范围内飞机速度为0（防止飞机抖动）
		(tagetTouchPoint.x-10) < player->getPosition().x &&
		(tagetTouchPoint.y+10) > player->getPosition().y &&
		(tagetTouchPoint.y-10) < player->getPosition().y)
	{
		playerBody->SetLinearVelocity(b2Vec2(0, 0));
		speedx = 0;
	}
	else
	{
		Point vec = tagetTouchPoint - player->getPosition();
		vec = contentVeclecty(vec);
		b2Vec2 vecTob2Vec = b2Vec2(vec.x/PTM_RATIO, vec.y/PTM_RATIO);
		playerBody->SetLinearVelocity(vecTob2Vec);
		speedx = vecTob2Vec.x;
	}

	if(penshebatch->getChildByTag(1))
		penshebatch->getChildByTag(1)->setPosition(player->getPositionX(), player->getPositionY()+10);
	if(bulletType == 2)
	{
		std::list<b2Body*>::iterator itr1;
		for(itr1 = bullets.begin(); itr1 != bullets.end(); ++itr1)
		{
			Sprite *temp_bullet = (Sprite*)((b2Body*)*itr1)->GetUserData();
			if(temp_bullet->getTag() == 111)
				continue;
			BulletSprite *bullet = (BulletSprite*)((b2Body*)*itr1)->GetUserData();
			if(bullet->TYPE == 2)
			{
				((b2Body*)*itr1)->SetLinearVelocity(b2Vec2(speedx, ((b2Body*)*itr1)->GetLinearVelocity().y));
			}
		}

		int size = JGbullets.size();
		std::list<JGbullet*>::iterator itr2;
		for(itr2 = JGbullets.begin(); itr2 != JGbullets.end(); ++itr2)
		{
			JGbullet *bullet = (JGbullet*)*itr2;
			if(bullet->getTag() == 10)
			{
				bullet->setPosition(bullet->location + player->getPosition());
			}
		}
	}
}
/**
	level@子弹等级
	type@子弹类型
*/
void GameScene::shotBullets(float dt)
{
	if(player->isWiDi)
		return;
	switch(bulletType)
	{
	case 0:
		shutOnceTime+=dt;
		if(shutOnceTime >=  shutTime)
		{
			int bulletNumber = (bulletLevel+1)*4;
			float maxAngle = (bulletLevel+1)*20;
			float temp = maxAngle/(bulletNumber-1);
			for(int i = 0; i < bulletNumber; ++i)
			{
				float angle =  90 - maxAngle/2 + i*temp;
				BulletSprite *bullet = BulletSprite::create(1);
				bullet->setPosition(player->getPosition());
				bullet->setRotation(angle);
				//addChild(bullet, 50);
				bulletBatch->addChild(bullet, 50);
				bullet->setType(bulletType);

				b2BodyDef bulletBodyDef;
				bulletBodyDef.type = b2_dynamicBody;
				bulletBodyDef.bullet = true;
				bulletBodyDef.position.Set(playerBody->GetPosition().x, playerBody->GetPosition().y);

				b2Body *bulletBody = world->CreateBody(&bulletBodyDef);
				bulletBody->SetUserData(bullet);
				bulletBody->SetBullet(true);

				b2PolygonShape polygonShape;
				polygonShape.SetAsBox(bullet->getContentSize().width/2/PTM_RATIO, 
					bullet->getContentSize().height/2/PTM_RATIO);

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &polygonShape;
				fixtureDef.density = 0;
				fixtureDef.restitution = 0;
				fixtureDef.friction = 0;
				fixtureDef.filter.groupIndex = -2;

				bulletBody->CreateFixture(&fixtureDef)->SetDensity(0);
				bulletBody->ResetMassData();
				bulletBody->SetFixedRotation(true);
			
				float ration = CC_DEGREES_TO_RADIANS(angle);
				
				bulletBody->SetTransform(playerBody->GetPosition(), ration);
				bulletBody->SetLinearVelocity(b2Vec2((float)BULLET_VELOCITY*cos(ration), (float)BULLET_VELOCITY*sin(ration)));
				
				bullets.push_back(bulletBody);
			}
			shutOnceTime = 0;
			if (!isBaozou)
			{
				if(shutTime == (float)BULLET_ONCE_TIME)
					shutTime = (float)BULLET_TWICE_TIME;
				else
					shutTime = (float)BULLET_ONCE_TIME;
			}
			
		}	
		break;
	case 1:
		shutOnceTime+=dt;
		if(shutOnceTime >=  shutTime)
		{
			int bulletNumber = (bulletLevel+2)*2+1;
			//float maxAngle = (bulletLevel+1)*20;
			//float temp = maxAngle/(bulletNumber-1);
			float temp_y = player->getPosition().y+20;
			float max_width = bulletLevel*10+100;
			for(int i = 0; i < bulletNumber; ++i)
			{
				//float angle =  90 - maxAngle/2 + i*temp;
				float x = player->getPosition().x - max_width/2 + i*max_width/(bulletNumber-1);
				BulletSprite *bullet = BulletSprite::create(2);
				bullet->setPosition(player->getPosition());
				//addChild(bullet, 50);
				bulletBatch->addChild(bullet, 50);
				bullet->setType(bulletType);

				b2BodyDef bulletBodyDef;
				bulletBodyDef.type = b2_dynamicBody;
				bulletBodyDef.bullet = true;
				bulletBodyDef.position.Set(x/PTM_RATIO, temp_y/PTM_RATIO);
				float cout_y = 10;
				if(i >= (bulletNumber-1)/2)
					cout_y = - cout_y;
				temp_y += cout_y;

				b2Body *bulletBody = world->CreateBody(&bulletBodyDef);
				bulletBody->SetUserData(bullet);
				bulletBody->SetBullet(true);

				b2PolygonShape polygonShape;
				polygonShape.SetAsBox(bullet->getContentSize().width/2/PTM_RATIO, 
					bullet->getContentSize().height/2/PTM_RATIO);

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &polygonShape;
				fixtureDef.density = 0;
				fixtureDef.restitution = 0;
				fixtureDef.friction = 0;
				fixtureDef.filter.groupIndex = -2;

				bulletBody->CreateFixture(&fixtureDef)->SetDensity(0);
				bulletBody->ResetMassData();
				bulletBody->SetFixedRotation(true);
			
				bulletBody->SetLinearVelocity(b2Vec2(0, (float)BULLET_VELOCITY));
				
				bullets.push_back(bulletBody);
			}
			shutOnceTime = 0;
			if (!isBaozou)
			{
				if(shutTime == (float)BULLET_ONCE_TIME)
					shutTime = (float)BULLET_TWICE_TIME;
				else
					shutTime = (float)BULLET_ONCE_TIME;
			}
		}

		break;
	case 2:
		shutOnceTime += dt;
		if(shutOnceTime > (float)BULLET_ONCE_TIME)
		{
			for(int i = 0; i < bulletLevel; ++i)
			{
				BulletSprite *bulletCenter1 = BulletSprite::createWithTexture(bulletBatch->getTexture(), JiGziDanCenterRect);
				BulletSprite *bulletCenter2 = BulletSprite::createWithTexture(bulletBatch->getTexture(), JiGziDanCenterRect);
				int x1 = player->getPosition().x - 2*i*JiGziDanCenterViewRect.size.width - JiGziDanCenterViewRect.size.width - 0;
				int x2 = player->getPosition().x + 2*i*JiGziDanCenterViewRect.size.width + JiGziDanCenterViewRect.size.width - 0;
		
				//addChild(bulletCenter1, 50);
				//addChild(bulletCenter2, 50);
				bulletCenter1->setType(bulletType);
				bulletCenter2->setType(bulletType);

				bulletBatch->addChild(bulletCenter1, 50);
				bulletBatch->addChild(bulletCenter2, 50);

				bulletCenter1->setPosition(x1, player->getPosition().y + JiGziDanCenterRect.size.height/2);
				bulletCenter2->setPosition(x2, player->getPosition().y + JiGziDanCenterRect.size.height/2);

				b2BodyDef bullet1BodyDef;
				bullet1BodyDef.type = b2_dynamicBody;
				bullet1BodyDef.position.Set(bulletCenter1->getPosition().x/PTM_RATIO,
					(bulletCenter1->getPosition().y)/PTM_RATIO);

				b2BodyDef bullet2BodyDef;
				bullet2BodyDef.type = b2_dynamicBody;
				bullet2BodyDef.position.Set(bulletCenter2->getPosition().x/PTM_RATIO,
					(bulletCenter2->getPosition().y)/PTM_RATIO);

				b2Body *bullet1Body = world->CreateBody(&bullet1BodyDef);
				b2Body *bullet2Body = world->CreateBody(&bullet2BodyDef);
				bullet1Body->SetUserData(bulletCenter1);
				bullet2Body->SetUserData(bulletCenter2);
				bullet1Body->SetBullet(true);
				bullet2Body->SetBullet(true);

				b2PolygonShape polygonShape1;
				polygonShape1.SetAsBox((JiGziDanCenterRect.size.width-3)/PTM_RATIO, 
					JiGziDanCenterRect.size.height/PTM_RATIO);

				b2PolygonShape polygonShape2;
				polygonShape2.SetAsBox((JiGziDanCenterRect.size.width-3)/PTM_RATIO, 
					JiGziDanCenterRect.size.height/PTM_RATIO);

				b2FixtureDef fixtureDef1;
				fixtureDef1.shape = &polygonShape1;
				fixtureDef1.density = 0;
				fixtureDef1.restitution = 0;
				fixtureDef1.friction = 0;
				fixtureDef1.filter.groupIndex = -2;

				b2FixtureDef fixtureDef2;
				fixtureDef2.shape = &polygonShape2;
				fixtureDef2.density = 0;
				fixtureDef2.restitution = 0;
				fixtureDef2.friction = 0;
				fixtureDef2.filter.groupIndex = -2;

				bullet1Body->CreateFixture(&fixtureDef1)->SetDensity(0);
				bullet1Body->ResetMassData();
				bullet1Body->SetFixedRotation(true);

				bullet2Body->CreateFixture(&fixtureDef2)->SetDensity(0);
				bullet2Body->ResetMassData();
				bullet2Body->SetFixedRotation(true);
			
				bullet1Body->SetLinearVelocity(b2Vec2(0, (float)JG_BULLET_VELOCITY));
				bullet2Body->SetLinearVelocity(b2Vec2(0, (float)JG_BULLET_VELOCITY));
				bullets.push_back(bullet1Body);
				bullets.push_back(bullet2Body);
			}
			BulletSprite *bulletLeft = BulletSprite::createWithTexture(bulletBatch->getTexture(), JiGziDanLeftRect);
			BulletSprite *bulletRight = BulletSprite::createWithTexture(bulletBatch->getTexture(), JiGziDanRightRect);

			bulletBatch->addChild(bulletLeft, 50);
			bulletBatch->addChild(bulletRight, 50);

			bulletLeft->setType(bulletType);
			bulletRight->setType(bulletType);

			b2BodyDef bulletLeftBodyDef;
			bulletLeftBodyDef.type = b2_dynamicBody;
			bulletLeftBodyDef.position.Set((player->getPosition().x 
				- 2*bulletLevel*JiGziDanCenterViewRect.size.width-JiGziDanLeftViewRect.size.width-4 )/PTM_RATIO,
				(player->getPosition().y + JiGziDanLeftRect.size.height/2)/PTM_RATIO);

			b2BodyDef bulletRightBodyDef;
			bulletRightBodyDef.type = b2_dynamicBody;
			bulletRightBodyDef.position.Set((player->getPosition().x 
			+ 2*bulletLevel*JiGziDanCenterViewRect.size.width+JiGziDanRightViewRect.size.width+4 )/PTM_RATIO,
				(player->getPosition().y + JiGziDanRightRect.size.height/2)/PTM_RATIO);

			b2Body *bulletLeftBody = world->CreateBody(&bulletLeftBodyDef);
			b2Body *bulletRightBody = world->CreateBody(&bulletRightBodyDef);
			bulletLeftBody->SetUserData(bulletLeft);
			bulletRightBody->SetUserData(bulletRight);

			b2PolygonShape polygonShapeLeft;
			polygonShapeLeft.SetAsBox((JiGziDanLeftRect.size.width-2)/PTM_RATIO, 
				JiGziDanLeftRect.size.height/PTM_RATIO);

			b2PolygonShape polygonShapeRight;
			polygonShapeRight.SetAsBox((JiGziDanRightRect.size.width-2)/PTM_RATIO, 
				JiGziDanRightRect.size.height/PTM_RATIO);

			b2FixtureDef fixtureDefLeft;
			fixtureDefLeft.shape = &polygonShapeLeft;
			fixtureDefLeft.density = 0;
			fixtureDefLeft.restitution = 0;
			fixtureDefLeft.friction = 0;
			fixtureDefLeft.filter.groupIndex = -2;

			b2FixtureDef fixtureDefRight;
			fixtureDefRight.shape = &polygonShapeRight;
			fixtureDefRight.density = 0;
			fixtureDefRight.restitution = 0;
			fixtureDefRight.friction = 0;
			fixtureDefRight.filter.groupIndex = -2;

			bulletLeftBody->CreateFixture(&fixtureDefLeft)->SetDensity(0);
			bulletLeftBody->ResetMassData();
			bulletLeftBody->SetFixedRotation(true);

			bulletRightBody->CreateFixture(&fixtureDefRight)->SetDensity(0);
			bulletRightBody->ResetMassData();
			bulletRightBody->SetFixedRotation(true);
			
			bulletLeftBody->SetLinearVelocity(b2Vec2(0, (float)BULLET_VELOCITY));
			bulletRightBody->SetLinearVelocity(b2Vec2(0, (float)BULLET_VELOCITY));
			bullets.push_back(bulletLeftBody);
			bullets.push_back(bulletRightBody);
			shutOnceTime = 0;
		}
		break;
	default:
		break;
	}
}

void GameScene::addremoveBullets()
{
	std::list<b2Body*>::iterator itr;
	for(itr = bullets.begin(); itr != bullets.end();)
	{
		b2Body *bulletBody = (b2Body*)*itr;
		Point point(bulletBody->GetPosition().x * PTM_RATIO, bulletBody->GetPosition().y * PTM_RATIO);
		if(point.x < -50 | point.x > 690 | point.y < -50 | point.y > 1050)
		{
			itr = bullets.erase(itr);
			deleteBullets.push_back(bulletBody);	
		}
		else
			++itr;
	}

}
void GameScene::addAllRemoveBullets()
{
	std::list<b2Body*>::iterator itr;
	for(itr = bullets.begin(); itr != bullets.end();)
	{
		b2Body *bulletBody = (b2Body*)*itr;
		((Sprite*)bulletBody->GetUserData())->setVisible(false);
		itr = bullets.erase(itr);
		deleteBullets.push_back(bulletBody);	

	}
}
/*
   @point : 创建坐标
   @level : 创建敌机的等级
   @tarGetPoint   : 敌机的运动的目标点
   @veclecty: 敌机速度
   @angle: 敌机运动到目标点后改变方向（改变后的角度）
   @startShutTime: 敌机运动多久后开始射击
*/
void GameScene::createDiJi(Point point, int _level, Point tarGetPoint, float veclecty,float angle, float startShutTime)
{
	float width;
	float height;
	DiJiSprite *diJi = DiJiSprite::create(_level);
	switch(_level)
	{
	case 0:
		width = 35/PTM_RATIO;
		height = 35/PTM_RATIO;
		break;
	case 1:
		width = 40/PTM_RATIO;
		height = 40/PTM_RATIO;
		break;
	case 2:
		width = 60/PTM_RATIO;
		height = 40/PTM_RATIO;
		break;
	case 3:
		width = 65/PTM_RATIO;
		height = 40/PTM_RATIO;
		break;
	case 4:
		width = 70/PTM_RATIO;
		height = 60/PTM_RATIO;
		break;
	default:
		width = 35/PTM_RATIO;
		height = 35/PTM_RATIO;
		break;
	}
	diJi->setLevel(_level);
	diJi->setAddAngle(angle);
	diJi->setPosition(point);
	diJi->veclecty = veclecty;
	diJi->startShutTime = startShutTime;
	diJi->changeAngleRect = Rect(tarGetPoint.x - 5, tarGetPoint.y - 5, 10, 10);
	addChild(diJi, 49);

	b2BodyDef diJiBodyDef;
	diJiBodyDef.type = b2_dynamicBody;
	diJiBodyDef.position.Set(point.x/PTM_RATIO, point.y/PTM_RATIO);
	b2Body *diJiBody = world->CreateBody(&diJiBodyDef);
	diJiBody->SetUserData(diJi);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(height, width);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0;
	fixtureDef.restitution = 0;
	fixtureDef.friction = 0;
	fixtureDef.filter.groupIndex = 2;

	float ration = (tarGetPoint - point).getAngle();//CC_DEGREES_TO_RADIANS((tarGetPoint - point).getAngle());
	diJiBody->CreateFixture(&fixtureDef);
	diJiBody->SetFixedRotation(true);
	diJiBody->SetTransform(diJiBody->GetPosition(), ration);
	diJiBody->SetLinearVelocity(b2Vec2(veclecty*cos(ration), veclecty*sin(ration)));

	diJis.push_back(diJiBody);
	
}

void GameScene::addDeleteBullet(b2Body *body)
{
	bullets.remove(body);
	std::vector<b2Body*>::iterator ret;
	ret = std::find(deleteBullets.begin(), deleteBullets.end(), body);
	if(ret == deleteBullets.end())//deleteBullets中不存在相同元素
		deleteBullets.push_back(body);
}

void GameScene::destoryBullets()
{
	int size = deleteBullets.size();
	if(size != 0)
	{
		std::vector<b2Body*>::iterator itr;
		for(itr = deleteBullets.begin(); itr != deleteBullets.end(); ++itr)
		{
			b2Body *bulletBody = (b2Body*)*itr;			
			BulletSprite *bullet = (BulletSprite*)bulletBody->GetUserData();
			bullet->removeFromParentAndCleanup(true);
			world->DestroyBody(bulletBody);			
		}
		deleteBullets.clear();
	}
}

void GameScene::addremoveDiJi()
{
	std::list<b2Body*>::iterator itr1;
	for(itr1 = diJis.begin(); itr1 != diJis.end(); )
	{
		Point point(((b2Body*)*itr1)->GetPosition().x * PTM_RATIO, ((b2Body*)*itr1)->GetPosition().y * PTM_RATIO);
		if(point.y < -200 | point.y > 1300)
		{
			b2Body *diJiBody = (b2Body*)*itr1;
			itr1 = diJis.erase(itr1);
			deleteDiJis.push_back(diJiBody);	
		}
		else
			++itr1;
	}
}

void GameScene::destoryDiJis()
{
	int size = deleteDiJis.size();
	if(size != 0)
	{
		for(int i = 0; i < size; ++ i)
		{
			b2Body *diJiBody = (b2Body*)deleteDiJis.at(i);			
			DiJiSprite *diJi = (DiJiSprite*)diJiBody->GetUserData();
			if(diJi->isBoom)
			{
				showBoomParticle(diJi->getPosition(), diJi->level);
			}
			if (diJi->level > 1 && diJi->getPositionX() > 0 && diJi->getPositionX() < 640 &&  diJi->getPositionY() > 0
				&& diJi->getPositionY() < 960)
			{
				int _random  = rand()%10;
				if (_random > 8)
				{
					Money* money = Money::create(1);
					money->setPosition(diJi->getPosition());
					addChild(money, 100);
					moneys.push_back(money);
					money->runAction(RepeatForever::create(RotateBy::create(1, 360)));
				}
				else if(_random > 1)
				{
					Money* money = Money::create(0);
					money->setPosition(diJi->getPosition());
					addChild(money, 100);
					moneys.push_back(money);
					money->runAction(RepeatForever::create(RotateBy::create(1, 360)));
				}
			}
			diJi->removeFromParentAndCleanup(true);
			world->DestroyBody(diJiBody);			
		}
		deleteDiJis.clear();
	}
}

void GameScene::subDiJiLife(b2Body *diJiBody, float damege)
{
	DiJiSprite *diji = (DiJiSprite*)diJiBody->GetUserData();
	if(diji->life > 0)
	{
		diji->life -= damege;		
	}
	else
	{
		if(!diji->isBoom)
		{
			diji->isBoom = true;
			if(isSoundOpen)
				SimpleAudioEngine::getInstance()->playEffect(boom_sound.c_str());
			diJis.remove(diJiBody);
			deleteDiJis.push_back(diJiBody);
		}
	}
}

void GameScene::subDiJiLife(b2Body *diJiBody, b2Body *bulletBody)
{
	DiJiSprite *diji = (DiJiSprite*)diJiBody->GetUserData();
	BulletSprite *bullet = (BulletSprite*)bulletBody->GetUserData();
	if(diji->life > 0)
	{
		diji->life -= bullet->ATK;		
	}
	else
	{
		if(!diji->isBoom)
		{
			diji->isBoom = true;
			if(isSoundOpen)
				SimpleAudioEngine::getInstance()->playEffect(boom_sound.c_str());
			diJis.remove(diJiBody);
			deleteDiJis.push_back(diJiBody);
		}
	}
}
/**
	point@爆炸坐标
	level@爆炸等级（范围）
*/
void GameScene::showBoomParticle(Point point,int level)
{
	ParticleSystem *boomParticle = MyParticle::create(boomPlistData, "lizi/boom.plist");  
	//std::string listFilePath = "lizi/boom.plist";
	//boomParticle->initWithDictionary(boomPlistData, listFilePath.c_str());
	boomParticle->retain();  
	boomParticle->setTexture(boom);
	boomParticle->setPosition(point);
	
	boomParticle->setEndRadius(boomParticle->getEndRadius()*(level+1)+20);
	boomParticle->setStartSize(boomParticle->getStartSize()*(level+1)+2);
	boomParticle->setEmissionRate(boomParticle->getEmissionRate()*(level+1));
	boomParticle->setAutoRemoveOnFinish(true);
	boombatch->addChild(boomParticle);
	boomParticle->release(); 
	
	/*
	Sprite *boom = Sprite::createWithSpriteFrameName("boom_1.png");
	boom->setPosition(point);
	addChild(boom, 50);
	boom->setScale((level+1)*0.3);
	Animation* animation = Animation::createWithSpriteFrames(Manager::Instance()->booms);
	animation->setDelayPerUnit(0.04f);
	animation->setLoops(1);
	Animate* anim = Animate::create(animation);
	boom->runAction(Sequence::create(anim, RemoveSelf::create(true), NULL));
	*/
}
/**
	point@被击中坐标
*/
void GameScene::showBinGoParticle(Point point)
{
	ParticleSystem *boomParticle = MyParticle::create(binGonplistData, "lizi/binGon.plist");  
	//ParticleSystem *boomParticle = ParticleSystemQuad::create("lizi/binGon.plist");  
	boomParticle->retain();  
	boomParticle->setTexture(boom);
	
	boomParticle->setPosition(point);
	boomParticle->setAutoRemoveOnFinish(true);
	binGobatch->addChild(boomParticle);	
		
	boomParticle->release(); 
}

void GameScene::showJGBinGoParticle(Point point, int tag)
{
	ParticleSystem *JGParticle = MyParticle::create(jgBingoPlistData,"lizi/JGbingo.plist");  
	JGParticle->retain();  
	JGParticle->setTexture(shot);
	JGParticle->setPositionType(ParticleSystem::PositionType::GROUPED);
	JGParticle->setPosition(point);
	JGParticle->setTag(tag);
	JGbatch->addChild(JGParticle);	
	JGbinggos.push_back(JGParticle);
	JGParticle->release(); 
}
void GameScene::initJGbullet()
{
	std::list<JGbullet*>::iterator iterator;
	for (iterator = JGbullets.begin(); iterator != JGbullets.end(); ++iterator)
	{
		(*iterator)->removeFromParentAndCleanup(true);
	}
	JGbullets.clear();

	if(bulletType == 2)
	{
		int id = 2;
		for(int i = 0; i < bulletLevel; i++)
		{
			JGbullet *bulletCenter1 = JGbullet::createWithTexture(bulletsTexture, JiGziDanCenterViewRect);
			JGbullet *bulletCenter2 = JGbullet::createWithTexture(bulletsTexture, JiGziDanCenterViewRect);
			int x1 = player->getPosition().x - 2*i*JiGziDanCenterViewRect.size.width - JiGziDanCenterViewRect.size.width;
			int x2 = player->getPosition().x + 2*i*JiGziDanCenterViewRect.size.width + JiGziDanCenterViewRect.size.width;
			addChild(bulletCenter1, 50);
			addChild(bulletCenter2, 50);
			bulletCenter1->setTag(10);
			bulletCenter2->setTag(10);
			bulletCenter1->id = id;
			bulletCenter2->id = id+1;
			bulletCenter1->setScale(2);
			bulletCenter2->setScale(2);
			bulletCenter1->setAnchorPoint(Point(0.5, 0));
			bulletCenter2->setAnchorPoint(Point(0.5, 0));
			bulletCenter1->setPosition(x1, player->getPosition().y+10);
			bulletCenter2->setPosition(x2, player->getPosition().y+10);
			bulletCenter1->location = bulletCenter1->getPosition() - player->getPosition();
			bulletCenter2->location = bulletCenter2->getPosition() - player->getPosition();

			JGbullets.push_back(bulletCenter1);
			JGbullets.push_back(bulletCenter2);
			id += 2;
			
		}
		JGbullet *bulletLeft = JGbullet::createWithTexture(bulletsTexture, JiGziDanLeftViewRect);
		JGbullet *bulletRight = JGbullet::createWithTexture(bulletsTexture, JiGziDanRightViewRect);

		bulletLeft->setScale(2);
		bulletRight->setScale(2);
		bulletLeft->id = 0;
		bulletRight->id = 1;
		bulletLeft->setAnchorPoint(Point(0.5, 0));
		bulletRight->setAnchorPoint(Point(0.5, 0));

		bulletLeft->setPosition(player->getPosition().x 
			- 2*bulletLevel*JiGziDanCenterViewRect.size.width-JiGziDanLeftViewRect.size.width,
			player->getPosition().y+10);	
		
		bulletRight->setPosition(player->getPosition().x - 1
			+ 2*bulletLevel*JiGziDanCenterViewRect.size.width+JiGziDanRightViewRect.size.width,
			player->getPosition().y+10);
		bulletLeft->location = bulletLeft->getPosition() - player->getPosition();
		bulletRight->location = bulletRight->getPosition() - player->getPosition();

		addChild(bulletLeft, 50);
		addChild(bulletRight, 50);

		bulletLeft->setTag(10);
		bulletRight->setTag(10);


		JGbullets.push_back(bulletLeft);
		JGbullets.push_back(bulletRight);

		//激光子弹特效
		/*JGbullet *sdSprite1 = JGbullet::createWithTexture(bulletsTexture, sdAnimation1);
		addChild(sdSprite1, 51);
		sdSprite1->setAnchorPoint(Point(0.5, 0));
		sdSprite1->setPosition(bulletLeft->getPosition().x-10, bulletLeft->getPosition().y);
		sdSprite1->setScaleY(2);
		sdSprite1->setScaleX((bulletLevel+1)*0.5);
		sdSprite1->location = sdSprite1->getPosition()-player->getPosition();
		sdSprite1->setTag(10);

		JGbullet *sdSprite2 = JGbullet::createWithTexture(bulletsTexture, sdAnimation1);
		addChild(sdSprite2, 51);
		sdSprite2->setAnchorPoint(Point(0.5, 0));
		sdSprite2->setPosition(bulletRight->getPosition());
		sdSprite2->setScaleY(2);
		sdSprite2->setScaleX((bulletLevel+1)*0.5);
		sdSprite2->location = sdSprite2->getPosition()-player->getPosition();
		sdSprite2->setTag(10);
		
		SpriteFrame *frame0, *frame1, *frame2, *frame3, *frame4, *frame5, *frame6
			, *frame7, *frame8, *frame9;

		frame0 = SpriteFrame::createWithTexture(bulletsTexture, sdAnimation1);
		frame1 = SpriteFrame::createWithTexture(bulletsTexture, sdAnimation2);
		frame2 = SpriteFrame::createWithTexture(bulletsTexture, sdAnimation3);
		frame3 = SpriteFrame::createWithTexture(bulletsTexture, sdAnimation4);
		frame4 = SpriteFrame::createWithTexture(bulletsTexture, sdAnimation5);
		frame5 = SpriteFrame::createWithTexture(bulletsTexture, sdAnimation6);
		frame6 = SpriteFrame::createWithTexture(bulletsTexture, sdAnimation7);
	
		Vector<SpriteFrame*> actions;

		actions.pushBack(frame0);
		actions.pushBack(frame1);
		actions.pushBack(frame2);
		actions.pushBack(frame3);
		actions.pushBack(frame4);
		actions.pushBack(frame5);
		actions.pushBack(frame6);

		Animation *animation = Animation::createWithSpriteFrames(actions, 0.1f);
		animation->setLoops(-1);
		Animate *anima = Animate::create(animation);
		anima->setTag(1);
		//Animate *animaCopy = anima->clone();

		sdSprite2->runAction(anima->clone()->reverse());
		sdSprite1->runAction(anima);

		JGbullets.push_back(sdSprite1);
		JGbullets.push_back(sdSprite2);*/

		
	}
}

void GameScene::destoryJGbullet()
{
	std::list<JGbullet*>::iterator itr;
	for(itr = JGbullets.begin(); itr != JGbullets.end(); ++itr)
	{
		JGbullet *sprite = (JGbullet*)*itr;
		sprite->setVisible(false);
	}
}
void GameScene::showJGbullet()
{
	std::list<JGbullet*>::iterator itr;
	for(itr = JGbullets.begin(); itr != JGbullets.end(); ++itr)
	{
		JGbullet *sprite = (JGbullet*)*itr;
		sprite->setVisible(true);
	}
}

void GameScene::updateJGbullet()
{
	if(player->isWiDi)
		return;
	std::list<JGbullet*>::iterator itr2;
	for(itr2 = JGbullets.begin(); itr2 != JGbullets.end(); ++itr2)
	{
		JGbullet *bullet = (JGbullet*)*itr2;
		if(bullet->getTag() == 10)
		{
			b2Vec2 point1;
			if(bullet->getPosition().x < player->getPosition().x)
				point1 = b2Vec2((bullet->getPosition().x - bullet->getContentSize().width)/PTM_RATIO
				,( player->getPosition().y+10)/PTM_RATIO);
			else
				point1 = b2Vec2((bullet->getPosition().x + bullet->getContentSize().width)/PTM_RATIO
				,( player->getPosition().y+10)/PTM_RATIO);
			b2Vec2 point2(point1.x, 1000/PTM_RATIO);
		
			world->RayCast(&rayCastCallback, point1, point2);
			
			if(rayCastCallback._fraction < 1 && rayCastCallback._fraction > 0)
			{
				int index = rayCastCallback._fixture->GetFilterData().groupIndex;
				float len = (point2.y - point1.y)*PTM_RATIO;
				Rect rect = bullet->getTextureRect();
				rect.size.height = len*rayCastCallback._fraction/2;
				bullet->setTextureRect(rect);
				bullet->setPosition(bullet->getPosition().x,
					player->getPosition().y+10);
				bullet->location = bullet->getPosition()-player->getPosition();
				if(index == 2 || index == 4  || index == -1)
				{
					
					int id = bullet->id;
					Point contactPoint(bullet->getPosition().x, player->getPosition().y+10 + len*rayCastCallback._fraction);
					if(JGbatch->getChildByTag(200+id) !=NULL)
					{
						if(index != -1)
							JGbatch->getChildByTag(200+id)->setPosition(contactPoint);
						else
							JGbatch->getChildByTag(200+id)->setPosition(Point(contactPoint.x, contactPoint.y+50));
						if(!JGbatch->getChildByTag(200+id)->isVisible())
							JGbatch->getChildByTag(200+id)->setVisible(true);
					}
					else
					{
						if(index != -1)
							showJGBinGoParticle(contactPoint, 200+id);
						else
							showJGBinGoParticle(Point(contactPoint.x, contactPoint.y+50), 200+id);
					}
				}
				/*
				else if(index == -1)
				{
					int id = bullet->id;
					if(JGbatch->getChildByTag(200+id))
					{
						JGbatch->getChildByTag(200+id)->setVisible(false);
						//JGbatch->getChildByTag(200+id)->removeFromParentAndCleanup(true);
					}
				}
				*/
			}
		}
	}
	
}

void GameScene::initShotAnima()
{
	if(bulletType != 2)
		return;
	penshebatch->removeAllChildrenWithCleanup(true);
	ParticleSystem *JGParticle = ParticleSystemQuad::create("lizi/penshe.plist");  
	JGParticle->retain();  
	JGParticle->setTexture(penshe);
	JGParticle->setStartSpinVar(60);
	JGParticle->setPositionType(ParticleSystem::PositionType::GROUPED);
	JGParticle->setPosition(player->getPosition());
	JGParticle->setTag(1);
	penshebatch->addChild(JGParticle);	
	updateJGShutAnimaSize();
	JGParticle->release(); 
}
void GameScene::updateJGShutAnimaSize()
{
	ParticleSystem *JGParticle = (ParticleSystem*)penshebatch->getChildByTag(1);
	JGParticle->setStartSize(180+bulletLevel*70);
	JGParticle->setEndSize(210+bulletLevel*70);
}

void GameScene::initParticleBatch()
{
	JGbatch = ParticleBatchNode::createWithTexture(shot);
	addChild(JGbatch, 51);
	binGobatch = ParticleBatchNode::createWithTexture(boom);
	addChild(binGobatch, 51);
	boombatch = ParticleBatchNode::createWithTexture(boom);
	addChild(boombatch, 51);
	penshebatch = ParticleBatchNode::createWithTexture(penshe);
	addChild(penshebatch, 52);
}

int GameScene::getGK()
{
	return guanka;
}
b2World* GameScene::getWorld()
{
	return world;
}
b2Body* GameScene::getPlayerBody()
{
	return playerBody;
}

void GameScene::removeListener()
{
	_eventDispatcher->removeEventListener(touchListener);
}

void GameScene::stopShutBullet()
{
	player->isWiDi = true;
	destoryJGbullet();
	if(bulletType == 2)
	{
		penshebatch->removeAllChildrenWithCleanup(true);
		JGbatch->removeAllChildrenWithCleanup(true);
	}
}

bool GameScene::fuHuo()
{
	if(playerLife < 1)
	{
		//游戏结束或者充值买命
		isGameOver = true;
		scheduleOnce(schedule_selector(GameScene::showFail), 1.5f);
		return false;
	}
	playerLife--;
	life_text->setText(Tool::toString(playerLife));
	UserDefault::getInstance()->setIntegerForKey("life", playerLife);
	player->setVisible(true);
	b2Filter filter;
	filter.groupIndex = -1;
	playerBody->GetFixtureList()->SetFilterData(filter);
	playerBody->SetTransform(b2Vec2(320/PTM_RATIO, -300/PTM_RATIO), playerBody->GetAngle());
	playerBody->SetLinearVelocity(b2Vec2(0, 6));
	//player->setVisible(true);
	player->isDead = false;
	player->OnWuDi();
	isFuHuoing = true;
	//这里开启主角无敌闪烁
	scheduleOnce(schedule_selector(GameScene::fuHuoing), 2.0f);
	return true;
}

void GameScene::fuHuoing(float dt)
{
	setTouchListener();
	playerBody->SetLinearVelocity(b2Vec2(0, 0));
	tagetTouchPoint = player->getPosition();
	b2Filter filter;
	filter.groupIndex = 1;
	playerBody->GetFixtureList()->SetFilterData(filter);
	isFuHuoing = false;
	scheduleOnce(schedule_selector(GameScene::quXiaoWudi), 1.0f);//1秒后取消闪烁无敌
}
void GameScene::quXiaoWudi(float dt)
{
	if(bulletType == 2)
	{
		initShotAnima();
		initJGbullet();
	}
	player->isWiDi = false;
	player->OffWuDi();
}

PlayerSprite *GameScene::getPlayer()
{
	return player;
}

void GameScene::initPropScene()
{
	Node *scene = static_cast<Widget*>(CSLoader::createNode ("PropScene.csb"));
	addChild(scene, 100);
	max_button = scene->getChildByName<Button*>("Max_button");
	max_button->addTouchEventListener(this, toucheventselector(GameScene::max_click));
	Button* pauseButton = scene->getChildByName<Button*>("pauseButton");
	pauseButton->addTouchEventListener(this, toucheventselector(GameScene::clickPause));
	max_text = scene->getChildByName<Text*>("maxText");
	max_text->setText(Tool::toString(UserDefault::getInstance()->getIntegerForKey("max_cout", 3)));
	life_text = scene->getChildByName<Text*>("lifeText");
	life_text->setText(Tool::toString(UserDefault::getInstance()->getIntegerForKey("life", 3)));
}

void GameScene::max_click(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::BEGAN:
		if(max_cout <= 0)
			return;
		if(this->isFuHuoing || player->isDead)
			return;
		if(isSoundOpen)
		{
			pauseBGmusic();
			this->unschedule(schedule_selector(GameScene::resumeBGmusic));
			SimpleAudioEngine::getInstance()->playEffect(max_sound.c_str());
		}
		show_max_texiao();
		addAllRemoveBullets();
		this->unscheduleUpdate();
		this->player->schedule(schedule_selector(PlayerSprite::max_open));
		max_button->setEnabled(false);
		max_button->setBright(false);
		max_cout--;
		if(max_cout < 0)
			max_cout = 0;
		max_text->setText(Tool::toString(max_cout));
		UserDefault::getInstance()->setIntegerForKey("max_cout", max_cout);
		break;
	default:
		break;
	}
}
void GameScene::show_max_texiao()
{
	Sprite *maxSrite = Sprite::createWithSpriteFrameName("max1.png");
	addChild(maxSrite, player->getZOrder()+1);
	maxSrite->setPosition(player->getPosition());
	//maxSrite->setTag(102);
	maxSrite->setScale(3);
	Animation *animation = Animation::createWithSpriteFrames(Manager::Instance()->maxing, 0.03f, 1);
	Animate* anima = Animate::create(animation);
	maxSrite->runAction(Sequence::create(anima, RemoveSelf::create(), nullptr));
}
void GameScene::resumeBGmusic(float dt)
{
	if(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() >=1 )
	{
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
		this->unschedule(schedule_selector(GameScene::resumeBGmusic));
	}
	else
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(
		SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()+dt);
}
void GameScene::pauseBGmusic()
{
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
}

void GameScene::douDong(float dt)
{
	if(this->getPositionX() > 0)
		this->setPositionX(-3);
	else
		this->setPositionX(3);

	if(this->getPositionY() > 0)
		this->setPositionY(-3);
	else
		this->setPositionY(3);
}

void GameScene::stopDouDong()
{
	this->unschedule(schedule_selector(GameScene::douDong));
	this->setPosition(0, 0);
}

void GameScene::setCanCorcarlt(float dt)
{
	if (game_mode == BOSS_MODE)
	{
		bossUpdate->show_warning();
		this->scheduleOnce(schedule_selector(GameScene::setCanCorcarltTrue), 4);
	}else
	{
		isCanCortarl = true;
		initJGbullet();
		initShotAnima();
	}
	
}

void GameScene::setCanCorcarltTrue(float dt)
{
	isCanCortarl = true;
	initJGbullet();
	initShotAnima();
}

void GameScene::updateMoneyMove(float dt)
{
	std::list<Money*>::iterator itr;
	for (itr = moneys.begin(); itr != moneys.end(); )
	{
		Money* money = *itr;
		Rect rect = Rect(money->getPositionX() - money->getContentSize().width/2
			, money->getPositionY() - money->getContentSize().height/2, 
			money->getContentSize().width, money->getContentSize().height);
		if (rect.containsPoint(player->getPosition()))
		{
			if(money->type == 0)//子弹升级
			{			
				JGbatch->removeAllChildrenWithCleanup(true);
				JGbinggos.clear();
				bulletLevel++;
				if (bulletLevel > 3 )
					bulletLevel = 3;
				if(!player->isWiDi && bulletType == 2)
				{
					updateJGShutAnimaSize();
					initJGbullet();
				}

				if (bulletLevel == 3)//暴走
				{
					isBaozou = true;
					baozou_time = 6;
					shutTime = (float)BULLET_ONCE_TIME;
					this->schedule(schedule_selector(GameScene::baozouUpdate), 1);
					Sprite* crazy = Sprite::createWithSpriteFrameName("crazy.png");
					addChild(crazy, 125);
					crazy->setPosition(320, 500);
					crazy->setScale(0.1f);
					crazy->runAction(Sequence::create(ScaleTo::create(0.4f, 2),DelayTime::create(2),RemoveSelf::create(true), nullptr));
				}
			}
			else if(money->type == 1)//必杀
			{
				max_cout++;
				max_text->setText(Tool::toString(max_cout));
				UserDefault::getInstance()->setIntegerForKey("max_cout", max_cout);
			}
			else if(money->type == 2)//护盾
			{

			}
			money->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f), RemoveSelf::create(), nullptr));
			itr = moneys.erase(itr);
		}
		else
		{
			money->updatePosition(dt);
			++itr;
		}
	}
}

void GameScene::baozouUpdate(float dt)
{
	baozou_time -= dt;
	if (baozou_time <= 0)
	{
		this->unschedule(schedule_selector(GameScene::baozouUpdate));
		isBaozou = false;
		bulletLevel = 2;
		JGbatch->removeAllChildrenWithCleanup(true);
		JGbinggos.clear();
		if(bulletType == 2)
		{
			updateJGShutAnimaSize();
			initJGbullet();
		}
	
	}
}

void GameScene::boss_come(float dt)
{
	bossUpdate->show_warning();
	this->scheduleOnce(schedule_selector(GameScene::setISboss), 4);
}
void GameScene::setISboss(float dt)
{
	isBoss = true;
}

void GameScene::setCancorcarlt(bool _f)
{
	isCanCortarl = _f;
	addAllRemoveBullets();
	world->DestroyBody(bossUpdate->bossBody);
	showBoomParticle(bossUpdate->boss->getPosition()+Point(-50+rand()%80, -50+rand()%80), 2+rand()%6);
	this->schedule(schedule_selector(GameScene::showBossBoom1), 0.3f);
	this->scheduleOnce(schedule_selector(GameScene::showBossBoom2), 2.0f);
}

void GameScene::showBossBoom1(float dt)
{
	showBoomParticle(bossUpdate->boss->getPosition()+Point(-50+rand()%80, -50+rand()%80), 2+rand()%6);
}

void GameScene::showBossBoom2(float dt)
{
	unschedule(schedule_selector(GameScene::showBossBoom1));
	showBoomParticle(bossUpdate->boss->getPosition(), 8);
	bossUpdate->boss->removeFromParentAndCleanup(true);
	_eventDispatcher->removeAllEventListeners();
	world->DestroyBody(playerBody);
	if(!player->isDead)
	{
		scheduleOnce(schedule_selector(GameScene::showPlanOut), 1);
	}
	
}

void GameScene::showPlanOut(float dt)
{
	player->runAction(MoveBy::create(1.0f, Point(0, 1500)));
	scheduleOnce(schedule_selector(GameScene::showPlayerWin), 1);
}

void GameScene::showPlayerWin(float dt)
{
	Node *scene = static_cast<Widget*>(CSLoader::createNode ("WinScene.csb"));
	addChild(scene, 250);
	Button* mainButton = scene->getChildByName<Button*>("Main_Button");
	mainButton->addTouchEventListener(this, toucheventselector(GameScene::Main_button));
	if(game_mode == NORMAL_MODE)
	{
		if(through_gq < guanka)
		{
			through_gq = guanka;
			UserDefault::getInstance()->setIntegerForKey("through_gq", through_gq);
		}
		else
			scene->getChildByName("new_text")->setVisible(false);
	}
}


void GameScene::resume_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		{
			this->removeChildByTag(250);
			scheduleUpdate();
		}		
		break;
	default:
		break;
	}
}

void GameScene::Main_button(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::ENDED:
		{
			Scene *scene = SelectScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}		
		break;
	default:
		break;
	}
}

void GameScene::showFail(float dt)
{
	Node *scene = static_cast<Widget*>(CSLoader::createNode ("FailScene.csb"));
	addChild(scene, 250);
	unscheduleUpdate();
	Button* mainButton = scene->getChildByName<Button*>("Main_Button");
	mainButton->addTouchEventListener(this, toucheventselector(GameScene::Main_button));
}

void GameScene::showPause(float dt)
{
	Node *scene = static_cast<Widget*>(CSLoader::createNode ("PauseScene.csb"));
	addChild(scene, 250);
	scene->setTag(250);
	unscheduleUpdate();
	Button* mainButton = scene->getChildByName<Button*>("Main_Button");
	mainButton->addTouchEventListener(this, toucheventselector(GameScene::Main_button));
	Button* resumeButton = scene->getChildByName<Button*>("goOn_Button");
	resumeButton->addTouchEventListener(this, toucheventselector(GameScene::resume_button));
}

void GameScene::initbgs()
{

	bg1 = Sprite::createWithSpriteFrameName("bg"+Tool::toString(guanqia)+"_1.png");
	bg2 = Sprite::createWithSpriteFrameName("bg"+Tool::toString(guanqia)+"_2.png");
	bg3 = Sprite::createWithSpriteFrameName("bg"+Tool::toString(guanqia)+"_3.png");
	bg1->setScale(2);
	bg2->setScale(2);
	bg3->setScale(2);
	bg1->setPosition(320, 480);
	bg2->setPosition(320, 480 + 960);
	bg3->setPosition(320, 480 + 960 + 960);
	addChild(bg1, 10);
	addChild(bg2, 11);
	addChild(bg3, 12);
}

void GameScene::clickPause(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	switch (type)
	{
	case (int)Widget::TouchEventType::BEGAN:
		{
			showPause(0);
		}		
		break;
	default:
		break;
	}
}
