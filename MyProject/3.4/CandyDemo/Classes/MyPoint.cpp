#include "MyPoint.h"
#include "Perf.h"


MyPoint::MyPoint()
{

}
MyPoint::MyPoint(int _x, int _y)
{
	world_x = _x;
	world_y = _y;
	true_x = zero_point.x + world_x*TILED_WIDTH+TILED_WIDTH/2;
	true_y = zero_point.y + world_y*TILED_HEIGHT+TILED_HEIGHT/2;
}
void MyPoint::set_world_point(int _x, int _y)
{
	world_x = _x;
	world_y = _y;
	true_x = zero_point.x + world_x*TILED_WIDTH+TILED_WIDTH/2;
	true_y = zero_point.y + world_y*TILED_HEIGHT+TILED_HEIGHT/2;
}

void MyPoint::set_world_point(MyPoint p)
{
	set_world_point(p.world_x, p.world_y);
}


Point MyPoint::get_true_point()
{
	return Point(true_x, true_y);
}

const bool MyPoint::operator==(const MyPoint& p)
{
	if(world_x == p.world_x && world_y == p.world_y)
		return true;
	else
		return false;
}