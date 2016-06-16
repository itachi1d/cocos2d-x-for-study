#include "GameTitle.h"

GameTitle::GameTitle()
{
	title = Sprite::create("pic/title.png");
	title->setPosition(Point(270, 600));
	effectNode = NodeGrid::create();
	effectNode->addChild(title);
	effectNode->runAction(RepeatForever::create(Ripple3D::create(2.0f, Size(32, 24), title->getPosition(), 360, 2, 5)));
	this->addChild(effectNode);
}

GameTitle::~GameTitle()
{

}

GameTitle* GameTitle::create()
{
	return new GameTitle();
}
