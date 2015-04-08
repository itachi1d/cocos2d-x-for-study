#ifndef _GAME_MANAGER_
#define _GAME_MANAGER_


#include "cocos2d.h"
#include "Fruit.h"
#include "Obstacle.h"
#include "Contral.h"
using namespace cocos2d;
class GameManager
{
public:
	static GameManager* Instance();
	void init_all_fruit(Layer*);
	void init_map();
	void add_all_tiled(Layer*);
	void init_obstacle();
	Fruit* random_fruit(MyPoint);
private:
	GameManager();
	~GameManager();
	static GameManager* manager;
public:
	SpriteFrameCache* frames;
	TextureCache* texture;
	std::list<Fruit*> all_fruit;
	std::vector<MyPoint> all_Obstacle; 
	std::vector<Sprite*> all_Tiled; 
	Contarl* contarl;
};

#endif