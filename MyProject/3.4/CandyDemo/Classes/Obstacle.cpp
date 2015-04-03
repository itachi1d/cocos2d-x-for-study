#include "Obstacle.h"
#include "Perf.h"

Obstacle::Obstacle(){}

Obstacle* Obstacle::create(MyPoint point)
{
	return createWithSpriteFrameName(Obstacle_name, point);
}

Obstacle* Obstacle::createWithSpriteFrameName(const std::string& spriteFrameName, MyPoint point)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != nullptr, msg);
#endif

	return createWithSpriteFrame(frame, point);
}
Obstacle* Obstacle::createWithSpriteFrame(SpriteFrame *spriteFrame, MyPoint point)
{
	Obstacle *sprite = new (std::nothrow) Obstacle();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		sprite->set_world_point(point.world_x, point.world_y);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Obstacle::set_world_point(int _x, int _y)
{
	world_point.set_world_point(_x, _y);
	this->setPosition(world_point.true_x, world_point.true_y);
}

