#include "RankLayer.h"

using namespace std;

bool RankLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	initTile(TYPE::FRUIT);
	return true;
}

void RankLayer::save(int newScore)
{
	string score;
	int *tempScore = new int[5];
	load();
	int i = 0;
	string name = TYPE::FRUIT == m_id ? "fruit" : "bird";
	for ( i = 0; i < 5; ++i)
	{
		tempScore[i] = atoi(scores[i].c_str());
	}
	for (i = 4; i >= 0; ++i)
	{
		score = StringUtils::format("%d", newScore);
		if (newScore > tempScore[i])
		{
			if (i != 4)
			{
				score = StringUtils::format("%d", tempScore[i]);
				UserDefault::getInstance()->setStringForKey((name + StringUtils::format("b%d", (i + 1))).c_str(), score);
			}
			UserDefault::getInstance()->setStringForKey((name + StringUtils::format("b%d", i)).c_str(), score);
		}
	}
	UserDefault::getInstance()->flush();
}

void RankLayer::load()
{
	string name = TYPE::FRUIT == m_id ? "fruit" : "bird";
	for (int i = 0; i < 5; ++i)
	{
		scores[i] = UserDefault::getInstance()->getStringForKey((name + StringUtils::format("b%d", i)).c_str(), "0");
	}
}

void RankLayer::initTile(TYPE id)
{
	m_id = id;
	this->removeAllChildren();
	auto rootNode = CSLoader::createNode("RankLayer.csb");
	addChild(rootNode);
	string titleName = "title" + StringUtils::format("%d", TYPE::FRUIT == m_id ? 1 : 2);
	string bgName = "bg" + StringUtils::format("%d", TYPE::FRUIT == m_id ? 1 : 2);
	(rootNode->getChildByName(titleName))->setVisible(true);
	(rootNode->getChildByName(bgName))->setVisible(true);
	labelSprite = Sprite::create();
	addChild(labelSprite);
	load();
	string scoreTxt;
	for (int i = 0; i < 5; ++i)
	{
		scoreTxt = scores[i];
		labels = Label::createWithTTF(StringUtils::format("%d", (i + 1)), "fonts/FZKATJW.ttf", 60, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		labels->setPosition(Point(146, 380 - (50 * i)));
		labels->enableOutline(Color4B(187, 187, 187, 255), 2);
		labelSprite->addChild(labels);

		if ("0" == scoreTxt)
		{
			scoreTxt = "-";
		}
		labels = Label::createWithTTF(scoreTxt, "fonts/FZKATJW.ttf", 60, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
		labels->setPosition(Point(375, 380 - (50 * i)));
		labels->enableOutline(Color4B(187, 187, 187, 255), 2);
		labelSprite->addChild(labels);
	}
	m_next_button = static_cast<Button*>(rootNode->getChildByName("NextBtn"));
	m_menu_button = static_cast<Button*>(rootNode->getChildByName("MenuBtn"));
	m_next_button->addClickEventListener(CC_CALLBACK_1(RankLayer::menuCallBack0, this));
	m_menu_button->addClickEventListener(CC_CALLBACK_1(RankLayer::menuCallBack0, this));
}
void RankLayer::menuCallBack0(Ref*pSender)
{
	if (pSender == m_next_button)
	{
		initTile(TYPE::FRUIT == m_id ? TYPE::BIRD : TYPE::FRUIT);
	}
	else if (pSender == m_menu_button)
	{
		GameSceneManager::getInstance()->goToMainScene();
	}
}
