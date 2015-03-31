#include "ListViewItemListener.h"
#include "UILayout.h"
#include "Gbk2UTF_8.h"
#include "UIText.h"
#include "UIScrollView.h"
#include "UIImageView.h"
#include "UIButton.h"
#include "GameScene.h"
#include "EmailManager.h"
using namespace ui;
using namespace cocos2d;
void ListViewItemListener::showContent(Ref* button ,  TouchEventType type)
{
	Widget* UI;
	Layout *contentPanel;
	ImageView *bg;
	ImageView *extra;
	int _id;
	EMail *mail;
	Button* backButton;
	std::string str;
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		log("began");
		break;
	case TOUCH_EVENT_MOVED:
		log("moved");
		break;
	case TOUCH_EVENT_ENDED:
		UI = (Widget*)layer->getChildByTag(1);
		contentPanel = (Layout*)UI->getChildByName("ContentPanel");
		
		backButton = (Button*)contentPanel->getChildByName("back");
		bg = (ImageView*)contentPanel->getChildByName("bg");
		extra = (ImageView*)bg->getChildByName("Image_26");
		_id = ((Button*)button)->getTag();
		mail = EmailManager::Instance()->find(_id);
		mail->isRead = true;
		contentPanel->setTouchEnabled(true);
		contentPanel->setVisible(true);
		((Text*)contentPanel->getChildByName("title"))->setText(mail->name);
		((Text*)contentPanel->getChildByName("content"))->setText(mail->content);
		((Text*)contentPanel->getChildByName("addresser"))->setText(mail->addresser);
		if(mail->type == 2)
		{
			str = "领取";
			Gbk2UTF_8::ConvertStringToUTF8(str);
			((Text*)backButton->getChildByName("backButtonText"))->setText(str);
		}
		else
		{
			str = "确定";
			mail->icon = "01508.png";
			Gbk2UTF_8::ConvertStringToUTF8(str);
			((Text*)backButton->getChildByName("backButtonText"))->setText(str);
			extra->setVisible(false);
		}
		break;
	case TOUCH_EVENT_CANCELED:
		log("canceled");
		break;
	default:
		break;
	}

}

void ListViewItemListener::back(Ref* sender , ui::TouchEventType type)
{
	std::string str;
	std::string str2;
	Button* button = (Button*)sender;
	Widget* UI;
	Layout *contentPanel;
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		log("began");
		break;
	case TOUCH_EVENT_MOVED:
		log("moved");
		break;
	case TOUCH_EVENT_ENDED:
		str = ((Text*)button->getChildByName("backButtonText"))->getStringValue();
		str2 = "确定";
		Gbk2UTF_8::ConvertStringToUTF8(str2);
		if(str.compare(str2) == 0)
		{
			UI = (Widget*)layer->getChildByTag(1);
			contentPanel = (Layout*)UI->getChildByName("ContentPanel");
			contentPanel->setTouchEnabled(false);
			contentPanel->setVisible(false);
			layer->list->removeItem(contentPanel->getParent()->getTag());
			layer->updateListView();
		}
		else
		{
			//领取奖励代码
			UI = (Widget*)layer->getChildByTag(1);
			contentPanel = (Layout*)UI->getChildByName("ContentPanel");
			contentPanel->setTouchEnabled(false);
			contentPanel->setVisible(false);
			layer->list->removeItem(contentPanel->getParent()->getTag());
			layer->updateListView();
		}
		break;
	case TOUCH_EVENT_CANCELED:
		log("canceled");
		break;
	default:
		break;
	}
}
void ListViewItemListener::changeType0(Ref* sender , ui::TouchEventType type)
{
	Widget* UI;
	Button *noReaderbutton;
	Button *overReaderbutton;
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		log("began");
		break;
	case TOUCH_EVENT_MOVED:
		log("moved");
		break;
	case TOUCH_EVENT_ENDED:
		layer->type = 0;
		layer->updateListView();
		UI = (Widget*)layer->getChildByTag(1);
		noReaderbutton = (Button*)UI->getChildByName("NoRead");
		overReaderbutton = (Button*)UI->getChildByName("OverRead");
		noReaderbutton->setBright(false);
		noReaderbutton->setTouchEnabled(false);
		overReaderbutton->setBright(true);
		overReaderbutton->setTouchEnabled(true);
		noReaderbutton->setZOrder(3);
		noReaderbutton->setPositionX(noReaderbutton->getPositionX()-8);
		overReaderbutton->setZOrder(0);
		overReaderbutton->setPositionX(noReaderbutton->getPositionX()+8);
		break;
	case TOUCH_EVENT_CANCELED:
		log("canceled");
		break;
	default:
		break;
	}
}
void ListViewItemListener::changeType1(Ref* sender , ui::TouchEventType type)
{
	Widget* UI;
	Button *noReaderbutton;
	Button *overReaderbutton;
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		log("began");
		break;
	case TOUCH_EVENT_MOVED:
		log("moved");
		break;
	case TOUCH_EVENT_ENDED:
		layer->type = 1;
		layer->updateListView();
		UI = (Widget*)layer->getChildByTag(1);
		noReaderbutton = (Button*)UI->getChildByName("NoRead");
		overReaderbutton = (Button*)UI->getChildByName("OverRead");
		noReaderbutton->setBright(true);
		noReaderbutton->setTouchEnabled(true);
		overReaderbutton->setBright(false);
		overReaderbutton->setTouchEnabled(false);
		overReaderbutton->setZOrder(3);
		overReaderbutton->setPositionX(noReaderbutton->getPositionX()-8);
		noReaderbutton->setZOrder(0);
		noReaderbutton->setPositionX(noReaderbutton->getPositionX()+8);
		break;
	case TOUCH_EVENT_CANCELED:
		log("canceled");
		break;
	default:
		break;
	}
}
void ListViewItemListener::close(Ref* sender , ui::TouchEventType type)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameScene *layer = (GameScene*)scene->getChildByTag(0);
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		log("began");
		break;
	case TOUCH_EVENT_MOVED:
		log("moved");
		break;
	case TOUCH_EVENT_ENDED:
		layer->getChildByTag(1)->removeFromParentAndCleanup(true);
		break;
	case TOUCH_EVENT_CANCELED:
		log("canceled");
		break;
	default:
		break;
	}
	
}