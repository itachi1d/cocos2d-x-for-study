#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameControl.h"
using namespace cocos2d;
class GameLayer : public cocos2d::Layer
{
public:
	~GameLayer();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void showReadyMenu();
    void showQuestion(float time);
	void showWin();
	void showFail();
	void randomLoadMap();
	void createAnimals();
	void run();
	void returnMainMenu(cocos2d::Ref* pSender,ui::TouchEventType type);
	void nextStep(cocos2d::Ref* pSender,ui::TouchEventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
private:
	GameControl *control;
	
};

#endif // __HELLOWORLD_SCENE_H__
