#include "GameScene.h"
#include "MyContactListener.h"
#define PTM_RATIO 32

void MyContactListener::BeginContact(b2Contact* contact)
{
	contactBeginLu(contact);
	contactBeginCi(contact);
	contactBeginJumpLu(contact);
}

void MyContactListener::EndContact(b2Contact* contact)
{
	contactEndLu(contact);
	//contactEndCi(contact);
}

void MyContactListener::contactBeginLu(b2Contact* contact)
{
	int a = contact->GetFixtureA()->GetFilterData().groupIndex;
	int b = contact->GetFixtureB()->GetFilterData().groupIndex;
	if((a == 1 && b == -1) | (b == 1 && a == -1))
	{
		b2Body *hcrBody;
		b2Fixture *luDi;
		if(a == 1)
		{
			hcrBody = contact->GetFixtureA()->GetBody();
			luDi = contact->GetFixtureB();
		}
		else
		{
			hcrBody = contact->GetFixtureB()->GetBody();
			luDi = contact->GetFixtureA();
		}
		b2WorldManifold *fold = new b2WorldManifold;
		contact->GetWorldManifold(fold);
		b2Vec2 contactPoint1 =  fold->points[0];
		b2Vec2 contactPoint2 =  fold->points[1];
		if((contactPoint2.y == contactPoint1.y) && (contactPoint2.x != contactPoint1.x))
		{
			if(contactPoint1.y < hcrBody->GetPosition().y )
			{
				auto *scene = Director::getInstance()->getRunningScene();
				GameScene *layer = (GameScene *)scene->getChildByTag(0);
				layer->contactsWithPlayer.insert(luDi);
				layer->isCanUp = true;
				layer->playState = GameScene::PlayerState::run;
			}
		}
	}
}
void MyContactListener::contactBeginCi(b2Contact* contact)
{
	int a = contact->GetFixtureA()->GetFilterData().groupIndex;
	int b = contact->GetFixtureB()->GetFilterData().groupIndex;
	if((a == 1 && b == -2) | (b == 1 && a == -2))
	{
		auto *scene = Director::getInstance()->getRunningScene();
		GameScene *layer = (GameScene *)scene->getChildByTag(0);
		layer->gameState = GameScene::GameState::end;
	}
}

void MyContactListener::contactEndLu(b2Contact* contact)
{
	int a = contact->GetFixtureA()->GetFilterData().groupIndex;
	int b = contact->GetFixtureB()->GetFilterData().groupIndex;
	if((a == 1 && b == -1) | (b == 1 && a == -1))
	{
		b2Fixture *luDi;
		b2Body *hcrBody;
		if(a == 1)
		{
			luDi = contact->GetFixtureB();
			hcrBody = contact->GetFixtureA()->GetBody();
		}
		else
		{
			luDi = contact->GetFixtureA();
			hcrBody = contact->GetFixtureB()->GetBody();
		}
	
		auto *scene = Director::getInstance()->getRunningScene();
		GameScene *layer = (GameScene *)scene->getChildByTag(0);
		layer->contactsWithPlayer.erase(luDi);
		if(layer->contactsWithPlayer.empty())
			layer->playState = GameScene::PlayerState::jump;
	}
}

void MyContactListener::contactEndCi(b2Contact* contact)
{
	//Àë¿ª´Ì
}

void MyContactListener::contactBeginJumpLu(b2Contact* contact)
{
	int a = contact->GetFixtureA()->GetFilterData().groupIndex;
	int b = contact->GetFixtureB()->GetFilterData().groupIndex;
	if((a == 1 && b == -1) | (b == 1 && a == -1))
	{
		b2Body *hcrBody;
		b2Body *luDi;
		if(a == 1)
		{
			hcrBody = contact->GetFixtureA()->GetBody();
			luDi = contact->GetFixtureB()->GetBody();
		}
		else
		{
			hcrBody = contact->GetFixtureB()->GetBody();
			luDi = contact->GetFixtureA()->GetBody();
		}
		float VeclocityY = hcrBody->GetLinearVelocity().y;
		Sprite *ludi = (Sprite*)luDi->GetUserData();
		if(VeclocityY < -0.07f && ludi->getTag() == 1)
		{
			auto *scene = Director::getInstance()->getRunningScene();
			GameScene *layer = (GameScene *)scene->getChildByTag(0);
			layer->playerHighJump(VeclocityY);
			layer->playState = GameScene::PlayerState::jump;
		}
	}
}