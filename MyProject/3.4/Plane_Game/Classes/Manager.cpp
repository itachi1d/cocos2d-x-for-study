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

void Manager::init_boom_anim()
{
	std::string name;
	int i = 1;
	while(true)
	{
		name = "boom_"+Tool::toString(i)+".png";
		if(!frames->getSpriteFrameByName(name))
			break;
		booms.pushBack(frames->getSpriteFrameByName(name));
		i++;
	}
}

void Manager::init_Anima()
{
	init_boom_anim();
	init_maxing_anima1();
	init_max_anima1();
}

void Manager::init_Player_anim()
{
	player1.pushBack(frames->getSpriteFrameByName("A_player01_1.png"));
	player1.pushBack(frames->getSpriteFrameByName("A_player01_2.png"));
	player2.pushBack(frames->getSpriteFrameByName("A_player02_1.png"));
	player2.pushBack(frames->getSpriteFrameByName("A_player02_2.png"));
	player3.pushBack(frames->getSpriteFrameByName("A_player03_1.png"));
	player3.pushBack(frames->getSpriteFrameByName("A_player03_2.png"));
}

Manager* Manager::manager = nullptr;