#include "GameScene.h"
#include "cocostudio\CocoStudio.h"
#include "cocos-ext.h"
#include "UIButton.h"
#include "EMailXmlReader.h"
#include "EmailManager.h"
#include "EMail.h"
#include "UILayout.h"
#include "Gbk2UTF_8.h"
#include "UIText.h"
#include "UIScrollView.h"
#include "UIImageView.h"
#include "ListViewItemListener.h"



USING_NS_CC;

using namespace ui;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	layer->setTag(0);
    // return the scene
    return scene;
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("UI/Email/NewUi_1.ExportJson");
	this->addChild(UI);
	UI->setTag(1);
	type = 0;
	Button *noReaderbutton = (Button*)UI->getChildByName("NoRead");
	Button *overReaderbutton = (Button*)UI->getChildByName("OverRead");
	noReaderbutton->addTouchEventListener(this, toucheventselector(ListViewItemListener::changeType0));
	overReaderbutton->addTouchEventListener(this, toucheventselector(ListViewItemListener::changeType1));
	noReaderbutton->setBright(false);
	noReaderbutton->setTouchEnabled(false);
	noReaderbutton->setZOrder(3);
	noReaderbutton->setPositionX(noReaderbutton->getPositionX()-8);
	list = (ListView*)UI->getChildByName("ListView1");
	Layout *contentPanel = (Layout*)UI->getChildByName("ContentPanel");
	Button* backButton = (Button*)contentPanel->getChildByName("back");
	backButton->addTouchEventListener(this, toucheventselector(ListViewItemListener::back));
	Button *closebutton = (Button*)UI->getChildByName("Close");
	closebutton->addTouchEventListener(this, toucheventselector(ListViewItemListener::close));
	loadXML();
	//----------------模拟发送数据------------
	loadItem(200010);
	loadItem(200007);
	loadItem(200008);
	loadItem(200009);
	loadItem(200003);
	//--------------------------------------------
	updateListView();//更新列表
	return true;
}
void GameScene::loadItem(int _id)
{
	Widget* UI = (Widget*)getChildByTag(1);
	EMail *mail = EmailManager::Instance()->find(_id);
	Layout *item = (Layout*)UI->getChildByName("ItemPanel");
	Text *title = (Text*)item->getChildByName("title");
	title->setText(mail->name);
	Text *addresser = (Text*)item->getChildByName("addresser");
	addresser->setText(mail->addresser);
	Layout *item2 = (Layout*)item->clone();
	Button *itemButton = (Button*)item2->getChildByName("button");
	itemButton->setTag(_id);
	mail->isRead = false;
	itemButton->addTouchEventListener(this, toucheventselector(ListViewItemListener::showContent));
	ImageView *icon = (ImageView*)item2->getChildByName("icon")->getChildByName("iconImg");
	((Sprite*)(icon->getVirtualRenderer()))->setSpriteFrame(mail->icon);//ImageView换图片
	item2->setVisible(true);
	//list->pushBackCustomItem(item2);
	map.insert(std::map<int,EMail*>::value_type(mail->ID,mail));
}

void GameScene::loadXML()
{
	EMailXmlReader reader;
	reader.Init("GameXml/MailBox.xml");
}



void GameScene::updateListView()
{
	list->removeAllItems();
	std::map<int, EMail*>::iterator iterMap = map.begin();
    for (;iterMap != map.end();iterMap++)
    {
		if (type == 0)
		{
			if(iterMap->second->isRead == false)
			{
				addListItem(iterMap->second);
			}
		}
		else
		{
			if(iterMap->second->isRead == true)
			{
				addListItem(iterMap->second);
			}
		}
    }
}

void GameScene::addListItem(EMail* mail)
{
	Widget* UI = (Widget*)getChildByTag(1);
	Layout *item = (Layout*)UI->getChildByName("ItemPanel");
	Text *title = (Text*)item->getChildByName("title");
	title->setText(mail->name);
	Text *addresser = (Text*)item->getChildByName("addresser");
	addresser->setText(mail->addresser);
	Layout *item2 = (Layout*)item->clone();
	Button *itemButton = (Button*)item2->getChildByName("button");
	itemButton->setTag(mail->ID);
	itemButton->addTouchEventListener(this, toucheventselector(ListViewItemListener::showContent));
	ImageView *icon = (ImageView*)item2->getChildByName("icon")->getChildByName("iconImg");
	((Sprite*)(icon->getVirtualRenderer()))->setSpriteFrame(mail->icon);//ImageView换图片
	item2->setVisible(true);
	list->pushBackCustomItem(item2);
}


