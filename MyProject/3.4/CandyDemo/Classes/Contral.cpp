#include "Contral.h"
#include "Manager/Manager.h"
#include "Perf.h"

Contarl::Contarl():finish_anima_fruits(0),fruit(nullptr){}
Contarl::~Contarl(){}

void Contarl::setTouchListener_game1()
{
	listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [=](Touch* touch, Event* event){
		Point touPoint = this->convertToNodeSpace(touch->getLocation());
		Rect rect1(zero_point.x, zero_point.y, WORLD_WIDTH*TILED_WIDTH, WORLD_HEIGHT*TILED_HEIGHT);
		if(rect1.containsPoint(touPoint))
		{
			std::vector<Sprite*>::iterator itr;
			for(itr = Manager::Instance()->all_Tiled.begin(); itr!=Manager::Instance()->all_Tiled.end(); ++itr)
			{
				Sprite* tiled = (Sprite*)*itr;
				Rect rect2(tiled->getPositionX()-TILED_WIDTH/2, tiled->getPositionY()-TILED_HEIGHT/2,
					TILED_WIDTH, TILED_HEIGHT);
				if(rect2.containsPoint(touPoint))
				{
					tiled->setVisible(!tiled->isVisible());
					break;
				}
			}
		}	
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

void Contarl::remove_touch_1()
{
	_eventDispatcher->removeEventListener(listener1);
}

void Contarl::setTouchListener_game2()
{
	listener2 = EventListenerTouchOneByOne::create();
	listener2->setSwallowTouches(true);
	listener2->onTouchBegan = [=](Touch* touch, Event* event){
		if(!Contarl::is_can_touch)
			return true;
		Point touPoint = this->convertToNodeSpace(touch->getLocation());
		Rect rect1(zero_point.x, zero_point.y, WORLD_WIDTH*TILED_WIDTH, WORLD_HEIGHT*TILED_HEIGHT);
		if(rect1.containsPoint(touPoint))
		{
			std::list<Fruit*>::iterator itr;
			std::string name;
			for(itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end(); ++itr)
			{
				this->fruit = (Fruit*)*itr;
				Rect rect2(this->fruit->getPositionX()-TILED_WIDTH/2, this->fruit->getPositionY()-TILED_HEIGHT/2,
					TILED_WIDTH, TILED_HEIGHT);
				if(rect2.containsPoint(touPoint))
				{
					name = this->fruit->getFileName();int index = name.find('.');name.insert(index, "1");
					this->fruit->setDisplayFrame(Manager::Instance()->frames->spriteFrameByName(name));
					break;
				}
			}
		}	
		return true;
	};
	listener2->onTouchMoved = CC_CALLBACK_2(Contarl::changePoint, this);
	listener2->onTouchEnded = [=](Touch* touch, Event* event){
		if (this->fruit)
		{
			this->fruit->setDisplayFrame(Manager::Instance()->frames->spriteFrameByName(this->fruit->getFileName()));
			this->fruit = nullptr;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
}

void Contarl::changePoint(Touch* touch, Event* event)
{
	if(!Contarl::is_can_touch || !fruit)
		return;
	Point touPoint = this->convertToNodeSpace(touch->getLocation());
	Point startPoint = this->convertToNodeSpace(touch->getStartLocation());
	Rect rect1(zero_point.x, zero_point.y, WORLD_WIDTH*TILED_WIDTH, WORLD_HEIGHT*TILED_HEIGHT);
	if (!rect1.containsPoint(startPoint))
		return;
	Rect rect2(this->fruit->getPositionX()-TILED_WIDTH/2, this->fruit->getPositionY()-TILED_HEIGHT/2,
		TILED_WIDTH, TILED_HEIGHT);
	if(!rect2.containsPoint(touPoint))
	{
		float angle = CC_RADIANS_TO_DEGREES((touPoint - fruit->getPosition()).getAngle());
		while(angle < 0)
			angle += 360;
		if(angle > 360)
			angle = ((int)angle) % 360;
		MyPoint point;
		if(angle >= 45 && angle < 135)
			point = MyPoint(fruit->world_point.world_x, fruit->world_point.world_y + 1);
		else if(angle >= 135 && angle < 225)
			point = MyPoint(fruit->world_point.world_x - 1, fruit->world_point.world_y);
		else if(angle >= 225 && angle < 315)
			point = MyPoint(fruit->world_point.world_x, fruit->world_point.world_y - 1);
		else
			point = MyPoint(fruit->world_point.world_x + 1, fruit->world_point.world_y);
		if(point.world_x < 0 || point.world_x > 7 || point.world_y < 0 || point.world_y > 7)
			return;
		std::list<Fruit*>::iterator itr;
		for(itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end(); ++itr)
		{
			Fruit* temp_fruit = (Fruit*)*itr;
			if(temp_fruit->world_point == point)
			{
				fruit->is_user_contact = true;
				temp_fruit->is_user_contact = true;
				temp_fruit->run_to_point(fruit->world_point, false);
				fruit->run_to_point(point, false);
				if (temp_fruit->level == 4 || fruit->level == 4)
				{
					if(temp_fruit->level == 4 && fruit->level == 4)
						add_remove_fruit_for_level_4(nullptr);//消除所有的水果
					else
					{
						if (temp_fruit->level == 4)
						{
							add_remove_fruit_for_level_4(fruit);
							xc_fruits.push_back(temp_fruit);
						}
						else
						{
							add_remove_fruit_for_level_4(temp_fruit);
							xc_fruits.push_back(fruit);
						}
					}
				}
				else
				{
					change_pos_fruits.push_back(fruit);
					change_pos_fruits.push_back(temp_fruit);
				}
				chang_pos_fruit_number = 2;

				Contarl::is_can_touch = false;
				break;
			}
		}
	}
}

bool Contarl::xiao_chu()
{
	Fruit* fruit;
	std::vector<Fruit*>::iterator itr;
	for (itr = change_pos_fruits.begin(); itr!=change_pos_fruits.end(); ++itr)
	{
		fruit = (Fruit*)*itr;
		xiaochu_number(fruit);
	}
	
	if(xc_fruits.size() != 0)
	{
		remove_fruits();
		return true;
	}
	
	return false;
}

int Contarl::xiaochu_number(Fruit* fruit)
{
	cocos2d::Map<int, Fruit*> width_map;
	cocos2d::Map<int, Fruit*> height_map;
	//std::map<int, Fruit*> width_map;
	//std::map<int, Fruit*> height_map;
	std::list<Fruit*>::iterator itr;
	for (itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end(); ++itr)
	{
		Fruit* temp_fruit = (Fruit*)*itr;
		if (temp_fruit->world_point.world_y == fruit->world_point.world_y)
		{
			width_map.insert(temp_fruit->world_point.world_x, temp_fruit);
		}
		if (temp_fruit->world_point.world_x == fruit->world_point.world_x)
		{
			height_map.insert(temp_fruit->world_point.world_y, temp_fruit);
		}
	}

	std::vector<Fruit*> temp_fruits;
	//temp_fruits.push_back(fruit);
	int width_number = 1;
	int height_number = 1;
	int width_cout1 = 0;
	int width_cout2 = 0;
	int height_cout1 = 0;
	int height_cout2 = 0;
	for (int i = fruit->world_point.world_x+1; i < WORLD_WIDTH; ++i)
	{
		Fruit* _fruit = width_map.at(i);
		if(_fruit)
		{
			if (_fruit->type == fruit->type && _fruit->level != 4)
			{
				temp_fruits.push_back(_fruit);
				width_number ++;
				width_cout1++;
			}
			else
				break;
		}
		else
			break;
	}
	for (int i = fruit->world_point.world_x-1; i >= 0; --i)
	{
		Fruit* _fruit = width_map.at(i);
		if(_fruit)
		{
			if (_fruit->type == fruit->type && _fruit->level != 4)
			{
				temp_fruits.push_back(_fruit);
				width_number ++;
				width_cout2++;
			}
			else
				break;
		}
		else
			break;
	}
	temp_fruits.push_back(fruit);
	if (temp_fruits.size() >= 3)
		xc_fruits.insert(xc_fruits.end(), temp_fruits.begin(), temp_fruits.end());
	temp_fruits.clear();

	for (int i = fruit->world_point.world_y+1; i < WORLD_HEIGHT; ++i)
	{
		Fruit* _fruit = height_map.at(i);
		if(_fruit)
		{
			if (_fruit->type == fruit->type && _fruit->level != 4)
			{
				temp_fruits.push_back(_fruit);
				height_number++;
				height_cout1++;
			}
			else
				break;
		}
		else
			break;
	}
	for (int i = fruit->world_point.world_y-1; i >= 0; --i)
	{
		Fruit* _fruit = height_map.at(i);
		if(_fruit)
		{
			if (_fruit->type == fruit->type && _fruit->level != 4)
			{
				temp_fruits.push_back(_fruit);
				height_number++;
				height_cout2++;
			}
			else
				break;
		}
		else
			break;
	}
	temp_fruits.push_back(fruit);
	if (temp_fruits.size() >= 3)
		xc_fruits.insert(xc_fruits.end(), temp_fruits.begin(), temp_fruits.end());
	temp_fruits.clear();
	if(fruit->level == 0)
	{
		if (width_number >= 5 || height_number >= 5)//5连消
		{
			create_level_fruit(4, fruit);
			CCLOG("5连消");
		}
		else if (width_number >= 3 && height_number >= 3)
		{
			if((width_cout1+height_cout1 == 0) || (width_cout1+height_cout2 == 0) || (width_cout2+height_cout1 == 0)
				|| (width_cout2+height_cout2 == 0))//L消除
			{
				create_level_fruit(3, fruit);
			}
			else//T型消
			{
				create_level_fruit(2, fruit);
			}
		}
		else if (width_number >= 4 || height_number >= 4)//4连消
		{
			create_level_fruit(1, fruit);
			CCLOG("4");
		}
	}
	return xc_fruits.size();
}

void Contarl::remove_fruits()
{
	std::vector<Fruit*>::iterator itr;
	for (itr = xc_fruits.begin(); itr != xc_fruits.end(); ++itr)
	{
		Fruit* fruit = (Fruit*)*itr;
		Manager::Instance()->all_fruit.remove(fruit);
		fruit->removeAnima();
		teshu_fruit(fruit);//特殊糖果的处理
	}
	xc_fruits.clear();

	for (itr = xc_more_fruits.begin(); itr != xc_more_fruits.end(); ++itr)
	{
		Fruit* fruit = (Fruit*)*itr;
		Manager::Instance()->all_fruit.remove(fruit);
		fruit->removeAnima();

	}
	xc_more_fruits.clear();
}

void Contarl::teshu_fruit(Fruit* fruit)
{
	switch (fruit->level)
	{
	case 1:
		{
			std::list<Fruit*>::iterator itr;
			if (rand()%10 > 4)
			{
				for (itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end();++itr)
				{
					Fruit* _fruit = (Fruit*)*itr;
					if (_fruit->world_point.world_x == fruit->world_point.world_x)
						xc_more_fruits.push_back(_fruit);
				}
			}
			else
			{
				for (itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end();++itr)
				{
					Fruit* _fruit = (Fruit*)*itr;
					if (_fruit->world_point.world_y == fruit->world_point.world_y)
						xc_more_fruits.push_back(_fruit);
				}
			}
		}
		break;
	case 2:
		{
			std::list<Fruit*>::iterator itr;
			if (rand()%10 > 4)
			{
				for (itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end();++itr)
				{
					Fruit* _fruit = (Fruit*)*itr;
					if (abs(_fruit->world_point.world_x - fruit->world_point.world_x) <= 1)
						xc_more_fruits.push_back(_fruit);
				}
			}
			else
			{
				for (itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end();++itr)
				{
					Fruit* _fruit = (Fruit*)*itr;
					if (abs(_fruit->world_point.world_y - fruit->world_point.world_y) <= 1)
						xc_more_fruits.push_back(_fruit);
				}
			}
		}
		break;
	case 3:
		{
			std::list<Fruit*>::iterator itr;
			for (itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end();++itr)
			{
				Fruit* _fruit = (Fruit*)*itr;
				if (abs(_fruit->world_point.world_y - fruit->world_point.world_y) <= 3 
					&& abs(_fruit->world_point.world_x - fruit->world_point.world_x) <= 3)
					xc_more_fruits.push_back(_fruit);
			}
		}
		break;
	default:
		break;
	}
}

void Contarl::update(float dt)
{
	if (finish_anima_fruits == chang_pos_fruit_number && finish_anima_fruits != 0)
	{			
		if(xiao_chu())
		{
			fruit = nullptr;
		}
		else
		{
			if(finish_anima_fruits == 2 && change_pos_fruits[0]->is_user_contact && change_pos_fruits[1]->is_user_contact)
			{
				MyPoint point1 = (*change_pos_fruits.at(0)).world_point;
				MyPoint point2 = (*change_pos_fruits.at(1)).world_point;
				change_pos_fruits[0]->run_to_point(point2, true);
				change_pos_fruits[1]->run_to_point(point1, true);
			}
		}
		std::vector<Fruit*>::iterator itr;
		for (itr = change_pos_fruits.begin(); itr!=change_pos_fruits.end(); ++itr)
		{
			((Fruit*)*itr)->is_user_contact = false;
		}
		finish_anima_fruits = 0;
		change_pos_fruits.clear();
		chang_pos_fruit_number = 0;
	}

}

void Contarl::create_level_fruit(int _level, Fruit* fruit)
{
	Fruit *_fruit = Fruit::create(fruit->type);
	_fruit->level_up(_level);
	_fruit->set_world_point(fruit->world_point.world_x, fruit->world_point.world_y);
	addChild(_fruit, 30);
	Manager::Instance()->all_fruit.push_back(_fruit);
}

void Contarl::add_remove_fruit_for_level_4(Fruit* fruit)
{
	if (fruit)//消除地图所有相同类型的水果
	{
		int _type = fruit->type;
		std::list<Fruit*>::iterator itr;
		for (itr = Manager::Instance()->all_fruit.begin(); itr != Manager::Instance()->all_fruit.end(); )
		{
			Fruit* _fruit = (Fruit*)*itr;
			if(_type == _fruit->type && _fruit->level != 4)
			{
				xc_fruits.push_back(_fruit);
				itr = Manager::Instance()->all_fruit.erase(itr);
			}
			else
				++itr;
		}
	}
	else//消除所有的水果
	{
		xc_fruits.insert(xc_fruits.end(), Manager::Instance()->all_fruit.begin(), Manager::Instance()->all_fruit.end());
		Manager::Instance()->all_fruit.clear();
	}
}

bool Contarl::is_can_touch = true;