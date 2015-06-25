#include "Boss.h"
#include "Tool.h"
#include "GameScene.h"

Boss::Boss():move_time(0), stand_time(0), need_move_time(0), begin(false), mode_cout_time(0), 
	whole_mode_time(0), shut_once_cout_time(0), flag(true),shut_once_cout_time_more(0)
{

}

Boss * Boss::create(int _guanqia)
{
	
	Boss* boss;
	switch (_guanqia)
	{
	case 1:
		boss = Boss::createWithSpriteFrameName("BOSS_1.png");
		boss->shut_points.push_back(Point(-30, 40));
		boss->shut_points.push_back(Point(30, 40));
		boss->shut_points.push_back(Point(-30, -70));
		boss->shut_points.push_back(Point(30, -70));
		boss->mode_cout = 5;
		boss->life = 60000;
		boss->max_life = boss->life;
		boss->width = 80;
		boss->height = 100;
		boss->shut_mode = rand()%3;
		boss->setModeTime();	
		break;
	case 2:
		boss = Boss::createWithSpriteFrameName("BOSS_2.png");
		boss->shut_points.push_back(Point(0, 0));
		boss->shut_points.push_back(Point(-18, -80));
		boss->shut_points.push_back(Point(18, -80));
		boss->mode_cout = 5;
		boss->life = 60000;
		boss->max_life = boss->life;
		boss->width = 70;
		boss->height = 50;
		boss->shut_mode = rand()%4;
		boss->setModeTime();
		break;
	case 3:
		boss = Boss::createWithSpriteFrameName("BOSS_3.png");
		boss->shut_points.push_back(Point(80, 0));
		boss->shut_points.push_back(Point(-80, 0));
		boss->shut_points.push_back(Point(-40, -220));
		boss->shut_points.push_back(Point(40, -220));
		boss->mode_cout = 5;
		boss->life = 60000;
		boss->max_life = boss->life;
		boss->width = 90;
		boss->height = 20;
		boss->shut_mode = rand()%4;
		boss->setModeTime();
		break;
	case 4:
		boss = Boss::createWithSpriteFrameName("BOSS_4.png");
		boss->shut_points.push_back(Point(0, 0));
		boss->mode_cout = 5;
		boss->life = 60000;
		boss->max_life = boss->life;
		boss->width = 60;
		boss->height = 60;
		boss->shut_mode = rand()%3;
		boss->setModeTime();
		break;
	default:
		break;
	}
	boss->move_points.push_back(Point(320, 750));
	boss->move_points.push_back(Point(180, 700));
	boss->move_points.push_back(Point(460, 700));
	boss->move_points.push_back(Point(320, 850));
	boss->next_move = boss->move_points.at(rand()%boss->move_points.size());
	return boss;
}
Boss* Boss::createWithSpriteFrameName(const std::string& spriteFrameName)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != nullptr, msg);
#endif

	return createWithSpriteFrame(frame);
}
Boss* Boss::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	Boss *sprite = new (std::nothrow) Boss();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Boss::changeMode()
{

}

void Boss::shutBullet(float dt, int _guanqia)
{
	switch (_guanqia)
	{
	case 1:
		shutBullet_1(dt);
		break;
	case 2:
		shutBullet_2(dt);
		break;
	case 3:
		shutBullet_3(dt);
		break;
	case 4:
		shutBullet_4(dt);
		break;
	default:
		break;
	}
}

void Boss::boom()
{

}

