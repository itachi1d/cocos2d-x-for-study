/*#include "MapManager.h"
#include "CanShu.h"

using namespace cocos2d;
MapManager* MapManager::Instance()
{
	if(manager)
		return manager;
	else
	{
		manager = new MapManager();
		return manager;
	}
};
void MapManager::createMap()
{
	std::stringstream ss;
	ss<<guanKa;
	std::string str;
	ss>>str;
	std::string mapName = "map"+str+".tmx";
	map = TMXTiledMap::create(mapName);
};

TMXTiledMap* MapManager::getMap()
{
	return map;
};*/