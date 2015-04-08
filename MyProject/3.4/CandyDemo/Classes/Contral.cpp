#include "Contral.h"
#include "Manager/Manager.h"
#include "Perf.h"
#include "Tool.h"

Contarl::Contarl():finish_anima_fruits(0),touch_fruit(nullptr),isMove(false),changePos(false),check_number(0),is_touch_move(true){}
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
		if(!Contarl::is_can_touch || touch_fruit ||!is_touch_move)
			return false;
		Point touPoint = this->convertToNodeSpace(touch->getLocation());
		Rect rect1(zero_point.x, zero_point.y, WORLD_WIDTH*TILED_WIDTH, WORLD_HEIGHT*TILED_HEIGHT);
		if(rect1.containsPoint(touPoint))
		{
			std::list<Fruit*>::iterator itr;
			std::string name;
			for(itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end(); ++itr)
			{
				Fruit* t_ftuit = (Fruit*)*itr;
				if(t_ftuit->getActionByTag(1) != nullptr)
					return true;
				Rect rect2(t_ftuit->getPositionX()-TILED_WIDTH/2, t_ftuit->getPositionY()-TILED_HEIGHT/2,
					TILED_WIDTH, TILED_HEIGHT);
				if(rect2.containsPoint(touPoint))
				{
					this->touch_fruit = t_ftuit;
					name = this->touch_fruit->getFileName();int index = name.find('.');name.insert(index, "1");
					this->touch_fruit->setDisplayFrame(Manager::Instance()->frames->spriteFrameByName(name));
					break;
				}
			}
		}	
		return true;
	};
	listener2->onTouchMoved = CC_CALLBACK_2(Contarl::changePoint, this);
	listener2->onTouchEnded = [=](Touch* touch, Event* event){
		if (this->touch_fruit)
		{
			this->touch_fruit->setDisplayFrame(Manager::Instance()->frames->spriteFrameByName(this->touch_fruit->getFileName()));
			this->touch_fruit = nullptr;
			is_touch_move = true;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
}

void Contarl::changePoint(Touch* touch, Event* event)
{
	if(!Contarl::is_can_touch || !touch_fruit)
		return;
	Point touPoint = this->convertToNodeSpace(touch->getLocation());
	Point startPoint = this->convertToNodeSpace(touch->getStartLocation());
	Rect rect1(zero_point.x, zero_point.y, WORLD_WIDTH*TILED_WIDTH, WORLD_HEIGHT*TILED_HEIGHT);
	if (!rect1.containsPoint(startPoint))
		return;
	Rect rect2(this->touch_fruit->getPositionX()-TILED_WIDTH/2, this->touch_fruit->getPositionY()-TILED_HEIGHT/2,
		TILED_WIDTH, TILED_HEIGHT);
	if(!rect2.containsPoint(touPoint))
	{
		float angle = CC_RADIANS_TO_DEGREES((touPoint - touch_fruit->getPosition()).getAngle());
		while(angle < 0)
			angle += 360;
		if(angle > 360)
			angle = ((int)angle) % 360;
		MyPoint point;
		if(angle >= 45 && angle < 135)
			point = MyPoint(touch_fruit->world_point.world_x, touch_fruit->world_point.world_y + 1);
		else if(angle >= 135 && angle < 225)
			point = MyPoint(touch_fruit->world_point.world_x - 1, touch_fruit->world_point.world_y);
		else if(angle >= 225 && angle < 315)
			point = MyPoint(touch_fruit->world_point.world_x, touch_fruit->world_point.world_y - 1);
		else
			point = MyPoint(touch_fruit->world_point.world_x + 1, touch_fruit->world_point.world_y);
		if(point.world_x < 0 || point.world_x > 7 || point.world_y < 0 || point.world_y > 7)
			return;
		std::list<Fruit*>::iterator itr;
		for(itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end(); ++itr)
		{
			Fruit* temp_fruit = (Fruit*)*itr;
			if(temp_fruit->world_point == point && temp_fruit->getActionByTag(1) == nullptr)
			{
				touch_fruit->is_user_contact = true;
				temp_fruit->is_user_contact = true;
				temp_fruit->run_to_point(touch_fruit->world_point, false);
				touch_fruit->run_to_point(point, false);
				if (temp_fruit->level == 4 || touch_fruit->level == 4)
				{
					if(temp_fruit->level == 4 && touch_fruit->level == 4)
						add_remove_fruit_for_level_4(nullptr);//消除所有的水果
					else
					{
						if (temp_fruit->level == 4)
						{
							add_remove_fruit_for_level_4(touch_fruit);
							xc_fruits.push_back(temp_fruit);
						}
						else
						{
							add_remove_fruit_for_level_4(temp_fruit);
							xc_fruits.push_back(touch_fruit);
						}
					}
				}
				else
				{
					change_pos_fruits.push_back(touch_fruit);
					change_pos_fruits.push_back(temp_fruit);
				}
				chang_pos_fruit_number = 2;

				Contarl::is_can_touch = false;
				is_touch_move = false;
				//listener2->setEnabled(false);
				if (this->touch_fruit)
				{
					this->touch_fruit->setDisplayFrame(Manager::Instance()->frames->spriteFrameByName(this->touch_fruit->getFileName()));
					//this->touch_fruit = nullptr;
				}
				return;
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
	{
		std::vector<Fruit*>::iterator itr;
		for (itr = temp_fruits.begin(); itr != temp_fruits.end(); ++itr)
		{
			if(find(xc_fruits.begin(), xc_fruits.end(), *itr) == xc_fruits.end())
				xc_fruits.push_back(*itr);
		}
	}
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
	{
		std::vector<Fruit*>::iterator itr;
		for (itr = temp_fruits.begin(); itr != temp_fruits.end(); ++itr)
		{
			if(find(xc_fruits.begin(), xc_fruits.end(), *itr) == xc_fruits.end())
				xc_fruits.push_back(*itr);
		}
		//xc_fruits.insert(xc_fruits.end(), temp_fruits.begin(), temp_fruits.end());
	}
	temp_fruits.clear();
	if (check_number < xc_fruits.size())
	{
		if(fruit->level == 0)
		{
			if (width_number >= 5 || height_number >= 5)//5连消
			{
				add_teshu_fruit.push_back(create_level_fruit(4, fruit));
				CCLOG("5连消");
			}
			else if (width_number >= 3 && height_number >= 3)
			{
				if((width_cout1+height_cout1 == 0) || (width_cout1+height_cout2 == 0) || (width_cout2+height_cout1 == 0)
					|| (width_cout2+height_cout2 == 0))//L消除
				{
					add_teshu_fruit.push_back(create_level_fruit(3, fruit));
				}
				else//T型消
				{
					add_teshu_fruit.push_back(create_level_fruit(2, fruit));
				}
			}
			else if (width_number >= 4 || height_number >= 4)//4连消
			{
				add_teshu_fruit.push_back(create_level_fruit(1, fruit));
				CCLOG("4");
			}
		}
	}
	check_number = xc_fruits.size();
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
		if(find(xc_more_points.begin(), xc_more_points.end(), fruit->world_point) == xc_more_points.end()
			&& find(xc_points.begin(), xc_points.end(), fruit->world_point) == xc_points.end())
			xc_points.push_back(fruit->world_point);
	}
	xc_fruits.clear();

	for (itr = xc_more_fruits.begin(); itr != xc_more_fruits.end(); ++itr)
	{
		Fruit* fruit = (Fruit*)*itr;
		Manager::Instance()->all_fruit.remove(fruit);
		fruit->removeAnima();
		if(find(xc_more_points.begin(), xc_more_points.end(), fruit->world_point) == xc_more_points.end()
			&& find(xc_points.begin(), xc_points.end(), fruit->world_point) == xc_points.end())
			xc_points.push_back(fruit->world_point);

	}

	for (itr = add_teshu_fruit.begin(); itr != add_teshu_fruit.end(); ++itr)
	{
		addChild(*itr, 30);
		Manager::Instance()->all_fruit.push_back(*itr);
	}

	add_teshu_fruit.clear();
	xc_more_fruits.clear();
	xc_more_points.clear();
	check_number = 0;
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
					if(_fruit->level > 0 && _fruit != fruit 
						&& find(xc_more_fruits.begin(), xc_more_fruits.end(), _fruit) == xc_more_fruits.end())
						teshu_fruit(_fruit);
				}
			}
			else
			{
				for (itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end();++itr)
				{
					Fruit* _fruit = (Fruit*)*itr;
					if (_fruit->world_point.world_y == fruit->world_point.world_y)
						xc_more_fruits.push_back(_fruit);
					if(_fruit->level > 0 && _fruit != fruit
						&& find(xc_more_fruits.begin(), xc_more_fruits.end(), _fruit) == xc_more_fruits.end())
						teshu_fruit(_fruit);
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
					if(_fruit->level > 0 && _fruit != fruit
						&& find(xc_more_fruits.begin(), xc_more_fruits.end(), _fruit) == xc_more_fruits.end())
						teshu_fruit(_fruit);
				}
			}
			else
			{
				for (itr = Manager::Instance()->all_fruit.begin(); itr!=Manager::Instance()->all_fruit.end();++itr)
				{
					Fruit* _fruit = (Fruit*)*itr;
					if (abs(_fruit->world_point.world_y - fruit->world_point.world_y) <= 1)
						xc_more_fruits.push_back(_fruit);
					if(_fruit->level > 0 && _fruit != fruit
						&& find(xc_more_fruits.begin(), xc_more_fruits.end(), _fruit) == xc_more_fruits.end())
						teshu_fruit(_fruit);
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
				if (abs(_fruit->world_point.world_y - fruit->world_point.world_y) <= 2 
					&& abs(_fruit->world_point.world_x - fruit->world_point.world_x) <= 2)
					xc_more_fruits.push_back(_fruit);
				if(_fruit->level > 0 && _fruit != fruit
					&& find(xc_more_fruits.begin(), xc_more_fruits.end(), _fruit) == xc_more_fruits.end())
					teshu_fruit(_fruit);
			}
		}
		break;
	default:
		break;
	}
}

