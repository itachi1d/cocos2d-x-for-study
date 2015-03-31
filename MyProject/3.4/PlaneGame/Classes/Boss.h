#ifndef _BOSS_
#define _BOSS_

class Boss
{
	virtual Boss *create() = 0;
	virtual void changeMode() = 0;
	virtual void shutBullet() = 0;
	virtual void boom() = 0;
};
#endif