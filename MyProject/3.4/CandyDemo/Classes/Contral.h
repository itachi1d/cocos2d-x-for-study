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
	void create_new_fruits();//创建新的水果

	Fruit* create_level_fruit(int _level, Fruit* fruit);//创建特殊水果
	void add_remove_fruit_for_level_4(Fruit*);//4等级水果处理

	void update(float dt);
	bool is_change_x();
	CREATE_FUNC(Contarl);
public:
	EventListenerTouchOneByOne *listener1;
	EventListenerTouchOneByOne *listener2;
private:
	Fruit* touch_fruit;
	int chang_pos_fruit_number;
	int check_number;
public:
	static bool is_can_touch;
	std::vector<Fruit*> change_pos_fruits;//判断是否可以进行消除的水果
	std::vector<Fruit*> xc_fruits;//进行消除的水果
	std::vector<Fruit*> xc_more_fruits;//进行额外消除的水果
	std::vector<MyPoint> xc_points;//进行消除所有水果的位置
	std::vector<MyPoint> xc_more_points;//产生特殊水果的位置
	std::vector<Fruit*> add_teshu_fruit;//创建特殊的水果
	int finish_anima_fruits;//记录结束活动的水果
	bool isMove;
	bool changePos;
	bool is_touch_move;
};
#endif