void Contarl::create_new_fruits()
{
	isMove = true;
	std::list<Fruit*>::iterator itr1;
	std::vector<MyPoint>::iterator itr2;
	for (itr1 = Manager::Instance()->all_fruit.begin(); itr1 != Manager::Instance()->all_fruit.end(); ++itr1)
	{
		Fruit* _fruit = (Fruit*)*itr1;
		for (itr2 = xc_points.begin(); itr2 != xc_points.end(); ++itr2)
		{
			MyPoint point = (MyPoint)*itr2;
			if(_fruit->world_point.world_x == point.world_x)
			{
				if(_fruit->world_point.world_y >= point.world_y)
				{
					_fruit->open_move();
					change_pos_fruits.push_back(_fruit);
					break;
				}
			}
		}
	}

	std::map<int, int> heightest;//最高障碍物的Y坐标
	std::vector<MyPoint>::iterator itr3;
	for (itr3 = Manager::Instance()->all_Obstacle.begin(); itr3 != Manager::Instance()->all_Obstacle.end(); ++itr3)
	{
		MyPoint obs_point = (MyPoint)*itr3;
		if(heightest.find(obs_point.world_x) == heightest.end())
			heightest[obs_point.world_x] = obs_point.world_y;
		else
		{
			if(heightest[obs_point.world_x] < obs_point.true_y)
				heightest[obs_point.world_x] = obs_point.world_y;
		}

	}
	std::map<int, int> map;
	for (int i = 0; i < WORLD_WIDTH; ++i)
	{
		map[i] = WORLD_HEIGHT;
	}
	for (itr2 = xc_points.begin(); itr2 != xc_points.end(); ++itr2)
	{
		
		MyPoint point = (MyPoint)*itr2;
		if(heightest.find(point.world_x) != heightest.end() && heightest[point.world_x] > point.world_y)
			continue;
		Fruit* new_fruit = Fruit::create(rand()%5);
		new_fruit->set_world_point(point.world_x, map[point.world_x]++);
		new_fruit->open_move();
		this->addChild(new_fruit, 30);
		change_pos_fruits.push_back(new_fruit);
		Manager::Instance()->all_fruit.push_back(new_fruit);
	}
	xc_points.clear();

}

