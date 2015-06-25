#include "Boss_Update.h"
#include "CanShu.h"
#include "GameScene.h"

Boss_Update::Boss_Update():bossBody(nullptr),xuetiao(nullptr)
{

}
Boss_Update::~Boss_Update()
{

}

void Boss_Update::begin_to_boss(float dt)
{
	boss = Boss::create(guanqia);
	boss->setPosition(320, 960+350);
	Scene* scene = Director::getInstance()->getRunningScene();
	GameScene* layer = (GameScene*)scene->getChildByTag(0);
	layer->addChild(boss, 49);
	b2BodyDef bossBodyDef;
	bossBodyDef.type = b2_dynamicBody;
	bossBodyDef.position.Set(320/PTM_RATIO, (960+350)/PTM_RATIO);
	bossBody = layer->getWorld()->CreateBody(&bossBodyDef);
	bossBody->SetUserData(boss);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(boss->width/PTM_RATIO, boss->height/PTM_RATIO);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = 0;
	fixtureDef.restitution = 0;
	fixtureDef.friction = 0;
	fixtureDef.filter.groupIndex = 4;

	bossBody->CreateFixture(&fixtureDef);
	bossBody->SetFixedRotation(true);
	bossBody->SetLinearVelocity(b2Vec2(0, -4));
	this->scheduleOnce(schedule_selector(Boss_Update::first_stop), 4.5f);
	if(guanqia == 4)
		bossBody->SetAngularVelocity(1.5f);
}


void Boss_Update::show_warning()
{
	Sprite* warning = Sprite::createWithSpriteFrameName("Warning.png");
	warning->setPosition(320, 480);
	warning->setOpacity(0);
	auto scene = Director::getInstance()->getRunningScene();
	GameScene* layer = (GameScene*)scene->getChildByTag(0);
	layer->addChild(warning, 150);
	layer->bg_vec = 2;
	warning->runAction(Sequence::create(FadeIn::create(0.5f), FadeOut::create(0.5f),
		FadeIn::create(0.5f), FadeOut::create(0.5f),
		FadeIn::create(0.5f), FadeOut::create(0.5f),
		RemoveSelf::create(true), nullptr));
	this->scheduleOnce(schedule_selector(Boss_Update::begin_to_boss), 4);
}

void Boss_Update::boss_update(float dt, Layer*layer)
{
	Boss* boss = (Boss*)bossBody->GetUserData();
	if(!boss->begin)
		return;
	if (boss->getLife() <= 0)//BOSS死亡
	{
		bossBody->SetAngularVelocity(0);
		bossBody->SetLinearVelocity(b2Vec2(0, 0));
		GameScene* gameLayer = (GameScene*)layer;
		gameLayer->setCancorcarlt(false);
	}
	else
	{
		if (bossBody->GetLinearVelocity().x != 0 || bossBody->GetLinearVelocity().y != 0)
		{
			boss->move_time += dt;
			if (boss->move_time > boss->need_move_time)
			{
				bossBody->SetLinearVelocity(b2Vec2(0, 0));
				boss->need_move_time = 0;
				boss->move_time = 0;
			}
		}
		else
		{
			boss->stand_time += dt;
			if (boss->stand_time > 4)
			{
				boss->stand_time = 0;
				Point nowPoint = boss->next_move;
				boss->next_move = boss->move_points.at(rand()%boss->move_points.size());
				if (nowPoint != boss->next_move)
				{
					float speed = 3+rand()%4;
					float s = (boss->next_move - boss->getPosition()).length();
					float angle = (boss->next_move - boss->getPosition()).getAngle();
					boss->need_move_time = s/(speed*32);
					bossBody->SetLinearVelocity(b2Vec2(speed*cos(angle), speed*sin(angle)));
				}
			}
		}

		boss->shutBullet(dt, guanqia);
		if(guanqia == 4)
		{
			if(boss->shut_mode == 0)
				bossBody->SetAngularVelocity(3.0f);
			else if (boss->shut_mode == 2)
				bossBody->SetAngularVelocity(0.4f);
			else
				bossBody->SetAngularVelocity(1.5f);
		}
	}
}

void Boss_Update::first_stop(float dt)
{
	auto scene = Director::getInstance()->getRunningScene();
	GameScene* layer = (GameScene*)scene->getChildByTag(0);
	bossBody->SetLinearVelocity(b2Vec2(0, 0));
	xuetiao = ProgressTimer::create(Sprite::create("pic/loadingbar.png"));
	xuetiao->setBarChangeRate(Point(1, 0));//设置进度条的变化方向（横）
	xuetiao->setType(ProgressTimer::Type::BAR);
	xuetiao->setMidpoint(Point(0, 0));//设置增长中心 
	xuetiao->setPercentage(100);
	xuetiao->setPosition(320, 960 - 150);
	xuetiao->setScaleX(3);
	xuetiao->setScaleY(2);
	layer->addChild(xuetiao, 150);
	Boss* boss = (Boss*)bossBody->GetUserData();
	boss->begin = true;
}

void Boss_Update::updateXueTiao()
{
	xuetiao->setPercentage(100*((Boss*)bossBody->GetUserData())->getLife()/((Boss*)bossBody->GetUserData())->getMaxLife());
}

b2Body * Boss_Update::getBossBody()
{
	if (bossBody)
		return bossBody;
	return nullptr;
}



