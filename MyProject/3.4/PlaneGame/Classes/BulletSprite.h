#include "cocos2d.h"

USING_NS_CC;
class BulletSprite : public Sprite
{
public:
	BulletSprite():TYPE(0),ATK((TYPE+1)*30+70){};
	static BulletSprite* createWithTexture(Texture2D *texture, const Rect& rect, bool rotated=false)
	{
		BulletSprite *sprite = new BulletSprite();
		if (sprite && sprite->initWithTexture(texture, rect, rotated))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	void setATK(float _atk);
	void setType(int _type);
	int TYPE;
	float ATK;

	CREATE_FUNC(BulletSprite);
};