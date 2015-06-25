#include "Myb2RayCastCallback.h"
#include "JGbullet.h"

float32 Myb2RayCastCallback::ReportFixture(	b2Fixture* fixture, const b2Vec2& point,
									const b2Vec2& normal, float32 fraction)
{
	_fixture = fixture;
	_point = point;
	_normal = normal;
	if(_fixture->GetFilterData().groupIndex == -2)
		return -1;
	if(_fixture->GetFilterData().groupIndex == 2 || _fixture->GetFilterData().groupIndex == -1 || _fixture->GetFilterData().groupIndex == 4)
		_fraction = fraction;
	else
		_fraction = 1;

	return _fraction;
}
	