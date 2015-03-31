#pragma once
#include "cocos2d.h"

class EMail
{
public:
	EMail();
	~EMail();

	int ID;
	std::string name;
	int type;
	std::string icon;
	std::string content;
	std::string addresser;
	std::string rewardID;
	bool isRead;
};