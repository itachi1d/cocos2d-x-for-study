#include "MyContactFilter.h"


bool MyContactFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
{
	const b2Filter& filterA = fixtureA->GetFilterData();
	const b2Filter& filterB = fixtureB->GetFilterData();
	int a = filterA.groupIndex;
	int b = filterB.groupIndex;
	if(a == b)
		return false;
	if ((a == 2 && b == 1) || (a == 1 && b == 2)
		||(a == 2 && b == -2) || (a == -2 && b == 2)
		||(a == 1 && b == -1) || (a == -1 && b == 1)
		||(a == 1 && b == 3) || (a == 3 && b == 1)
		||(a == 4 && b == 1) || (a == 1 && b == 4)
		||(a == 4 && b == -2) || (a == -2 && b == 4))
	{
		return true;
	}
	else
		return false;
	if((a == -2 && b == 1) | (a == 1 && b == -2))
		return false;
	else if((a == -2 && b == -1) | (a == -1 && b == -2))
		return false;
	else if((a == 2 && b == -1) | (a == -1 && b == 2))
		return false;
	else if((a == -2 && b == 3) | (a == 3 && b == -2))
		return false;
	else if((a == -1 && b == 3) | (a == 3 && b == -1))
		return false;
	else if((a == 2 && b == 3) | (a == 3 && b == 2))
		return false;
	return true;
}