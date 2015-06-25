#ifndef _MYB2RAYCAST_
#define _MYB2RAYCAST_
#include "cocos2d.h"
#include <Box2D\Box2D.h>

class Myb2RayCastCallback: public b2RayCastCallback
{
public:
	float32 ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
									const b2Vec2& normal, float32 fraction);
	
	b2Fixture* _fixture;
	b2Vec2 _point;
	b2Vec2 _normal; 
	float32 _fraction;
};
#endif