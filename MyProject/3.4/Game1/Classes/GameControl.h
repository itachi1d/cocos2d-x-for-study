#ifndef __GAME_CONTROL__
#define __GAME_CONTROL__
#include "cocos2d.h"
#include "Anmial.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocostudio; 
using namespace cocos2d::ui;
class GameControl : public Layer
{
public:
	GameControl();
	~GameControl();
public:
	void random_create_AnImal();
	int randomNumber(int number, int numberVar);
	Point random_create_Poistion();
	void goRuns();
	std::string randomQuestion();
	void updateAnimals(float dt);
	void showQuestion(float time);
	void answerTime(float time);
	void readyTime(float time);
	void fourNumber();
	int number_not_same(int number);
	void update(float dt);
	void fourButtonCallBack(cocos2d::Ref* pSender,ui::TouchEventType type);
	void starButtonCallBack(cocos2d::Ref* pSender,ui::TouchEventType type);
	CREATE_FUNC(GameControl);
private:
	std::vector<Anmial*> allAnimals;
public:
	std::vector<std::string> questions;
	
public:
	int numbers[4];
	int ready_time;//准备剩余时间
	int answer_true;//正确答案
	int answer_time;//揭晓答案剩余时间
	int true_button;//正确的是第几个按钮
	int check_button;//玩家按的是第几个按钮
	int ques;//第几个问题
};

#endif