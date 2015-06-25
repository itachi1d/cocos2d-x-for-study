#include "DiJiSprite.h"
#include "CanShu.h"
#include "GameScene.h"
#include "Tool.h"


void DiJiSprite::setLevel(int _level)
{
	level = _level;
	life = level*2000 + 1000;
	switch(level)
	{
	case 0:
		startShutTime = rand()%3 + 4;
		everyShutTime = (float)DIJI_BULLET_ONCE_TIME_0;
		break;
	case 1:
		everyShutTime = (float)DIJI_BULLET_ONCE_TIME_1;
		break;
	case 2:
		everyShutTime = (float)DIJI_BULLET_ONCE_TIME_2;
		break;
	case 3:
		everyShutTime = (float)DIJI_BULLET_ONCE_TIME_3;
		break;
	case 4:
		everyShutTime = (float)DIJI_BULLET_ONCE_TIME_5;
		break;
	default:
		break;
	}
	changeShutTime = startShutTime;
}

void DiJiSprite::setAddAngle(float _addAngle)
{
	addAngle = _addAngle;
}

void DiJiSprite::beAttackAction()
{
	if(this->getColor() != Color3B::RED)
	{
		color = this->getColor();
		this->setColor(Color3B::RED);
		scheduleOnce(schedule_selector(DiJiSprite::beComeColor), 0.2f);
	}
}

void DiJiSprite::beComeColor(float time)
{
	this->setColor(color);
}

void DiJiSprite::shut_Bullet(float dt)
{
	//当敌机不在屏幕范围内不发射子弹
	if(this->getPositionX()>630 | this->getPositionX()<10 | this->getPositionY()>950 | this->getPositionY()<10)
		return;
	else
	{
		if(isCanShut)
		{
			shutTimeCout += dt;
			shutTimeSum += dt;
			if(shutTimeCout > everyShutTime)
			{
				switch(level)
				{
					case 0:
						shutBullet(shutMode);
						shutTimeSum = 0;
						isCanShut = false;
						break;
					case 1:
						shutBullet(shutMode);
						shutTimeSum = 0;
						isCanShut = false;
						break;
					case 2:
						shutBullet(shutMode);
						if(shutTimeSum - startShutTime > 4)//if连续射击了3秒后
						{
							isCanShut = false;//暂停射击						
							shutTimeSum = startShutTime - 1;//1秒后再开始射击
						}
						break;
					case 3:
						shutBullet(shutMode);
						
						if(shutTimeSum - changeShutTime > 1.5f)
						{
							isRightShut = !isRightShut;
							changeShutTime  += 1.5f;
						}
						if(shutTimeSum - startShutTime > 3)//if连续射击了3秒后
						{
							isCanShut = false;//暂停射击
							//1秒后改变射击模式
							shutTimeSum = startShutTime - 1;
							changeShutTime = startShutTime;
							shutMode += 1;
							if(shutMode > 1)
								shutMode = 0;
						}
						break;
					case 4:
						shutBullet(shutMode);
						if(shutTimeSum - changeShutTime > 2.0f)
						{
							isRightShut = !isRightShut;
							changeShutTime  += 2.0f;
						}
						if(shutTimeSum - startShutTime > 4)//if连续射击了4秒后
						{
							isCanShut = false;//暂停射击
							//1秒后改变射击模式
							shutTimeSum = startShutTime - 1;
							changeShutTime = startShutTime;
							shutMode += 1;
							if(shutMode > 2)
								shutMode = 0;
							switch (shutMode)
							{
							case 0:
								everyShutTime = (float)DIJI_BULLET_ONCE_TIME_5;
								break;
							case 1:
								everyShutTime = (float)DIJI_BULLET_ONCE_TIME_0;
								break;
							case 2:
								everyShutTime = (float)DIJI_BULLET_ONCE_TIME_3;
								break;
							default:
								break;
							}
						}
						break;
					default:
						break;
				}
				shutTimeCout = 0;
			}
		}
		else
		{
			shutTimeSum += dt;
			if(shutTimeSum >= startShutTime)
			{
				isCanShut = true;
			}
		}
	}
}
/*
mode:发射子弹模式(0-2等级的敌机只有一种模式，3等级有两种，4等级3种，mode从1开始)
*/
void DiJiSprite::shutBullet(int mode)
{
	switch (this->level)
	{
	case 0:
		shutBullet_type0(mode);
		break;
	case 1:
		shutBullet_type1(mode);
		break;
	case 2:
		shutBullet_type2(mode);
		break;
	case 3:
		shutBullet_type3(mode);
		break;
	case 4:
		shutBullet_type4(mode);
		break;
	default:
		break;
	}
}

