#include "BulletSprite.h"
#include "Tool.h"

void BulletSprite::setATK(float _atk)
{
	ATK = _atk;
}

void BulletSprite::setType(int _type)
{
	TYPE = _type;
}

BulletSprite* BulletSprite::create(int _type)
{
	return BulletSprite::createWithSpriteFrameName("player_bullet_"+Tool::toString(_type)+".png");
}

BulletSprite* BulletSprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != nullptr, msg);
#endif

	return createWithSpriteFrame(frame);
}

BulletSprite* BulletSprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	BulletSprite *sprite = new (std::nothrow) BulletSprite();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
