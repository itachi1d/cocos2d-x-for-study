#include "PlayerSprite.h"
#include "GameScene.h"
#include "Manager.h"
#include "DiJiSprite.h"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;

void PlayerSprite::dead()
{
	isDead = true;
	this->setVisible(false);
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	layer->showBoomParticle(this->getPosition(), 3);//²¥·Å±¬Õ¨ÌØÐ§
	layer->removeListener();//Í£Ö¹´¥ÃþÊÂ¼þ
	layer->stopShutBullet();//Í£Ö¹Éä»÷×Óµ¯
	layer->getPlayerBody()->SetLinearVelocity(b2Vec2(0, 0));
	//layer->getPlayerBody()->SetTransform(b2Vec2(320/PTM_RATIO, 500/PTM_RATIO), layer->getPlayerBody()->GetAngle());
}

bool PlayerSprite::fuHuo()
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	return layer->fuHuo();
}

b2Body* PlayerSprite::getBody()
{
	return body;
}
void PlayerSprite::setBody(b2Body* _body)
{
	body = _body;
}
void PlayerSprite::OnWuDi()
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	Animation *animation = Animation::createWithSpriteFrames(layer->wudis, 0.03f);
	animation->setLoops(-1);
	Animate *anim = Animate::create(animation);
	anim->setTag(1);
	this->runAction(anim);
}

void PlayerSprite::OffWuDi()
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	this->stopActionByTag(1);
	this->setTextureRect(layer->playerRect);
}

void PlayerSprite::max_open(float dt)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	max_time+=dt;
	if(max_time >= 0.6f)
	{
		layer->getChildByTag(102)->removeFromParentAndCleanup(true);
		switch (bulletType)
		{
		case 0:
			max1(dt);
			break;
		case 1:
			max2(dt);
			break;
		case 2:
			max3(dt);
			break;
		default:
			break;
		}	
	}
}
void PlayerSprite::max1(float dt)
{

}
void PlayerSprite::max2(float dt)
{

}
void PlayerSprite::max3(float dt)
{
	
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	if(isSoundOpen)
		maxing_sound_id = SimpleAudioEngine::getInstance()->playEffect(maxing1_sound.c_str(), true);
	layer->scheduleUpdate();
	Sprite* sprite = Sprite::createWithSpriteFrameName("MAX1_1.png");
	layer->addChild(sprite, layer->getPlayer()->getZOrder()-1);
	sprite->setPosition(layer->getPlayer()->getPosition());
	sprite->setScaleY(3);
	sprite->setScaleX(1.5);
	sprite->setTag(101);
	sprite->setAnchorPoint(Point(0.5, 0.08));
	Animation *animation1 = Animation::createWithSpriteFrames(Manager::Instance()->max1_start, 0.05f, 1);
	Animate* anima1 = Animate::create(animation1);
	Animation *animation2 = Animation::createWithSpriteFrames(Manager::Instance()->max1_content, 0.03f, 16);
	Animate* anima2 = Animate::create(animation2);
	Animation *animation3 = Animation::createWithSpriteFrames(Manager::Instance()->max1_end, 0.05f, 1);
	Animate* anima3 = Animate::create(animation3);
	FiniteTimeAction * actionOne = Sequence::create(
		anima1,
		anima2,
		anima3,
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(PlayerSprite::maxAnima_finish)),NULL);
	sprite->runAction(actionOne);
	actionOne->setTag(11);
	layer->unschedule(schedule_selector(PlayerSprite::max_open, this));
	max_time = 0;
	layer->schedule(schedule_selector(PlayerSprite::maxAnima_content, layer->player));
	layer->schedule(schedule_selector(GameScene::douDong));
}
void PlayerSprite::maxAnima_content(float dt)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	if(layer->isFuHuoing)
	{
		if(isSoundOpen)
		{
			SimpleAudioEngine::getInstance()->stopEffect(maxing_sound_id);
			layer->schedule(schedule_selector(GameScene::resumeBGmusic));
		}
		layer->stopDouDong();
		layer->unschedule(schedule_selector(PlayerSprite::maxAnima_content));
		layer->getPlayer()->stopActionByTag(11);
		layer->getPlayer()->maxAnima_finish();

	}
	if(layer->getChildByTag(101))
	{
		Sprite* sprite = (Sprite*)layer->getChildByTag(101);
		sprite->setPosition(layer->getPlayer()->getPosition());
		max_time += dt;
		if(max_time < 3)
		{	
			PlayerSprite* player = layer->getPlayer();
			Rect rect = Rect(player->getPositionX()-150, player->getPositionY()+50, 300, 960-50-player->getPositionY());
			std::list<b2Body*>::iterator itr;
			for(itr = layer->diJis.begin(); itr != layer->diJis.end(); )
			{
				b2Body* dijiBody = ((b2Body*)*itr);
				DiJiSprite* diji = (DiJiSprite*)(dijiBody->GetUserData());
				if(rect.containsPoint(diji->getPosition()))
				{
					if(diji->life > 0)
					{
						diji->life -= (float)MAX_DAMEGE1*dt;
						diji->beAttackAction();
						++itr;
					}
					else
					{
						if(!diji->isBoom)
						{
							diji->isBoom = true;
							if(isSoundOpen)
								SimpleAudioEngine::getInstance()->playEffect(boom_sound.c_str());
							itr = layer->diJis.erase(itr);
							layer->deleteDiJis.push_back(dijiBody);
						}
					}
				}else
					++itr;
			}
		}		
	}
	else
		layer->unschedule(schedule_selector(PlayerSprite::maxAnima_content));
}
void PlayerSprite::maxAnima_finish()
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->stopEffect(maxing_sound_id);
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	layer->getChildByTag(101)->removeFromParentAndCleanup(true);
	layer->schedule(schedule_selector(GameScene::resumeBGmusic));
	layer->stopDouDong();
	max_time = 0;
}
