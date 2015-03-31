#include "GameControl.h"
#include "ResourceManager.h"
#include "Parameters.h"
#include "GameLayer.h"

#include "Tool.h"


GameControl::GameControl()
{
	int len = sizeof(ResourceManager::Instance()->animal_Name) / sizeof(ResourceManager::Instance()->animal_Name[0]);
	for(int i = 0; i < len; ++i)
	{
		questions.push_back(ResourceManager::Instance()->animal_Name[i]);
	}
	questions.push_back("哺乳动物");
	true_button = 5;
	check_button = 0;
}
GameControl::~GameControl()
{
	
}

void GameControl::random_create_AnImal()
{
	int number = ResourceManager::Instance()->init_cout*mode
		+(guanQia-1)*randomNumber(ResourceManager::Instance()->add_cout, ResourceManager::Instance()->add_coutVar);
	for(int i = 0; i < number; ++i)
	{
		int type = 1+rand()%11;
		Anmial *animal = Anmial::create(type);

		animal->setSpeed(randomNumber(ResourceManager::Instance()->animal_Speed[type-1]
		+guanQia*ResourceManager::Instance()->animal_Speedcout[type-1]*mode, 
		ResourceManager::Instance()->animal_SpeedVar[type-1]+
		guanQia*ResourceManager::Instance()->animal_Speedcout[type-1]/2));//根据关卡设置动物速度

		animal->setPosition(random_create_Poistion());
		this->addChild(animal);
		allAnimals.push_back(animal);
	}

	answer_true = 0;
	std::vector<Anmial*>::iterator itr;
	if(ques >10)
	{
		switch (ques)
		{
		case 11:
			for(itr = allAnimals.begin(); itr != allAnimals.end(); ++itr)
			{
				Anmial* animal = (Anmial*)*itr;
				if(animal->isbuRu())
					answer_true ++;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		int _type = ques+1;
		for(itr = allAnimals.begin(); itr != allAnimals.end(); ++itr)
		{
			Anmial* animal = (Anmial*)*itr;
			if(animal->getType()==_type)
				answer_true ++;
		}
	}
}

Point GameControl::random_create_Poistion()
{
	return Point(480+rand()%100, 70+rand()%180);
}
int GameControl::randomNumber(int number, int numberVar)
{
	int _random = rand()%10;
	if(_random > 4)
		return number+rand()%numberVar;
	else
		return number-rand()%numberVar;
}

void GameControl::goRuns()
{
	std::vector<Anmial*>::iterator itr;
	for(itr = allAnimals.begin(); itr != allAnimals.end(); ++itr)
	{
		Anmial* animal = (Anmial*)*itr;
		animal->playerRunAnimation();
	}
}
//每帧更新动物的位置
void GameControl::updateAnimals(float dt)
{
	std::vector<Anmial*>::iterator itr;
	bool flag = false;
	for(itr = allAnimals.begin(); itr != allAnimals.end(); ++itr)
	{
		Anmial* animal = (Anmial*)*itr;
		if(animal->getPositionX() < -100)
			continue;
		else
		{
			flag = true;
			animal->setPosition(animal->getPositionX()-animal->getSpeed()*dt, animal->getPositionY());
			std::vector<Anmial*>::iterator itr2;
			for(itr2 = itr+1; itr2 != allAnimals.end(); ++itr2)
			{
				Anmial* animal2 = (Anmial*)*itr2;
				animal->AnimalsContact(animal2);
			}
		}
	}
	if(!flag)
	{
		unscheduleUpdate();
		auto *scene = Director::getInstance()->getRunningScene();
		GameLayer *layer = (GameLayer*)scene->getChildByTag(0);
		layer->scheduleOnce(schedule_selector(GameLayer::showQuestion), 0.2f);
	}
}

void GameControl::update(float dt)
{
	updateAnimals(dt);
}
//随机一个问题
std::string GameControl::randomQuestion()
{
	int len = questions.size();
	int _random = rand()%len;
	ques = _random;
	
	return questions[ques];
}

//答题倒计时
void GameControl::answerTime(float time)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameLayer *layer = (GameLayer*)scene->getChildByTag(0);
	Widget* questionMenu = (Widget*)layer->getChildByTag(1);
	Text* timeText = questionMenu->getChildByName<Text*>("timeText");
	timeText->setText(Tool::toString(--answer_time));
	if(answer_time <= 0)
	{
		unschedule(schedule_selector(GameControl::answerTime));
		layer->removeChild(questionMenu);
		if(check_button == true_button)
			layer->showWin();
		else
			layer->showFail();
	}
}
//准备倒计时
void GameControl::readyTime(float time)
{
	auto *scene = Director::getInstance()->getRunningScene();
	GameLayer *layer = (GameLayer*)scene->getChildByTag(0);
	Widget* readyMenu = (Widget*)layer->getChildByTag(1);
	Text* timeText = readyMenu->getChildByName<Text*>("timeText");
	timeText->setText(Tool::toString(--ready_time));
	if(ready_time == 2)
		layer->createAnimals();
	if(ready_time <= 0)
	{
		unschedule(schedule_selector(GameControl::readyTime));
		layer->removeChildByTag(1);
		layer->run();
	}
}

void GameControl::fourButtonCallBack(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	Button* button = (Button*)pSender;
	auto *scene = Director::getInstance()->getRunningScene();
	GameLayer *layer = (GameLayer*)scene->getChildByTag(0);
	Widget* questionMenu = (Widget*)layer->getChildByTag(1);
	Text* answerText = questionMenu->getChildByName<Text*>("answerText");
	 switch (type)
    {
		case ui::TouchEventType::TOUCH_EVENT_BEGAN:
			check_button = button->getTag();		
			answerText->setText(button->getTitleText());
			break;
		default:
			break;
    }
}

void GameControl::starButtonCallBack(cocos2d::Ref* pSender,ui::TouchEventType type)
{
	int starNumber;
	Scene *scene;
	GameLayer *layer;
	Widget* questionMenu;
	Text* starText;
	Button *button;
	switch(type)
	{
		case ui::TouchEventType::TOUCH_EVENT_BEGAN:
			scene = Director::getInstance()->getRunningScene();
			layer = (GameLayer*)scene->getChildByTag(0);
			questionMenu = (Widget*)layer->getChildByTag(1);
			starText = questionMenu->getChildByName<Text*>("starText");
			starNumber = Tool::toInt(starText->getString());
			int _random;
			if(starNumber <= 0)
			{							
				starText->runAction(Sequence::create(ScaleTo::create(0.1f, 1.5f), ScaleTo::create(0.1f, 0.5f), ScaleTo::create(0.1f, 1), NULL));
			}
			else
			{	
				starNumber --;
				UserDefault::getInstance()->setIntegerForKey("star", starNumber);
				starText->setText(Tool::toString(starNumber));
				((Button*)pSender)->runAction(Sequence::create(ScaleTo::create(0.1f, 1.5f), ScaleTo::create(0.1f, 0.5f), ScaleTo::create(0.1f, 1), NULL));
				
				std::vector<int> button_id;
				button_id.push_back(1);
				button_id.push_back(2);
				button_id.push_back(3);
				button_id.push_back(4);
				button_id.erase(button_id.begin()+true_button-1);
				for(int i = 0; i < 2; ++i)
				{
					_random = rand()%button_id.size();
					button = questionMenu->getChildByName<Button*>("Button_"+Tool::toString(button_id[_random]));
					button->setBright(false);
					button->setEnabled(false);
					button_id.erase(button_id.begin()+_random);
				}
				((Button*)pSender)->setEnabled(false);
				questionMenu->stopAllActions();
			}
			break;
		default:
			break;
	}
}

//随机出四个不同的结果
void GameControl::fourNumber()
{
	int alreadyNumber;
	
	int _random = rand()%10;
	if(_random <= 3)
	{
		alreadyNumber = 0;
		numbers[alreadyNumber] = answer_true;		
	}
	else if(_random <= 5)
	{
		alreadyNumber = 1;
		numbers[alreadyNumber] = answer_true;
	}
	else if(_random <= 7)
	{
		alreadyNumber = 2;
		numbers[alreadyNumber] = answer_true;
	}
	else if(_random <= 9)
	{
		alreadyNumber = 3;
		numbers[alreadyNumber] = answer_true;
	}
	true_button = alreadyNumber+1;
	int temp = answer_true;
	for(int i = 0; i < 4; ++i)
	{
		if(i == alreadyNumber)
			continue;
		int cout = 1+rand()%3;
		if(rand()%10 > 4)
		{
			numbers[i] = number_not_same(answer_true+cout);
		}
		else
		{
			if(answer_true-cout < 0)
				numbers[i] = number_not_same(answer_true+cout);
			else
				numbers[i] = number_not_same(answer_true-cout);
		}
	}
}
int GameControl::number_not_same(int number)
{
	for(int i = 0; i < 4; ++i)
	{
		if(number == numbers[i])
			number = number_not_same(++number);
	}
	return number;
}
