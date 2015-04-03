#ifndef _MYPOINT_
#define _MYPOINT_

#include "cocos2d.h"

using namespace cocos2d;
class MyPoint
{
public:
	MyPoint();
	MyPoint(int _x, int _y);
	void set_world_point(int _x, int _y);
	void set_world_point(MyPoint& p);
	const bool operator==(const MyPoint& p);
	Point get_true_point();
public:
	int world_x;
	int world_y;
	float true_x;
	float true_y;
};
#endif // !_MYPOINT_