void Boss::shutBullet_1(float dt)
{
	auto scene = Director::getInstance()->getRunningScene();
	GameScene* layer = (GameScene*)scene->getChildByTag(0);

	switch (shut_mode)
	{
	case 0:
		{
			mode_cout_time += dt;
			shut_once_cout_time += dt;
			if(mode_cout_time > whole_mode_time)
				resetMode(3);
			if(shut_once_cout_time > shut_once_time)
			{
				if (mode_cout_time < 1.6f)
				{
					shut_once_cout_time = 0;
					//float angle = (layer->getPlayer()->getPosition() - this->getPosition()).getAngle();
					createBullet(this->getPosition()+shut_points.at(0), 0, angle1, DIJI_BULLET_SPEED_TYPE_1);
					angle1 += 4;
					createBullet(this->getPosition()+shut_points.at(1), 0, angle2, DIJI_BULLET_SPEED_TYPE_1);
					angle2 -= 4;
				}
				else if(mode_cout_time > 2.6f)
				{
					float ration = (layer->getPlayer()->getPosition() - this->getPosition()).getAngle();
					float angle = CC_RADIANS_TO_DEGREES(ration);
					createBullet(this->getPosition()+shut_points.at(0), 7, (angle-10)+rand()%20, DIJI_BULLET_SPEED_TYPE_4);
					createBullet(this->getPosition()+shut_points.at(1), 7, (angle-10)+rand()%20, DIJI_BULLET_SPEED_TYPE_4);
				}
				
			}

		}		
		break;
	case 1:
		mode_cout_time += dt;
		shut_once_cout_time += dt;
		if(mode_cout_time > whole_mode_time)
			resetMode(3);
		if(shut_once_cout_time > shut_once_time)
		{
			float angle = 0;
			shut_once_cout_time = 0;
			for (int i = 0; i < 36; ++i)
			{
				createBullet(this->getPosition()+shut_points.at(2), 5, angle, DIJI_BULLET_SPEED_TYPE_1);
				createBullet(this->getPosition()+shut_points.at(3), 5, angle, DIJI_BULLET_SPEED_TYPE_1);
				angle += 10;
			}
		}
		break;
	case 2:
		{
			mode_cout_time += dt;
			shut_once_cout_time += dt;
			if(mode_cout_time > whole_mode_time)
				resetMode(3);
			if(shut_once_cout_time > shut_once_time)
			{
				float angle = 270;
				shut_once_cout_time = 0;
				createBullet(this->getPosition()+shut_points.at(0), 2, angle - 15, DIJI_BULLET_SPEED_TYPE_2);
				createBullet(this->getPosition()+shut_points.at(1), 2, angle + 15, DIJI_BULLET_SPEED_TYPE_2);
				createBullet(this->getPosition()+shut_points.at(2), 2, angle, DIJI_BULLET_SPEED_TYPE_2);
				createBullet(this->getPosition()+shut_points.at(3), 2, angle, DIJI_BULLET_SPEED_TYPE_2);
			}
		}
		break;
	default:
		break;
	}
}
void Boss::shutBullet_2(float dt)
{
	auto scene = Director::getInstance()->getRunningScene();
	GameScene* layer = (GameScene*)scene->getChildByTag(0);
	switch (shut_mode)
	{
	case 0:
		{
			mode_cout_time += dt;
			shut_once_cout_time += dt;
			if(mode_cout_time > whole_mode_time)
				resetMode(4);
			if(shut_once_cout_time > shut_once_time && mode_cout_time > 0.3f)
			{
				float ration = (layer->getPlayer()->getPosition() - this->getPosition()).getAngle();
				float angle = CC_RADIANS_TO_DEGREES(ration);
				shut_once_cout_time = 0;
				createBullet(this->getPosition()+shut_points.at(0), 3, angle, DIJI_BULLET_SPEED_TYPE_4);
				createBullet(this->getPosition()+shut_points.at(1), 4, angle1, DIJI_BULLET_SPEED_TYPE_2);
				createBullet(this->getPosition()+shut_points.at(2), 4, angle2, DIJI_BULLET_SPEED_TYPE_2);
				if(flag)
					angle1 += 5;
				else
					angle1 -= 5;				
				if(flag)
					angle2 -= 5;
				else
					angle2 += 5;
				if(angle1 >= 330)
					flag = false;
				else if(angle1 <= 210)
					flag = true;
			}
		}
		break;
	case 1:
		{
			mode_cout_time += dt;
			shut_once_cout_time += dt;
			if(mode_cout_time > whole_mode_time)
				resetMode(4);
			if(shut_once_cout_time > shut_once_time)
			{
				shut_once_cout_time = 0;
				float ration = (layer->getPlayer()->getPosition() - this->getPosition()).getAngle();
				float angle = CC_RADIANS_TO_DEGREES(ration);
				float angle_1 = 210+rand()%60;
				float angle_2 = 280+rand()%60;
				createBullet(this->getPosition()+shut_points.at(1), 0, angle_1, DIJI_BULLET_SPEED_TYPE_1);
				createBullet(this->getPosition()+shut_points.at(2), 0, angle_2, DIJI_BULLET_SPEED_TYPE_1);
				flag = !flag;
				if(mode_cout_time > 2.5f && flag)
					createBullet(this->getPosition()+shut_points.at(0), 1, angle, DIJI_BULLET_SPEED_TYPE_6);
			}
		}
		break;
	case 2:
		{
			mode_cout_time += dt;
			shut_once_cout_time += dt;
			if(mode_cout_time > whole_mode_time)
				resetMode(4);
			if(shut_once_cout_time > shut_once_time && mode_cout_time > 0.3f)
			{
				shut_once_cout_time = 0;
				float ration = (layer->getPlayer()->getPosition() - this->getPosition()).getAngle();
				float angle = CC_RADIANS_TO_DEGREES(ration);
				createBullet(this->getPosition()+shut_points.at(0), 1, angle, DIJI_BULLET_SPEED_TYPE_2);
				if (mode_cout_time > 1.0f)
				{
					createBullet(this->getPosition()+shut_points.at(1), 0, angle - 5, DIJI_BULLET_SPEED_TYPE_7);
					createBullet(this->getPosition()+shut_points.at(2), 0, angle + 5, DIJI_BULLET_SPEED_TYPE_7);
				}
			}
		}
		break;
	case 3:
		{
			mode_cout_time += dt;
			shut_once_cout_time += dt;
			if(mode_cout_time > whole_mode_time)
				resetMode(4);
			if(shut_once_cout_time > shut_once_time && mode_cout_time > 0.5f)
			{
				shut_once_cout_time = 0;
				float ration = (layer->getPlayer()->getPosition() - this->getPosition()).getAngle();
				float angle = CC_RADIANS_TO_DEGREES(ration);
				createBullet(this->getPosition()+shut_points.at(1), 0, angle - 3, DIJI_BULLET_SPEED_TYPE_8);
				createBullet(this->getPosition()+shut_points.at(1), 0, angle - 8, DIJI_BULLET_SPEED_TYPE_8);
				createBullet(this->getPosition()+shut_points.at(2), 0, angle + 3, DIJI_BULLET_SPEED_TYPE_8);
				createBullet(this->getPosition()+shut_points.at(2), 0, angle + 8, DIJI_BULLET_SPEED_TYPE_8);
			}
		}
		break;
	default:
		break;
	}
}
void Boss::shutBullet_3(float dt)
{
	auto scene = Director::getInstance()->getRunningScene();
	GameScene* layer = (GameScene*)scene->getChildByTag(0);
	switch (shut_mode)
	{
	case 0:
		mode_cout_time += dt;
		shut_once_cout_time += dt;
		if(mode_cout_time > whole_mode_time)
			resetMode(4);
		if(shut_once_cout_time > shut_once_time && mode_cout_time > 0.5f)
		{
			shut_once_cout_time = 0;
			float angle = 270;
			createBullet(this->getPosition()+shut_points.at(0), 2, angle, DIJI_BULLET_SPEED_TYPE_7);
			createBullet(this->getPosition()+shut_points.at(1), 2, angle, DIJI_BULLET_SPEED_TYPE_7);
			createBullet(this->getPosition()+shut_points.at(2), 4, angle, DIJI_BULLET_SPEED_TYPE_7);
			createBullet(this->getPosition()+shut_points.at(3), 4, angle, DIJI_BULLET_SPEED_TYPE_7);
		}
		break;
	case 1:
		mode_cout_time += dt;
		shut_once_cout_time += dt;
		if(mode_cout_time > whole_mode_time)
			resetMode(4);
		if(shut_once_cout_time > shut_once_time && mode_cout_time > 0.1f && mode_cout_time < 5.0f)
		{
			shut_once_cout_time = 0;
			float angle = 200;
			createBullet(this->getPosition()+shut_points.at(0), 0, angle+rand()%140, DIJI_BULLET_SPEED_TYPE_1);
			createBullet(this->getPosition()+shut_points.at(1), 0, angle+rand()%140, DIJI_BULLET_SPEED_TYPE_1);
			createBullet(this->getPosition()+shut_points.at(2), 0, angle+rand()%140, DIJI_BULLET_SPEED_TYPE_1);
			createBullet(this->getPosition()+shut_points.at(3), 0, angle+rand()%140, DIJI_BULLET_SPEED_TYPE_1);
		}
		break;
	case 2:
		mode_cout_time += dt;
		shut_once_cout_time += dt;
		if(mode_cout_time > whole_mode_time)
			resetMode(4);
		if(shut_once_cout_time > shut_once_time && mode_cout_time > 0.5f)
		{
			shut_once_cout_time = 0;
			Point playerPoint = layer->getPlayer()->getPosition();
			createBullet(this->getPosition()+shut_points.at(0), 2, getAngleforPointToPoint(shut_points.at(0), playerPoint)-15, DIJI_BULLET_SPEED_TYPE_7);
			createBullet(this->getPosition()+shut_points.at(1), 2, getAngleforPointToPoint(shut_points.at(1), playerPoint)+15, DIJI_BULLET_SPEED_TYPE_7);
			flag = !flag;
			if(flag)
			{
				createBullet(this->getPosition()+shut_points.at(2), 0, getAngleforPointToPoint(shut_points.at(2), playerPoint), DIJI_BULLET_SPEED_TYPE_2);
				createBullet(this->getPosition()+shut_points.at(3), 0, getAngleforPointToPoint(shut_points.at(3), playerPoint), DIJI_BULLET_SPEED_TYPE_2);
		
			}
		}
		break;
	case 3:
		mode_cout_time += dt;
		shut_once_cout_time += dt;
		if(mode_cout_time > whole_mode_time)
			resetMode(4);
		if(shut_once_cout_time > shut_once_time && mode_cout_time > 0.5f && mode_cout_time < 3.5f)
		{
			shut_once_cout_time = 0;
			float angle = 210;
			for (int i = 0; i < 7; ++i)
			{
				createBullet(this->getPosition()+shut_points.at(0), 2, angle, DIJI_BULLET_SPEED_TYPE_0);
				createBullet(this->getPosition()+shut_points.at(1), 2, angle, DIJI_BULLET_SPEED_TYPE_0);
				createBullet(this->getPosition()+shut_points.at(2), 4, angle, DIJI_BULLET_SPEED_TYPE_0);
				createBullet(this->getPosition()+shut_points.at(3), 4, angle, DIJI_BULLET_SPEED_TYPE_0);
				angle += 18;
			}
			
		}
		break;
	default:
		break;
	}
}
void Boss::shutBullet_4(float dt)
{
	auto scene = Director::getInstance()->getRunningScene();
	GameScene* layer = (GameScene*)scene->getChildByTag(0);
	switch (shut_mode)
	{
	case 0:
		{
			mode_cout_time += dt;
			shut_once_cout_time += dt;
			shut_once_cout_time_more += dt;
			if(mode_cout_time > whole_mode_time)
				resetMode(3);
			if(shut_once_cout_time > shut_once_time && mode_cout_time > 0.5f && mode_cout_time < 17.0f)
			{
				shut_once_cout_time = 0;
				createBullet(this->getPosition()+shut_points.at(0), 5, -1*this->getRotation(), DIJI_BULLET_SPEED_TYPE_0);
			}
			if (shut_once_cout_time_more > DIJI_BULLET_ONCE_TIME_1 && mode_cout_time > 5.0f)
			{
				shut_once_cout_time_more = 0;
				float ration = (layer->getPlayer()->getPosition() - this->getPosition()).getAngle();
				float angle = CC_RADIANS_TO_DEGREES(ration);
				createBullet(this->getPosition()+shut_points.at(0), 1, angle, DIJI_BULLET_SPEED_TYPE_5);
				createBullet(this->getPosition()+shut_points.at(0), 1, angle + 3, DIJI_BULLET_SPEED_TYPE_5);
				createBullet(this->getPosition()+shut_points.at(0), 1, angle - 3, DIJI_BULLET_SPEED_TYPE_5);
			}
		}
		break;
	case 1:
		{
			mode_cout_time += dt;
			shut_once_cout_time += dt;
			if(mode_cout_time > whole_mode_time)
				resetMode(3);
			if(shut_once_cout_time > shut_once_time && mode_cout_time > 0.5f && mode_cout_time < 3.5f)
			{
				shut_once_cout_time = 0;
				float angle;
				if(flag)
					angle = angle1;
				else
					angle = angle2;
				flag = !flag;
				for (int i = angle; i < 360+angle; i += 5)
				{
					createBullet(this->getPosition()+shut_points.at(0), 7, i, DIJI_BULLET_SPEED_TYPE_3);
				}
			}
		}
		break;
	case 2:
		{
			mode_cout_time += dt;
			shut_once_cout_time += dt;
			if(mode_cout_time > whole_mode_time)
				resetMode(3);
			if(shut_once_cout_time > shut_once_time && mode_cout_time > 1.0f && mode_cout_time < 7.0f)
			{
				shut_once_cout_time = 0;
				float angle = 210;
				createBullet(this->getPosition()+shut_points.at(0), rand()%8, angle + rand()%120, 2+rand()%25);
				createBullet(this->getPosition()+shut_points.at(0), rand()%8, angle + rand()%120, 2+rand()%25);
			}
		}
		break;
	default:
		break;
	}
}

