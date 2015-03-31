#include "SceneInterface.h"
#include "SceneSelect.h"

SceneInterface::SceneInterface()
{
	CCScene::init();
	win_size_=CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* label = CCLabelTTF::create("Back", "Arial", 20);
	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(SceneInterface::MainMenuCallback));

    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);

    pMenu->setPosition( Vec2::ZERO );
	pMenuItem->setPosition( CCPointMake( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

    addChild(pMenu);
}

SceneInterface::~SceneInterface()
{
}
void SceneInterface::onEnter()
{
	CCScene::onEnter();
}

void SceneInterface::MainMenuCallback(CCObject* pSender)
{
	CCScene* p_scene=CCScene::create();
	CCLayer* p_layer=SceneSelect::create();

	p_scene->addChild(p_layer);
	CCDirector::sharedDirector()->replaceScene(p_scene);
}