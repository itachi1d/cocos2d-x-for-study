#ifndef _CONTARL_
#define _CONTARL_

#include "cocos2d.h"
#include "fruit/Fruit.h"
using namespace cocos2d;
class Contarl : public Layer
{
public:
	Contarl();
	~Contarl();
	void setTouchListener_game1();
	void remove_touch_1();
	void setTouchListener_game2();
	void remove_touch_2();

	void changePoint(Touch* touch, Event* event);
	bool xiao_chu();
	int xiaochu_number(Fruit*);
	void remove_fruits();

	void update(float dt);
	CREATE_FUNC(Contarl);
private:
	EventListenerTouchOneByOne *listener1;
	EventListenerTouchOneByOne *listener2;
private:
	Fruit* fruit;
	
public:
	static bool is_can_touch;
	std::vector<Fruit*> change_pos_fruits;//判断是否可以进行消除的水果
	std::vector<Fruit*> xc_fruits;//进行消除的水果
	int finish_anima_fruits;//记录结束活动的水果
};
#endif