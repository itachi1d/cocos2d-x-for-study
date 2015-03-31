#include "MyContactFiler.h"

bool MyContactFiler::ShouldCollide(b2Fixture* fixtureA, b2Fixture *fixtureB)
{
	const b2Filter& filterA = fixtureA->GetFilterData();
	const b2Filter& filterB = fixtureB->GetFilterData();
	int a = filterA.groupIndex;
	int b = filterB.groupIndex;
	if(a == b)
		return false;
	if((a == -2 && b == -1) || (a == -1 && b == -2))
		return false;
	return true;
}