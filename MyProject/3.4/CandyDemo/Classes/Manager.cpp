#include "Manager.h"
#include "Perf.h"
#include "Tool.h"

GameManager::GameManager(){}
GameManager::~GameManager(){}

GameManager* GameManager::Instance()
{
	if(manager == nullptr)
	{
		manager = new GameManager();
		manager->frames = SpriteFrameCache::getInstance();
		manager->texture = TextureCache::getInstance();
		manager->contarl = Contarl::create();
	}
	return  manager;
}

void GameManager::init_all_fruit(Layer* layer)
{
	bool flag = true;
	std::vector<MyPoint>::iterator itr;
	for(int i = 0; i < WORLD_HEIGHT; ++i)
	{
		for(int j = 0; j < WORLD_WIDTH; ++j)
		{
			flag = true;
			for(itr = all_Obstacle.begin(); itr!=all_Obstacle.end(); ++itr)
			{
				MyPoint point = (MyPoint)*itr;
				MyPoint this_point(j, i);
				if(this_point == point)
				{
					flag = false;
					break;
				}
			}
			if(!flag)
				continue;
			Fruit* fruit = random_fruit(MyPoint(j, i));
			fruit->set_world_point(j, i);
			all_fruit.push_back(fruit);
			layer->addChild(fruit, 30);
		}
	}
}
Fruit* GameManager::random_fruit(MyPoint myPoint)
{
	int x = myPoint.world_x;
	int y = myPoint.world_y;
	bool x_flag = false;
	MyPoint x_point1;
	MyPoint x_point2;
	if(x - 2 >= 0)
	{
		x_flag = true;
		x_point1 = MyPoint(x - 2, y);
		x_point2 = MyPoint(x - 1, y);
	}
	bool y_flag = false;
	MyPoint y_point1;
	MyPoint y_point2;
	if(y - 2 >= 0)
	{
		y_flag = true;
		y_point1 = MyPoint(x, y - 2);
		y_point2 = MyPoint(x, y - 1);
	}
	int x_type = -1;
	int y_type = -1;
	std::list<Fruit*>::iterator itr;
	for (itr = all_fruit.begin(); itr!=all_fruit.end(); ++itr)
	{
		Fruit* fruit = (Fruit*)*itr;
		if(x_flag)
		{
			if(fruit->world_point == x_point1)
			{
				x_type = fruit->type;
			}
			else if(fruit->world_point == x_point2)
			{
				if(x_type != -1)
				{
					if(fruit->type != x_type)
						x_flag = false;
				}
				else
					x_flag = false;
			}
		}
		if(y_flag)
		{
			if(fruit->world_point == y_point1)
			{
				y_type = fruit->type;
			}
			else if(fruit->world_point == y_point2)
			{
				if(y_type != -1)
				{
					if(fruit->type != y_type)
						y_flag = false;
				}
				else
					y_flag = false;
			}
		}
		
	}
	int _type = rand()%fruit_number;
	int _random = rand()%10;
	if(x_flag)
	{
		if(_type == x_type)
		{
			if(_random > 4)
			{
				_type++;
				if(_type > fruit_number-1)
					_type = 0;
			}
			else
			{
				_type--;
				if(_type < 0)
					_type = fruit_number-1;
			}
		}
	}
	if(y_flag)
	{
		if(_type == y_type)
		{
			if(_random > 4)
			{
				_type++;
				if(_type > fruit_number-1)
					_type = 0;
			}
			else
			{
				_type--;
				if(_type < 0)
					_type = fruit_number-1;
			}
		}
	}
	return Fruit::create(_type);
}

void GameManager::init_map()
{
	for(int i = 0; i < WORLD_HEIGHT; ++i)
	{
		for(int j = 0; j < WORLD_WIDTH; ++j)
		{
			Sprite* tiled = Sprite::createWithSpriteFrameName(Tiled_name);
			tiled->setPosition(Tool::world_to_true(MyPoint(j, i)));
			all_Tiled.push_back(tiled);
		}
	}
}

void GameManager::add_all_tiled(Layer* layer)
{
	std::vector<Sprite*>::iterator itr;
	for(itr = all_Tiled.begin(); itr!=all_Tiled.end(); ++itr)
	{
		layer->addChild(*itr, 10);
	}
}

void GameManager::init_obstacle()
{
	std::vector<Sprite*>::iterator itr;
	MyPoint point;
	for(itr = GameManager::Instance()->all_Tiled.begin(); itr!=GameManager::Instance()->all_Tiled.end(); ++itr)
	{
		Sprite* tiled = (Sprite*)*itr;
		if(!tiled->isVisible())
		{
			point.set_world_point(Tool::true_to_world(tiled->getPosition()));
			all_Obstacle.push_back(point);
		}
	}
}

GameManager* GameManager::manager = nullptr;