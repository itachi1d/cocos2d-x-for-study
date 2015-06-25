#ifndef _MYFILTER_
#define _MYFILTER_
#include "cocos2d.h"
#include <Box2D\Box2D.h>
USING_NS_CC;

class MyContactFilter: public b2ContactFilter
{
public:
	bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);
};

#endif