void Contarl::update(float dt)
{
	if (finish_anima_fruits == chang_pos_fruit_number && finish_anima_fruits != 0)
	{			
		if(xiao_chu() || xc_points.size() != 0)
		{
			std::vector<Fruit*>::iterator itr;
			for (itr = change_pos_fruits.begin(); itr!=change_pos_fruits.end(); ++itr)
			{
				((Fruit*)*itr)->is_user_contact = false;
			}
			change_pos_fruits.clear();
			touch_fruit = nullptr;
			create_new_fruits();
			
		}
		else
		{
			if(finish_anima_fruits == 2 && change_pos_fruits[0]->is_user_contact && change_pos_fruits[1]->is_user_contact)
			{
				MyPoint point1 = (*change_pos_fruits.at(0)).world_point;
				MyPoint point2 = (*change_pos_fruits.at(1)).world_point;
				change_pos_fruits[0]->run_to_point(point2, true);
				change_pos_fruits[1]->run_to_point(point1, true);
				Contarl::is_can_touch = false;
				//listener2->setEnabled(false);
			}
			std::vector<Fruit*>::iterator itr;
			for (itr = change_pos_fruits.begin(); itr!=change_pos_fruits.end(); ++itr)
			{
				((Fruit*)*itr)->is_user_contact = false;
			}
			change_pos_fruits.clear();
			CCLOG("ss");
			if(!is_change_x())
			{
				Contarl::is_can_touch = true;
				//listener2->setEnabled(true);
			}
			else
			{
				Contarl::is_can_touch = false;
				//listener2->setEnabled(false);
			}
		}
		chang_pos_fruit_number = change_pos_fruits.size();
		finish_anima_fruits = 0;	
	}

	if(isMove)
	{
		bool flag = true;
		std::vector<Fruit*>::iterator itr;
		for (itr = change_pos_fruits.begin(); itr!=change_pos_fruits.end(); ++itr)
		{
			Fruit*_fruit = (Fruit*)*itr;
			if(_fruit->isMove)
			{
				flag = false;
				if(!_fruit->is_change_pos)
				{
					_fruit->speed += Gravity*dt;
					_fruit->setPosition(_fruit->getPositionX(), _fruit->getPositionY() - _fruit->speed);
					_fruit->updatePoint();
				}			
				
				if(_fruit->getPositionY() < _fruit->world_point.true_y)
				{
					if(_fruit->getPositionY() < zero_point.y + TILED_HEIGHT/2)
					{
						_fruit->off_move();
						_fruit->set_world_point(_fruit->world_point.world_x, 0);
					}
					else
					{
						bool flag2 = true;
						std::list<Fruit*>::iterator itr1;
						for (itr1 = Manager::Instance()->all_fruit.begin(); itr1 != Manager::Instance()->all_fruit.end(); ++itr1)
						{
							Fruit* fruit = (Fruit*)*itr1;
							if(fruit->world_point.world_x == _fruit->world_point.world_x 
								&& _fruit->world_point.world_y - fruit->world_point.world_y == 1)
							{
								flag2 = false;
								if (!fruit->isMove)
								{
									_fruit->off_move();
									_fruit->set_world_point(fruit->world_point.world_x, fruit->world_point.world_y+1);
								}
								break;
							}
						}
						if(flag2)//如果上面代码在下方没找到水果就判断下方是否有阻挡物
						{
							std::vector<MyPoint>::iterator itr2;
							for (itr2 = Manager::Instance()->all_Obstacle.begin(); itr2 != Manager::Instance()->all_Obstacle.end(); ++itr2)
							{
								MyPoint obs_point = (MyPoint)*itr2;
								if(_fruit->world_point.world_x == obs_point.world_x && 
									_fruit->world_point.world_y - obs_point.world_y == 1)	
								{
									_fruit->off_move();
									_fruit->set_world_point(_fruit->world_point.world_x, obs_point.world_y+1);
									break;
								}
							}
						}
					}
				}
			}
			
		}
		
		if(flag)
		{
			isMove = false;	
			finish_anima_fruits = chang_pos_fruit_number = change_pos_fruits.size();

		}
	}

	

}

