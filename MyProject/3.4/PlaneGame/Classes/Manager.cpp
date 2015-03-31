#include "Manager.h"
#include "Tool.h"
Manager::Manager(){}

Manager::~Manager(){}


Manager* Manager::Instance()
{
	if(manager == nullptr)
	{
		manager = new Manager();
		manager->frames = SpriteFrameCache::getInstance();
	}
	return manager;
}

void Manager::init_max_anima1()
{
	int i = 1;
	std::string name;
	for (; i <= 3; ++i)
	{
		name = "MAX1_"+Tool::toString(i)+".png";
		max1_start.pushBack(frames->getSpriteFrameByName(name));
	}
	for (; i <= 8; ++i)
	{
		name = "MAX1_"+Tool::toString(i)+".png";
		max1_content.pushBack(frames->getSpriteFrameByName(name));
	}
	for (; i <= 24; ++i)
	{
		name = "MAX1_"+Tool::toString(i)+".png";
		max1_end.pushBack(frames->getSpriteFrameByName(name));
	}
	
}

void Manager::init_maxing_anima1()
{
	std::string name;
	for(int i = 1; i <= 17; ++i)
	{
		name = "max"+Tool::toString(i)+".png";
		maxing.pushBack(frames->getSpriteFrameByName(name));
	}
}

Manager* Manager::manager = nullptr;