#include "RTscene.h"
#include "SceneSelect.h"
RTscene::RTscene(void)
{
}


RTscene::~RTscene(void)
{
}
void RTscene::pushThisScene(std::string _str)
{
	RTlayer* p_display=new RTlayer();
	p_display->autorelease();
	p_display->str = _str;
	
	addChild(p_display);
	CCDirector::sharedDirector()->replaceScene(this);
}

void RTscene::pushThisScene()
{
	RTlayer* p_display=new RTlayer();
	p_display->autorelease();
	
	addChild(p_display);
	CCDirector::sharedDirector()->replaceScene(this);
}

RTlayer::RTlayer()
{
	
}

void RTlayer::onEnter()
{
	LabelTTF *scene = LabelTTF::create(str,"Arial",50.0f);
	addChild(scene, 10);
	scene->setPosition(300, 200);
}

RTlayer::~RTlayer()
{
}
