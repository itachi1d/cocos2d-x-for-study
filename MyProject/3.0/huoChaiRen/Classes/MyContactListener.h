#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;
class MyContactListener: public b2ContactListener
{

public:

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	  {
		
	  }
	void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
	  {
		
	  }
	void jieChuDiMian(){}

	void contactBeginLu(b2Contact* contact);
	void contactEndLu(b2Contact* contact);
	void contactBeginCi(b2Contact* contact);
	void contactEndCi(b2Contact* contact);
	void contactBeginJumpLu(b2Contact* contact);
};