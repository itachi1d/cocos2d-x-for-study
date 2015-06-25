#ifndef Boss_Update_h__
#define Boss_Update_h__

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "Boss.h"

using namespace cocos2d;
class Boss_Update : public Layer
{
public:
	Boss_Update();
	~Boss_Update();
public:
	void begin_to_boss(float dt);
	void show_warning();
	void boss_update(float dt, Layer* layer);
	void first_stop(float dt);
	void updateXueTiao();
	b2Body *getBossBody();
	CREATE_FUNC(Boss_Update);
private:
	
public:
	ProgressTimer* xuetiao;
	Boss* boss;
	b2Body *bossBody;
};
#endif // Boss_Update_h__
