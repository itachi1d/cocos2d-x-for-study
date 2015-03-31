#pragma once
#include "cocos2d.h"
#include "CanShu.h"
#include <Box2D\Box2D.h>
USING_NS_CC;

USING_NS_CC;
class MyContactListener: public b2ContactListener
{

public:

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse);

	void atackDiJi(b2Contact* contact);
	void playerContactDiji(b2Contact* contact);
private:
	int a;
	int b;
};