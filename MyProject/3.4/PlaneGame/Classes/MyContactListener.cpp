#include "MyContactListener.h"
#include "GameScene.h"
#include "DiJiSprite.h"
#include "PlayerSprite.h"


void MyContactListener::BeginContact(b2Contact* contact)
{
	a = contact->GetFixtureA()->GetFilterData().groupIndex;
	b = contact->GetFixtureB()->GetFilterData().groupIndex;
	if((a == 2 && b == -2) | (b == 2 && a == -2))//我方子弹碰到敌机
		atackDiJi(contact);
	if((a == 1 && b == 2) | (b == 1 && a == 2))//敌机碰到主角
		playerContactDiji(contact);
	if((a == 1 && b == 3) | (b == 1 && a == 3))//敌机子弹碰到主角
		playerContactDiji(contact);
}
void MyContactListener::EndContact(b2Contact* contact)
{
	
}
void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	int a = contact->GetFixtureA()->GetFilterData().groupIndex;
	int b = contact->GetFixtureB()->GetFilterData().groupIndex;
	if((a == 1 && b == -1) | (b == 1 && a == -1))
		return;
	else
		contact->SetEnabled(false);
}
void MyContactListener::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse){}

void MyContactListener::atackDiJi(b2Contact* contact)
{
		b2Body *bulletBody;
		b2Body *diJiBody;
		if(a == -2)
		{
			bulletBody = contact->GetFixtureA()->GetBody();
			diJiBody = contact->GetFixtureB()->GetBody();
		}
		else
		{
			bulletBody = contact->GetFixtureB()->GetBody();
			diJiBody = contact->GetFixtureA()->GetBody();
		}
		b2WorldManifold *fold = new b2WorldManifold;
		contact->GetWorldManifold(fold);
		b2Vec2 contactPoint1 =  fold->points[0];
		b2Vec2 contactPoint2 =  fold->points[1];
		Point point = Point(contactPoint1.x*PTM_RATIO, contactPoint1.y*PTM_RATIO);
		fold = 0;
		delete fold;
		BulletSprite *bullet = (BulletSprite*)bulletBody->GetUserData();
		auto *scene = Director::getInstance()->getRunningScene();
		GameScene *layer = (GameScene*)scene->getChildByTag(0);
		layer->subDiJiLife(diJiBody, bulletBody);
		((DiJiSprite*)diJiBody->GetUserData())->beAttackAction();
		if(bullet->TYPE == 0)
		{
			layer->addDeleteBullet(bulletBody);
			layer->showBinGoParticle(point);
		}
		else if(bullet->TYPE == 1)
		{
			layer->showBinGoParticle(point);		
		}

		else if(bullet->TYPE == 2)
		{
			layer->addDeleteBullet(bulletBody);
		}
}

void MyContactListener::playerContactDiji(b2Contact* contact)
{
		b2Body *playerBody;
		b2Body *diJiBody;
		if(a == 1)
		{
			playerBody = contact->GetFixtureA()->GetBody();
			diJiBody = contact->GetFixtureB()->GetBody();
		}
		else
		{
			playerBody = contact->GetFixtureB()->GetBody();
			diJiBody = contact->GetFixtureA()->GetBody();
		}
		PlayerSprite *player = (PlayerSprite*)playerBody->GetUserData();
		BulletSprite *bullet = (BulletSprite*)diJiBody->GetUserData();
		if(!player->isWiDi)
		{
			if(!player->isDead)
				player->dead();
		}
}
