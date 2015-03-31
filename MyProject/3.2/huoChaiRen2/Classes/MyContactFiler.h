#include "cocos2d.h"
#include <Box2D\Box2D.h>

class MyContactFiler: public b2ContactFilter
{
public:
	bool ShouldCollide(b2Fixture* fixtureA, b2Fixture *fixtureB);
};