bool Contarl::is_change_x()
{
	std::list<Fruit*>::iterator itr1;
	std::list<Fruit*>::iterator itr2;
	std::vector<MyPoint>::iterator itr3;
	std::map<int, MyPoint> points;
	std::map<int, Fruit*> max_height_fruit;
	for (itr1 = Manager::Instance()->all_fruit.begin(); itr1 != Manager::Instance()->all_fruit.end(); ++itr1)
	{
	 	Fruit* fruit = (Fruit*)*itr1;
		if(fruit->isMove || fruit->world_point.world_y == 0)
			continue;
		MyPoint point1 = MyPoint(fruit->world_point.world_x - 1, fruit->world_point.world_y - 1);
		MyPoint point2 = MyPoint(fruit->world_point.world_x + 1, fruit->world_point.world_y - 1);

		bool flag_1 = true;
		bool flag_2 = true;
		int i = 0;
		int j = 0;
		for (itr3 = Manager::Instance()->all_Obstacle.begin(); itr3 != Manager::Instance()->all_Obstacle.end(); ++ itr3)
		{
			MyPoint _point = (MyPoint)*itr3;
			if(_point.world_x == point1.world_x && flag_1)
			{
				i++;
				if(_point.world_y == point1.world_y)
					flag_1 = false;
			}
			if(_point.world_x == point2.world_x && flag_2)
			{
				j++;
				if(_point.world_y == point2.world_y)
					flag_2 = false;
			}
			if(!flag_1 && !flag_2)
				break;
		}
		if(i == 0)
			flag_1 = false;
		if(j == 0)
			flag_2 = false;

		if(!flag_1 && !flag_2)
			continue;
		
		for (itr2 = Manager::Instance()->all_fruit.begin(); itr2 != Manager::Instance()->all_fruit.end(); ++itr2)
		{
			Fruit* _fruit = (Fruit*)*itr2;
			if(_fruit->world_point == point1)
				flag_1 = false;
			if(_fruit->world_point == point2)
				flag_2 = false;
			if(!flag_1 && !flag_2)
				break;
		}
		if(!flag_1 && !flag_2)
			continue;
		if (flag_1 && (point1.world_x >= 0 && point1.world_x <= WORLD_WIDTH-1))
		{
			if(max_height_fruit.find(fruit->world_point.world_x) == max_height_fruit.end())
			{
				max_height_fruit[fruit->world_point.world_x] = fruit;
				points[fruit->world_point.world_x] = point1;
			}
			else
			{
				if(max_height_fruit[fruit->world_point.world_x]->world_point.world_y < fruit->world_point.world_y)
				{
					max_height_fruit[fruit->world_point.world_x] = fruit;
					points[fruit->world_point.world_x] = point1;
				}
			}
		}
		else if (flag_2 && (point2.world_x >= 0 && point2.world_x <= WORLD_WIDTH-1))
		{
			if(max_height_fruit.find(fruit->world_point.world_x) == max_height_fruit.end())
			{
				max_height_fruit[fruit->world_point.world_x] = fruit;
				points[fruit->world_point.world_x] = point2;
			}
			else
			{
				if(max_height_fruit[fruit->world_point.world_x]->world_point.world_y < fruit->world_point.world_y)
				{
					max_height_fruit[fruit->world_point.world_x] = fruit;
					points[fruit->world_point.world_x] = point2;
				}
			}
		}
	}
	std::vector<MyPoint> set_point;
	std::map<int, Fruit*>::iterator map_itr;
	for (map_itr = max_height_fruit.begin(); map_itr != max_height_fruit.end(); ++map_itr)
	{
		Fruit* _fruit = map_itr->second;
		if(find(set_point.begin(), set_point.end(), points[map_itr->first]) != set_point.end())
			continue;
		xc_points.push_back(MyPoint(_fruit->world_point));
		_fruit->change_x_pos(points[map_itr->first]);
		set_point.push_back(points[map_itr->first]);
		//_fruit->set_world_point(points[map_itr->first].world_x, points[map_itr->first].world_y);
		change_pos_fruits.push_back(_fruit);
		_fruit->open_move();
	}
	if(max_height_fruit.size() != 0)
	{
		//isMove = true;
		finish_anima_fruits = chang_pos_fruit_number = change_pos_fruits.size();
		return true;
	}
	else
		return false;
}

Fruit* Contarl::create_level_fruit(int _level, Fruit* fruit)
{
	Fruit *_fruit = Fruit::create(fruit->type);
	_fruit->level_up(_level);
	_fruit->set_world_point(fruit->world_point.world_x, fruit->world_point.world_y);
	//addChild(_fruit, 30);
	//Manager::Instance()->all_fruit.push_back(_fruit);
	xc_more_points.push_back(_fruit->world_point);
	return _fruit;
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