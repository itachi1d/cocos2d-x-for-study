#include "Money.h"

Money::Money(): angle(rand()%360)
{
	float ratation = CC_DEGREES_TO_RADIANS(angle);
	vec_x = 120*sin(ratation);
	vec_y = 120*cos(ratation);
}

Money* Money::createWithSpriteFrameName(const std::string& spriteFrameName)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != nullptr, msg);
#endif

	return createWithSpriteFrame(frame);
}

Money* Money::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	Money *sprite = new (std::nothrow) Money();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Money::updatePosition(float dt)
{
	this->setPositionX(this->getPositionX()+vec_x*dt);
	this->setPositionY(this->getPositionY()+vec_y*dt);
	if(this->getPositionX() < 0)
	{
		vec_x = -vec_x;
		this->setPositionX(0);
	}
	if(this->getPositionX() > 640)
	{
		vec_x = -vec_x;
		this->setPositionX(640);
	}
	if(this->getPositionY() < 0)
	{
		vec_y = -vec_y;
		this->setPositionY(0);
	}
	if(this->getPositionY() > 960)
	{
		vec_y = -vec_y;
		this->setPositionY(960);
	}
}

Money* Money::create(int _type)
{
	Money * money;
	switch (_type)
	{
	case 0:
		money = Money::createWithSpriteFrameName("upPower.png");
		break;
	case 1:
		money = Money::createWithSpriteFrameName("Max_Play_action.png");
		break;
	case 2:
		money = Money::createWithSpriteFrameName("upPower.png");
		break;
	default:
		break;
	}
	money->type = _type;
	return  money;
}
