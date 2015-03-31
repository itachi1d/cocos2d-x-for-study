#include "cocos2d.h"

using namespace cocos2d;
class GameResource
{
public:
	static GameResource* Instance()
	{
		if(gameResource == NULL)
			gameResource = new GameResource();
		return gameResource;
	}
	Texture2D *bgs;
	Texture2D *feiji;
	Texture2D *boom;
	Texture2D *shot;
	Texture2D *penshe;
	Texture2D *bulletsTexture;
private:
	GameResource();
	~GameResource();
	static GameResource *gameResource;
};