void DiJiSprite::shutBullet_type0(int mode)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	float ration = (layer->getPlayer()->getPosition() - shutPoint1).getAngle();
	createBullet(layer, shutPoint1, 0, CC_RADIANS_TO_DEGREES(ration), (float)DIJI_BULLET_SPEED_TYPE_1);
}
void DiJiSprite::shutBullet_type1(int mode)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	float ration = (layer->getPlayer()->getPosition() - shutPoint1).getAngle();
	float angle = CC_RADIANS_TO_DEGREES(ration);
	createBullet(layer, shutPoint1, 5, angle, (float)DIJI_BULLET_SPEED_TYPE_1);
}
void DiJiSprite::shutBullet_type2(int mode)
{
	float maxAngle = 30;
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	
	for(int i = 0; i < 3; ++i)
	{
		float angle = 270 - 30 + i*5;
		createBullet(layer, shutPoint2, 3, angle, (float)DIJI_BULLET_SPEED_TYPE_2);
		
	}
	for(int i = 0; i < 3; ++i)
	{
		float angle = 270 + 30 - i*5;
		createBullet(layer, shutPoint1, 3, angle, (float)DIJI_BULLET_SPEED_TYPE_2);
	}
}
void DiJiSprite::shutBullet_type3(int mode)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);

	switch (mode)
	{
		float ration;
		float maxAngle;
	case 0:
		ration = (layer->getPlayer()->getPosition() - shutPoint1).getAngle();
		maxAngle = CC_RADIANS_TO_DEGREES(ration)+5;
		for(int i = 0; i < 3; ++i)
		{
			float angle = maxAngle - i*5;
			Point point = shutPoint1;
			if(isRightShut)
				point = shutPoint2;
			createBullet(layer, point, 4, angle, (float)DIJI_BULLET_SPEED_TYPE_2);
		}
		break;
	case 1:
		//float maxAngle = 30;
		for(int i = 0; i < 5; ++i)
		{
			float angle = 240 + i*15;
			Point point = shutPoint1;
			if(isRightShut)
				point = shutPoint2;
			createBullet(layer, point, 4, angle, (float)DIJI_BULLET_SPEED_TYPE_1);
		}
		break;
	default:
		break;
	}
}
void DiJiSprite::shutBullet_type4(int mode)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	Point point;
	int _angle;
	switch (mode)
	{
	case 0:
		if(shutAngle1 < 210)
		{
			shutAngle1 = 210;
			shutAngle2 = 330;
			angleFlag = true;
		}
		if(shutAngle1 > 330)
		{
			shutAngle1 = 330;
			shutAngle2 = 210;
			angleFlag = false;
		}
		if(angleFlag)
		{
			shutAngle1+=7;
			shutAngle2-=7;
		}
		else
		{
			shutAngle1-=7;
			shutAngle2+=7;
		}
		createBullet(layer, shutPoint1, 2, shutAngle1, (float)DIJI_BULLET_SPEED_TYPE_1);
		createBullet(layer, shutPoint2, 2, shutAngle2, (float)DIJI_BULLET_SPEED_TYPE_1);
		break;
	case 1:
		point = shutPoint1;
		if(isRightShut)
			point = shutPoint2;
		_angle =  CC_RADIANS_TO_DEGREES((layer->getPlayer()->getPosition() - point).getAngle());	
		createBullet(layer, point, 7, _angle, (float)DIJI_BULLET_SPEED_TYPE_4);
		break;
	case 2:
		_angle =  CC_RADIANS_TO_DEGREES((layer->getPlayer()->getPosition() - shutPoint1).getAngle());
		if(shutAngle1 < _angle-10)
		{
			shutAngle1 = _angle-10;
			shutAngle2 = _angle+10;
			angleFlag = true;
		}
		if(shutAngle1 > _angle+10)
		{
			shutAngle1 = _angle+10;
			shutAngle2 = _angle-10;
			angleFlag = false;
		}
		if(angleFlag)
		{
			shutAngle1+=5;
			shutAngle2-=5;
		}
		else
		{
			shutAngle1-=5;
			shutAngle2+=5;
		}
		createBullet(layer, shutPoint1, 5, shutAngle1, (float)DIJI_BULLET_SPEED_TYPE_1);
		createBullet(layer, shutPoint2, 5, shutAngle2, (float)DIJI_BULLET_SPEED_TYPE_1);
		break;
	default:
		break;
	}
}
/*pointNumber:0：两个射击点都有效果
			  1：shutPoint1有效果
			  2：shutPoint2有效果
*/
void DiJiSprite::showShut(Layer *_layer, int pointNumber)
{
	GameScene *layer = (GameScene*)_layer;
	switch (level)
	{
	case 0:
		if(!shutFrame1)
		{
			shutFrame1 = Sprite::createWithTexture(layer->shutAnimaTexture, DiJi_Shut0);
			layer->addChild(shutFrame1, 62);
			shutFrame1->setPosition(shutPoint1);
		}
		else
		{
			shutFrame1->setVisible(true);
		}
	
		if(!this->isScheduled(schedule_selector(DiJiSprite::hideShut)))
			this->scheduleOnce(schedule_selector(DiJiSprite::hideShut), 0.2f);
		break;
	case 1:
		if(!shutFrame1)
		{
			shutFrame1 = Sprite::createWithTexture(layer->shutAnimaTexture, DiJi_Shut0);
			layer->addChild(shutFrame1, 62);
			shutFrame1->setPosition(shutPoint1);
		}
		else
		{
			shutFrame1->setVisible(true);
		}
	
		if(!this->isScheduled(schedule_selector(DiJiSprite::hideShut)))
			this->scheduleOnce(schedule_selector(DiJiSprite::hideShut), 0.2f);
		break;
	case 2:
		if(!shutFrame1)
		{
			shutFrame1 = Sprite::createWithTexture(layer->shutAnimaTexture, DiJi_Shut0);
			layer->addChild(shutFrame1, 62);
			shutFrame1->setPosition(shutPoint1);
		}
		else
			shutFrame1->setVisible(true);
		if(!shutFrame2)
		{
			shutFrame2 = Sprite::createWithTexture(layer->shutAnimaTexture, DiJi_Shut0);
			layer->addChild(shutFrame2, 62);
			shutFrame2->setPosition(shutPoint2);
		}
		else
			shutFrame2->setVisible(true);
		if(!this->isScheduled(schedule_selector(DiJiSprite::hideShut)))
			this->scheduleOnce(schedule_selector(DiJiSprite::hideShut), 0.2f);
		break;
	case 3:
		if(pointNumber == 0 || pointNumber == 1)
		{
			if(!shutFrame1)
			{
				shutFrame1 = Sprite::createWithTexture(layer->shutAnimaTexture, DiJi_Shut0);
				layer->addChild(shutFrame1, 62);
				shutFrame1->setPosition(shutPoint1);
			}
			else
				shutFrame1->setVisible(true);
		}
		if(pointNumber == 0 || pointNumber == 2)
		{
			if(!shutFrame2)
			{
				shutFrame2 = Sprite::createWithTexture(layer->shutAnimaTexture, DiJi_Shut0);
				layer->addChild(shutFrame2, 62);
				shutFrame2->setPosition(shutPoint2);
			}
			else
				shutFrame2->setVisible(true);
		}
		if(!this->isScheduled(schedule_selector(DiJiSprite::hideShut)))
			this->scheduleOnce(schedule_selector(DiJiSprite::hideShut), 0.2f);
		break;
		break;
	case 4:
		if(pointNumber == 0 || pointNumber == 1)
		{
			if(!shutFrame1)
			{
				shutFrame1 = Sprite::createWithTexture(layer->shutAnimaTexture, DiJi_Shut0);
				layer->addChild(shutFrame1, 62);
				shutFrame1->setPosition(shutPoint1);
			}
			else
				shutFrame1->setVisible(true);
		}
		if(pointNumber == 0 || pointNumber == 2)
		{
			if(!shutFrame2)
			{
				shutFrame2 = Sprite::createWithTexture(layer->shutAnimaTexture, DiJi_Shut0);
				layer->addChild(shutFrame2, 62);
				shutFrame2->setPosition(shutPoint2);
			}
			else
				shutFrame2->setVisible(true);
		}
		if(!this->isScheduled(schedule_selector(DiJiSprite::hideShut)))
			this->scheduleOnce(schedule_selector(DiJiSprite::hideShut), 0.2f);
		break;
	default:
		break;
	}
}

