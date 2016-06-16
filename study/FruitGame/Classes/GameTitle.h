#pragma one
#include "cocos2d.h"

using namespace cocos2d;

class GameTitle : public Sprite
{
public:
	GameTitle();
	~GameTitle();
public:
	static GameTitle* create();
private:
	Sprite* title;
	NodeGrid* effectNode;
};