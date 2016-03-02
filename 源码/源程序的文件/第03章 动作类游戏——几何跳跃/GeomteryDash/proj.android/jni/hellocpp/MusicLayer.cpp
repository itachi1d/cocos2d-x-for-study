#include "MusicLayer.h"
#include "../frameHelp/SpriteManager.h"
#include "Constant.h"

bool MusicLayer::init()
{
	//调用父类的初始化
    if (!Layer::init())
    {
        return false;
    }

    this->setTag(INDEX_MUSICLAYER);//设置节点的标签

    visibleSize = Director::getInstance()->getVisibleSize();//获取可见区域尺寸
	origin = Director::getInstance()->getVisibleOrigin();//获取可见区域原点坐标

	sh = new SpriteManager(this);//精灵管理类
	mlh = new MusicLayerHelp(this);//帮助类
	mlh->initCreateSprite();//初始化 创建精灵

	return true;
}


