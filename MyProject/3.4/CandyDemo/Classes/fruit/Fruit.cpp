#include "Fruit.h"
#include "Perf.h"
#include "Tool.h"
#include "Contral.h"
#include "HelloWorldScene.h"
Fruit::Fruit():is_user_contact(false),level(0)
{

}
Fruit* Fruit::create(int type)
{
	std::string fruit_name;
	switch (type)
	{
	case 0:
		fruit_name = apple_name;
		break;
	case 1:
		fruit_name = basaha_name;
		break;
	case 2:
		fruit_name = peach_name;
		break;
	case 3:
		fruit_name = sandia_name;
		break;
	case 4:
		fruit_name = banana_name;
		break;
	default:
		break;
	}

	return createWithSpriteFrameName(fruit_name, type);
}

Fruit* Fruit::createWithSpriteFrameName(const std::string& spriteFrameName, int type)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != nullptr, msg);
#endif

	return createWithSpriteFrame(frame, type);
}
Fruit* Fruit::createWithSpriteFrame(SpriteFrame *spriteFrame, int type)
{
	Fruit *sprite = new (std::nothrow) Fruit();
	if (sprite && spriteFrame && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->type = type;
		switch (type)
		{
		case 0:
			sprite->file_name = apple_name;
			break;
		case 1:
			sprite->file_name = basaha_name;
			break;
		case 2:
			sprite->file_name = peach_name;
			break;
		case 3:
			sprite->file_name = sandia_name;
			break;
		case 4:
			sprite->file_name = banana_name;
			break;
		default:
			break;
		}
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Fruit::set_world_point(int _x, int _y)
{
	world_point.set_world_point(_x, _y);
	this->setPosition(world_point.true_x, world_point.true_y);
}

void Fruit::run_to_point(MyPoint point, bool isback)
{
	MoveTo* action = MoveTo::create(0.2f, Point(point.true_x, point.true_y));
	FiniteTimeAction * actionOne;
	if(isback)
		actionOne = Sequence::create(
		action,
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(Fruit::updatePoint)),
		NULL);
	else
		actionOne = Sequence::create(
		action,
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(Fruit::updatePoint_with_xc)),
		NULL);
	this->runAction(actionOne);
}
void Fruit::removeAnima()
{
	FiniteTimeAction * actionOne = Sequence::create(
		ScaleTo::create(0.3f, 0.1f),
		CallFunc::create(this, CC_CALLFUNC_SELECTOR(Fruit::remove)),
		NULL);
	this->runAction(actionOne);
	
}

void Fruit::updatePoint_with_xc()
{
	Scene *scene = Director::getInstance()->getRunningScene();
	Game_Scene_1* layer = (Game_Scene_1*)scene->getChildByTag(0);
	this->world_point.true_x = this->getPositionX();
	this->world_point.true_y = this->getPositionY();
	MyPoint point = Tool::true_to_world(Point(world_point.true_x, world_point.true_y));
	this->world_point.set_world_point(point.world_x, point.world_y);
	layer->contarl->finish_anima_fruits++;
}
void Fruit::updatePoint()
{
	this->world_point.true_x = this->getPositionX();
	this->world_point.true_y = this->getPositionY();
	MyPoint point = Tool::true_to_world(Point(world_point.true_x, world_point.true_y));
	this->world_point.set_world_point(point.world_x, point.world_y);
	Contarl::is_can_touch = true;
}

void Fruit::remove()
{
	this->removeFromParentAndCleanup(true);
	Scene *scene = Director::getInstance()->getRunningScene();
	Contarl::is_can_touch = true;
}

std::string Fruit::getFileName()
{
	return file_name;
}

void Fruit::level_up(int _level)
{
	level = _level;
	FiniteTimeAction * actionOne = Sequence::create(
		ScaleTo::create(0.1f, 1.5f),
		ScaleTo::create(0.1f, 1.0f),
		NULL);
	switch (level)
	{
	case 1:
		this->setColor(Color3B(50, 50, 255));
		this->runAction(actionOne);
		break;
	case 2:
		this->setColor(Color3B(50, 255, 50));
		this->runAction(actionOne);
		break;
	case 3:
		this->setColor(Color3B(255, 50, 50));
		this->runAction(actionOne);
		break;
	case 4:
		this->runAction(actionOne);
		this->file_name = max_name;
		this->setDisplayFrame(Manager::Instance()->frames->spriteFrameByName(file_name));
		break;
	default:
		break;
	}
	
}
