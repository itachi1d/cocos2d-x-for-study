#ifndef _JGBULLET_
#define _JGBULLET_
#include "cocos2d.h"

USING_NS_CC;

class JGbullet : public Sprite
{
public:
	static JGbullet* createWithTexture(Texture2D *texture, const Rect& rect, bool rotated=false)
	{
		JGbullet *sprite = new JGbullet();
		if (sprite && sprite->initWithTexture(texture, rect, rotated))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	Point location;
	int id;

	CREATE_FUNC(JGbullet);
	
};

#endif