void DiJiSprite::hideShut(float dt)
{
	if(shutFrame1)
		shutFrame1->setVisible(false);
	if(shutFrame2)
		shutFrame2->setVisible(false);
}
//更新射击点
void DiJiSprite::updateShutPoint()
{
	float angle = -1*CC_DEGREES_TO_RADIANS(this->getRotation());;
	switch (level)
	{
	case 0:
		shutPoint1 = Point(this->getPositionX()+30*cos(angle), this->getPositionY()+35*sin(angle));
		if(shutFrame1)
		{
			shutFrame1->setPosition(shutPoint1);
			shutFrame1->setRotation(this->getRotation());
		}
		break;
	case 1:
		shutPoint1 = Point(this->getPositionX()+27*cos(angle), this->getPositionY()+27*sin(angle));
		if(shutFrame1)
		{
			shutFrame1->setPosition(shutPoint1);
			shutFrame1->setRotation(this->getRotation());
		}
		break;
	case 2:
		shutPoint1 = Point(this->getPositionX()+20, this->getPositionY()-30);
		shutPoint2 = Point(this->getPositionX()-20, this->getPositionY()-30);
		if(shutFrame1)
		{
			shutFrame1->setPosition(shutPoint1);
			shutFrame1->setRotation(this->getRotation());
		}
		if(shutFrame2)
		{
			shutFrame2->setPosition(shutPoint2);
			shutFrame2->setRotation(this->getRotation());
		}
		break;
	case 3:
		shutPoint1 = Point(this->getPositionX()+30, this->getPositionY()-50);
		shutPoint2 = Point(this->getPositionX()-30, this->getPositionY()-50);
		if(shutFrame1)
		{
			shutFrame1->setPosition(shutPoint1);
			shutFrame1->setRotation(this->getRotation());
		}
		if(shutFrame2)
		{
			shutFrame2->setPosition(shutPoint2);
			shutFrame2->setRotation(this->getRotation());
		}
		break;
	case 4:
		shutPoint2 = Point(this->getPositionX()+30, this->getPositionY()-20);
		shutPoint1 = Point(this->getPositionX()-30, this->getPositionY()-20);
		if(shutFrame1)
		{
			shutFrame1->setPosition(shutPoint1);
			shutFrame1->setRotation(this->getRotation());
		}
		if(shutFrame2)
		{
			shutFrame2->setPosition(shutPoint2);
			shutFrame2->setRotation(this->getRotation());
		}
		break;
		break;
	default:
		break;
	}
}
DiJiSprite::~DiJiSprite()
{
	if(shutFrame1)
		shutFrame1->removeFromParentAndCleanup(true);
	if(shutFrame2)
		shutFrame2->removeFromParentAndCleanup(true);
}
/*
	shutPos:子弹发出点
	bullet_type:子弹类型
	vec:速度
*/
void DiJiSprite::createBullet(Layer *_layer,Point shutPos, int bullet_type, float angle, float vec)
{
	auto scene = Director::getInstance()->getRunningScene();
	GameScene* layer = (GameScene*)scene->getChildByTag(0);
	std::string pic_name = "z_DiJi_Bullet"+Tool::toString(bullet_type)+".png";
	Sprite *bullet = Sprite::createWithSpriteFrameName(pic_name);
	if (bullet_type == 0)
		bullet->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.3f, 1.2f), ScaleTo::create(0.3f, 0.8f), nullptr)));
	else if (bullet_type == 7)
		bullet->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.3f, 1.2f), ScaleTo::create(0.3f, 0.8f), nullptr)));
	layer->diJiBulletBatch->addChild(bullet, 61);
	bullet->setTag(111);
	b2BodyDef bulletBodyDef;
	bulletBodyDef.position.Set(shutPos.x/PTM_RATIO, shutPos.y/PTM_RATIO);
	bulletBodyDef.type = b2_dynamicBody;
	b2Body *bulletBody = layer->getWorld()->CreateBody(&bulletBodyDef);
	bulletBody->SetUserData(bullet);
	bulletBody->SetBullet(true);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox((bullet->getContentSize().width - 5)/2/PTM_RATIO, 
		(bullet->getContentSize().height - 5)/2/PTM_RATIO);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0;
	fixtureDef.restitution = 0;
	fixtureDef.friction = 0;
	fixtureDef.filter.groupIndex = 3;

	bulletBody->CreateFixture(&fixtureDef);
	bulletBody->SetFixedRotation(true);
	float ration = CC_DEGREES_TO_RADIANS(angle);
	bulletBody->SetTransform(bulletBody->GetPosition(), ration);
	bulletBody->SetLinearVelocity(b2Vec2((float)vec*cos(ration), (float)vec*sin(ration)));
	layer->bullets.push_back(bulletBody);
	if (bullet_type == 5)
		bulletBody->SetAngularVelocity(0.8f);
	if(shutPos == shutPoint1)
		showShut(layer, 1);
	else
		showShut(layer, 2);
}

DiJiSprite* DiJiSprite::create(int type)
{
	DiJiSprite* diji = DiJiSprite::createWithSpriteFrameName("diji_"+Tool::toString(type)+".png");
	return diji;
}

DiJiSprite* DiJiSprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != nullptr, msg);
#endif

	return createWithSpriteFrame(frame);
}
DiJiSprite* DiJiSprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	DiJiSprite *sprite = new (std::nothrow) DiJiSprite();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
