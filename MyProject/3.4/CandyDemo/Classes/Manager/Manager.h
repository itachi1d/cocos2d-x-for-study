#ifndef _MANAGER_
#define _MANAGER_


#include "cocos2d.h"
#include "fruit/Fruit.h"
#include "Obstacle.h"
#include "Contral.h"
using namespace cocos2d;
class Manager
{
public:
	static Manager* Instance();
	void init_all_fruit(Layer*);
	void init_map();
	void add_all_tiled(Layer*);
	void init_obstacle();
	Fruit* random_fruit(MyPoint);
private:
	Manager();
	~Manager();
	static Manager* manager;
public:
	SpriteFrameCache* frames;
	TextureCache* texture;
	std::list<Fruit*> all_fruit;
	std::vector<MyPoint> all_Obstacle; 
	std::vector<Sprite*> all_Tiled; 
	Contarl* contarl;
};

#endif