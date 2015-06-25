#include "PlayerSprite.h"
#include "GameScene.h"
#include "Manager.h"
#include "DiJiSprite.h"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;

PlayerSprite* PlayerSprite::create(int type)
{
	PlayerSprite* plane;
	switch (type)
	{
	case 0:
		plane =  PlayerSprite::createWithSpriteFrameName("A_player01_1.png");
		break;
	case 1:
		plane =  PlayerSprite::createWithSpriteFrameName("A_player02_1.png");
		break;
	case 2:
		plane =  PlayerSprite::createWithSpriteFrameName("A_player03_1.png");
		break;
	default:
		break;
	}
	return plane;
}

PlayerSprite* PlayerSprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != nullptr, msg);
#endif

	return createWithSpriteFrame(frame);
}
PlayerSprite* PlayerSprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	PlayerSprite *sprite = new (std::nothrow) PlayerSprite();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void PlayerSprite::dead()
{
	isDead = true;
	this->setVisible(false);
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	bulletLevel --;
	if (bulletLevel < 0)
		bulletLevel = 0;
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
	Action *action = RepeatForever::create(Sequence::create(FadeIn::create(0.1f), FadeOut::create(0.1f), nullptr));
	action->setTag(1);
	this->runAction(action);
}

void PlayerSprite::OffWuDi()
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	this->stopActionByTag(1);
	this->setOpacity(255);
}

void PlayerSprite::max_open(float dt)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	max_time+=dt;
	if(max_time >= 0.6f)
	{
		//layer->getChildByTag(102)->removeFromParentAndCleanup(true);
		switch (bulletType)
		{
		case 0:
			max3(dt);
			//max1(dt);
			break;
		case 1:
			max3(dt);
			//max2(dt);
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
	if(layer->isFuHuoing || layer->getPlayer()->isDead)
	{
		if(isSoundOpen)
		{
			SimpleAudioEngine::getInstance()->stopEffect(maxing_sound_id);
			layer->schedule(schedule_selector(GameScene::resumeBGmusic));
		}
		return;
	}
	if(isSoundOpen)
		maxing_sound_id = SimpleAudioEngine::getInstance()->playEffect(maxing1_sound.c_str());
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
	Animation *animation2 = Animation::createWithSpriteFrames(Manager::Instance()->max1_content, 0.03f, 13);
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
	this->unschedule(schedule_selector(PlayerSprite::max_open));
	max_time = 0;
	this->schedule(schedule_selector(PlayerSprite::maxAnima_content));
	layer->schedule(schedule_selector(GameScene::douDong));
}
void PlayerSprite::maxAnima_content(float dt)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	if(layer->isFuHuoing || layer->getPlayer()->isDead)
	{
		if(isSoundOpen)
		{
			SimpleAudioEngine::getInstance()->stopEffect(maxing_sound_id);
			layer->schedule(schedule_selector(GameScene::resumeBGmusic));
		}
		layer->stopDouDong();
		this->unschedule(schedule_selector(PlayerSprite::maxAnima_content));
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
			if(layer->bossUpdate->getBossBody())
			{
				Boss* boss = layer->bossUpdate->boss;
				if (boss->getLife() > 0)
				{
					Rect bossRect = Rect(boss->getPositionX() - boss->width/2, boss->getPositionY() - boss->height/2
						, boss->width, boss->height);
					if(rect.intersectsRect(bossRect))
					{
						boss->subLife((float)MAX_DAMEGE1*dt);
						layer->bossUpdate->updateXueTiao();
					}
				}
			}
			
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
		this->unschedule(schedule_selector(PlayerSprite::maxAnima_content));
}
void PlayerSprite::maxAnima_finish()
{
	if(isSoundOpen)
		SimpleAudioEngine::getInstance()->stopEffect(maxing_sound_id);
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	if (layer->getPlayer()->getActionByTag(11))
		layer->getPlayer()->stopActionByTag(11);
	layer->getChildByTag(101)->removeFromParentAndCleanup(true);
	layer->schedule(schedule_selector(GameScene::resumeBGmusic));
	layer->stopDouDong();
	layer->max_button->setEnabled(true);
	layer->max_button->setBright(true);
	max_time = 0;
}


