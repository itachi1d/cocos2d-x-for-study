#ifndef __SceneInterface_h__
#define __SceneInterface_h__

#include "cocos2d.h"
#include "VisibleRect.h"

USING_NS_CC;

class SceneInterface:public CCScene
{
public:
	SceneInterface();
	~SceneInterface();

	virtual void onEnter();
	virtual void MainMenuCallback(CCObject* pSender);
	virtual void pushThisScene()=0;

	CCSize win_size_;

private:

};


#endif