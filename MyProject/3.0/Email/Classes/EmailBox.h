#include "cocos2d.h"

using namespace cocos2d;

class EmailBox : public Sprite
{
public:
	EmailBox();
	~EmailBox();
	void CreateBox();
	static EmailBox* createWithTexture(Texture2D *texture, const Rect& rect, bool rotated=false)
	{
		EmailBox *sprite = new EmailBox();
		if (sprite && sprite->initWithTexture(texture, rect, rotated))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
};