#include "GameLayer.h"
#include "cocostudio\CocoStudio.h"
#include "Tool.h"
#include "Anmial.h"
#include "ResourceManager.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "ui/CocosGUI.h"
#include "Parameters.h"
#include "MainMenuLayer.h"


USING_NS_CC;
using namespace cocostudio; 
using namespace cocos2d::ui;

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);
	layer->setTag(0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	srand((unsigned)time(NULL));
    Size visibleSize = Director::getInstance()->getVisibleSize();
	ResourceManager::initAnimats();

	randomLoadMap();

	Text* gqText = Text::create();
	std::string text = "当前关卡:"+Tool::toString(guanQia);
	gqText->setText(text);
	addChild(gqText);
	gqText->setFontSize(25);
	gqText->setPosition(Point(10, 310));
	gqText->setAnchorPoint(Point(0, 1));
	
	control = GameControl::create();
	addChild(control, 4);
	showReadyMenu();
    return true;
}

void GameLayer::createAnimals()
{
	control->random_create_AnImal();
}
void GameLayer::run()
{
	control->goRuns();
	control->scheduleUpdate();
}

void GameLayer::randomLoadMap()
{
	std::string map_name;
	int _random = 1+rand()%5;
	map_name = "GameScene"+Tool::toString(_random)+".csb";
	Widget* node1 = static_cast<Widget*>(CSLoader::createNode (map_name));
	Widget* node2 = static_cast<Widget*>(CSLoader::createNode ("chuanglian.csb"));

	this->addChild (node1);
	this->addChild (node2, 5);

	Widget* node3 = static_cast<Widget*>(CSLoader::createNode ("goldScene.csb"));
	Text* goldText = node3->getChildByName<Text*>("goldText");
	goldText->setText(Tool::toString(UserDefault::getInstance()->getIntegerForKey("gold", 0)));
	addChild(node3, 6);
	node3->setTag(2);
}

void GameLayer::showReadyMenu()
{
	Widget* readyMenu = static_cast<Widget*>(CSLoader::createNode ("ReadyScene.csb"));
	this->addChild(readyMenu, 10);
	readyMenu->setTag(1);
	Text* questionText = readyMenu->getChildByName<Text*>("questionText");
	questionText->setText(control->randomQuestion());

	control->ready_time = 4;
	control->schedule(schedule_selector(GameControl::readyTime), 1);
}

void GameLayer::showQuestion(float time)
{
	Widget* questionMenu = static_cast<Widget*>(CSLoader::createNode ("QuestionMenu.csb"));
	timeline::ActionTimeline* action = CSLoader::createTimeline("QuestionMenu.csb");
	this->addChild(questionMenu, 10);
	questionMenu->setTag(1);
	questionMenu->runAction(action);
	action->gotoFrameAndPlay(0, -1);

	Text* questionText = questionMenu->getChildByName<Text*>("questionText");
	questionText->setText(control->questions[control->ques]);

	Text* starText = questionMenu->getChildByName<Text*>("starText");
	starText->setText(Tool::toString(UserDefault::getInstance()->getIntegerForKey("star", 3)));

	Button *button1 = questionMenu->getChildByName<Button*>("Button_1");
	Button *button2 = questionMenu->getChildByName<Button*>("Button_2");
	Button *button3 = questionMenu->getChildByName<Button*>("Button_3");
	Button *button4 = questionMenu->getChildByName<Button*>("Button_4");
	Button *button5 = questionMenu->getChildByName<Button*>("Button_5");

	control->fourNumber();
	button1->setTitleText(Tool::toString(control->numbers[0]));
	button2->setTitleText(Tool::toString(control->numbers[1]));
	button3->setTitleText(Tool::toString(control->numbers[2]));
	button4->setTitleText(Tool::toString(control->numbers[3]));
	button1->setTag(1);
	button2->setTag(2);
	button3->setTag(3);
	button4->setTag(4);

	control->answer_time = 10;
	control->schedule(schedule_selector(GameControl::answerTime), 1);

	button1->addTouchEventListener(control, toucheventselector(GameControl::fourButtonCallBack));
	button2->addTouchEventListener(control, toucheventselector(GameControl::fourButtonCallBack));
	button3->addTouchEventListener(control, toucheventselector(GameControl::fourButtonCallBack));
	button4->addTouchEventListener(control, toucheventselector(GameControl::fourButtonCallBack));
	button5->addTouchEventListener(control, toucheventselector(GameControl::starButtonCallBack));
}


void GameLayer::showWin()
{
	Widget* winMenu = static_cast<Widget*>(CSLoader::createNode ("WinScene.csb"));
	Widget* tx = static_cast<Widget*>(CSLoader::createNode ("WinTX.csb"));
	timeline::ActionTimeline* action1 = CSLoader::createTimeline("WinScene.csb");
	timeline::ActionTimeline* action2 = CSLoader::createTimeline("WinTX.csb");
	this->addChild(winMenu, 10);
	this->addChild(tx, 10);
	winMenu->runAction(action1);
	action1->gotoFrameAndPlay(0, -1);
	tx->runAction(action2);
	action2->gotoFrameAndPlay(0, 0);

	Button*button1 = winMenu->getChildByName<Button*>("Button_1");
	Button*button2 = winMenu->getChildByName<Button*>("Button_2");
	button1->addTouchEventListener(this, toucheventselector(GameLayer::returnMainMenu));
	button2->addTouchEventListener(this, toucheventselector(GameLayer::nextStep));

	int addCout = guanQia*10;
	Text* addText = winMenu->getChildByName<Text*>("add_gold_text");
	addText->setText(Tool::toString(addCout));

	Text* goldText = this->getChildByTag(2)->getChildByName<Text*>("goldText");
	UserDefault::getInstance()->setIntegerForKey("gold", UserDefault::getInstance()->getIntegerForKey("gold", 0)+addCout);
	goldText->setText(Tool::toString(UserDefault::getInstance()->getIntegerForKey("gold", 0)));
}
void GameLayer::showFail()
{
	Widget* failMenu = static_cast<Widget*>(CSLoader::createNode ("FailScene.csb"));
	timeline::ActionTimeline* action = CSLoader::createTimeline("FailScene.csb");
	this->addChild(failMenu, 10);
	failMenu->runAction(action);
	action->gotoFrameAndPlay(0, 0);

	Button*button1 = failMenu->getChildByName<Button*>("Button_1");
	button1->addTouchEventListener(this, toucheventselector(GameLayer::returnMainMenu));
}

void GameLayer::returnMainMenu(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	Scene* scene;
	 switch (type)
	{
	 case (int)ui::TouchEventType::TOUCH_EVENT_ENDED:
		//回到主菜单
		guanQia = 1;
		ResourceManager::Instance()->destoryGameLayerResource();
		scene = Scene::create(); 
		scene->addChild(MainMenuLayer::create());
		Director::getInstance()->replaceScene(scene);
		break;
	default:
		break;
	}
}


void GameLayer::nextStep(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	Scene* scene;
	 switch (type)
	{
	 case (int)ui::TouchEventType::TOUCH_EVENT_ENDED:
		//下一关
		guanQia++;
		UserDefault::getInstance()->setIntegerForKey("highScore", guanQia);
		scene = GameLayer::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	default:
		break;
	}
}

GameLayer::~GameLayer()
{
	
}


