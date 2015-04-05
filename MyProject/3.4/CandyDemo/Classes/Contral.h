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
	void remove_fruits();//清空水果
	void teshu_fruit(Fruit* fruit);//特殊水果处理

	void create_level_fruit(int _level, Fruit* fruit);//创建特殊水果
	void add_remove_fruit_for_level_4(Fruit*);//4等级水果处理
	void update(float dt);
	CREATE_FUNC(Contarl);
private:
	EventListenerTouchOneByOne *listener1;
	EventListenerTouchOneByOne *listener2;
private:
	Fruit* fruit;
	int chang_pos_fruit_number;
public:
	static bool is_can_touch;
	std::vector<Fruit*> change_pos_fruits;//判断是否可以进行消除的水果
	std::vector<Fruit*> xc_fruits;//进行消除的水果
	std::vector<Fruit*> xc_more_fruits;//进行额外消除的水果
	int finish_anima_fruits;//记录结束活动的水果
};
#endif