void Boss::beAttackAction()
{
	if(this->getColor() != Color3B::RED)
	{
		color = this->getColor();
		this->setColor(Color3B::RED);
		scheduleOnce(schedule_selector(Boss::beComeColor), 0.2f);
	}
}

void Boss::beComeColor(float time)
{
	this->setColor(color);
}

float Boss::getMaxLife()
{
	return max_life;
}

float Boss::subLife(float cout)
{
	this->life = this->life - cout;
	if(life < 0)
		life = 0;
	return life;
}

float Boss::getLife()
{
	return life;
}

void Boss::createBullet(Point shutPos, int bullet_type, float angle, float vec)
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
}

void Boss::setModeTime()
{
	angle1 = 210;
	angle2 = 330;
	switch (guanqia)
	{
	case 1:
		switch (shut_mode)
		{
		case 0:
			whole_mode_time = 3;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_6;
			angle1 = 210;
			angle2 = 330;
			break;
		case 1:
			whole_mode_time = 3;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_1;
			angle1 = 210;
			angle2 = 330;
			break;
		case 2:
			whole_mode_time = 2;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_6;
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (shut_mode)
		{
		case 0:
			whole_mode_time = 3;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_6;
			break;
		case 1:
			whole_mode_time = 3;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_4;
			break;
		case 2:
			whole_mode_time = 2;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_6;
			break;
		case 3:
			whole_mode_time = 2;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_4;
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (shut_mode)
		{
		case 0:
			whole_mode_time = 3;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_4;
			break;
		case 1:
			whole_mode_time = 6;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_4;
			break;
		case 2:
			whole_mode_time = 5;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_4;
			break;
		case 3:
			whole_mode_time = 10;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_5;
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (shut_mode)
		{
		case 0:
			whole_mode_time = 20;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_7;
			break;
		case 1:
			whole_mode_time = 5;
			angle1 = 0;
			angle2 = 2;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_2;
			break;
		case 2:
			whole_mode_time = 8;
			shut_once_time = (float)DIJI_BULLET_ONCE_TIME_7;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
}

void Boss::resetMode(int maxMode)
{
	mode_cout_time = 0;
	shut_once_cout_time = 0;
	shut_once_cout_time_more = 0;
	shut_mode = rand()%maxMode;
	setModeTime();
	flag = true;
}

float Boss::getAngleforPointToPoint(Point ShutPoint, Point playerPoint)
{
	return CC_RADIANS_TO_DEGREES((playerPoint - (this->getPosition()+ShutPoint)).getAngle());
}


