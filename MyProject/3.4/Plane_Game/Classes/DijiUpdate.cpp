#include "DijiUpdate.h"
#include "DiJiSprite.h"
#include "GameScene.h"
#include <Box2D\Box2D.h>


void DijiUpdate::diJiUpdate(float dt, cocos2d::Layer* _layer)
{
	GameScene* layer = (GameScene*)_layer;
	if(timeSum < 2)
	{
		timeSum += dt;
		return;
	}
	switch(layer->getGK())
	{
	case 1:
		update1(dt, _layer);
		break;
	case 2:
		update2(dt, _layer);
		break;
	case 3:
		update3(dt, _layer);
		break;
	case 4:
		update4(dt, _layer);
		break;
	default:
		break;
	}
	updateDiji(dt, _layer);
}

void DijiUpdate::updateDiji(float dt, cocos2d::Layer* _layer)
{
	GameScene* layer = (GameScene*)_layer;
	if(layer->diJis.size() > 0)
	{
		std::list<b2Body*>::iterator itr;
		for(itr = layer->diJis.begin(); itr != layer->diJis.end(); ++itr)
		{
			b2Body *dijiBody = (b2Body*)*itr;
			DiJiSprite *diji = (DiJiSprite*)dijiBody->GetUserData();
			diji->updateShutPoint();
			diji->shut_Bullet(dt);
			if(diji->changeAngleRect.containsPoint(diji->getPosition())&&diji->flag)
			{			
				diji->isChange = true;
			}
			if(diji->isChange)
			{
				if(diji->addAngle >= 0)
				{
					float angle = CC_RADIANS_TO_DEGREES(dijiBody->GetAngle());
						while(angle < 0)
							angle += 360;
						if(angle > 360)
							angle = ((int)angle) % 360;
					if(CC_RADIANS_TO_DEGREES(dijiBody->GetAngle()) < diji->addAngle+3 && CC_RADIANS_TO_DEGREES(dijiBody->GetAngle()) > diji->addAngle-3)
					{
						dijiBody->SetAngularVelocity(0);
						dijiBody->SetTransform(dijiBody->GetPosition(), CC_DEGREES_TO_RADIANS(diji->addAngle));
						diji->isChange = false;
						diji->flag = false;
						float ration = dijiBody->GetAngle();
						dijiBody->SetLinearVelocity(b2Vec2(diji->veclecty*cos(ration), diji->veclecty*sin(ration)));
					}
					else
					{
						if(angle > diji->addAngle)
						{
							if(angle - diji->addAngle < 180)
								dijiBody->SetAngularVelocity(-(float)DIJI_RATION_SPEED*dt);	
							else
								dijiBody->SetAngularVelocity((float)DIJI_RATION_SPEED*dt);
						}
						else
						{
							if(diji->addAngle - angle < 180)
								dijiBody->SetAngularVelocity((float)DIJI_RATION_SPEED*dt);	
							else
								dijiBody->SetAngularVelocity(-(float)DIJI_RATION_SPEED*dt);
						}
						float ration = dijiBody->GetAngle();
						dijiBody->SetLinearVelocity(b2Vec2(diji->veclecty*cos(ration), diji->veclecty*sin(ration)));
					}
				}
				else
				{
					dijiBody->SetLinearVelocity(b2Vec2(0, 0));
					diji->isChange = false;
					diji->flag = false;
				}
			}
		}
	}
}
void DijiUpdate::update1(float dt, cocos2d::Layer* _layer)
{
	GameScene* layer = (GameScene*)_layer;
	if(number < 8)
	{
		if(!hasDji(layer->diJis))
		{
			number++;
			switch(number)
			{
			case 1:
				layer->createDiJi(Point(540, 1200), 0, Point(540, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(430, 1200), 1, Point(430, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(100, 1200), 0, Point(100, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(210, 1200), 1, Point(330, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 2:
				layer->createDiJi(Point(320, 1200), 2, Point(320, 800), 5, -1, 2);
				layer->createDiJi(Point(540, 1200), 0, Point(-500, -500), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(100, 1200), 0, Point(1460, -500), 6, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 3:
				layer->createDiJi(Point(320, 1100), 2, Point(320, 800), 5, -1, 2);
				layer->createDiJi(Point(100, 1299), 1, Point(100, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(200, 1299), 1, Point(200, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(300, 1299), 1, Point(300, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(400, 1299), 1, Point(400, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(500, 1299), 1, Point(500, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 4:
				layer->createDiJi(Point(320, 1200), 2, Point(320, 700), 5, -1, 2);
				layer->createDiJi(Point(100, 1200), 2, Point(100, 700), 2, -1, 5);
				layer->createDiJi(Point(540, 1200), 2, Point(540, 700), 2, -1, 5);
				break;
			case 5:
				layer->createDiJi(Point(320, 1200), 3, Point(320, 800), 4, -1, 3);
				layer->createDiJi(Point(100, 1299), 1, Point(100, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(200, 1299), 1, Point(200, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(300, 1299), 1, Point(300, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(400, 1299), 1, Point(400, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(500, 1299), 1, Point(500, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 6:
				layer->createDiJi(Point(150, 1200), 3, Point(150, 800), 4, -1, 3);
				layer->createDiJi(Point(490, 1200), 3, Point(490, 800), 4, -1, 3);
				break;
			case 7:
				layer->createDiJi(Point(320, 1200), 3, Point(320, 800), 4, -1, 3);
				layer->createDiJi(Point(150, 1200), 2, Point(150, 800), 5, -1, 3);
				layer->createDiJi(Point(490, 1200), 2, Point(490, 800), 5, -1, 3);
				break;
			case 8:
				layer->scheduleOnce(schedule_selector(GameScene::boss_come), 2);
				break;

			default:
				break;
			}
		}
		if(number <= 7)//小于第六波才会刷随机飞机
		{
			coutTime += dt;
			if(coutTime >= 6)//随机飞机出现计时器
			{
				coutTime = 0;
				randomCreateDiJi(layer);
			}
		}
	}
}

void DijiUpdate::update2(float dt, cocos2d::Layer* _layer)
{
	GameScene* layer = (GameScene*)_layer;
	if(number < 8)
	{
		if(!hasDji(layer->diJis))
		{
			number++;
			switch(number)
			{
			case 1:
				layer->createDiJi(Point(540, 1200), 0, Point(540, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(430, 1200), 1, Point(430, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(100, 1200), 0, Point(100, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(210, 1200), 1, Point(210, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 2:
				layer->createDiJi(Point(320, 1200), 2, Point(320, 800), 5, -1, 2);
				layer->createDiJi(Point(540, 1200), 0, Point(-500, -500), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(100, 1200), 0, Point(1460, -500), 6, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 3:
				layer->createDiJi(Point(320, 1100), 2, Point(320, 800), 5, -1, 2);
				layer->createDiJi(Point(100, 1299), 1, Point(100, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(200, 1299), 1, Point(200, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(300, 1299), 1, Point(300, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(400, 1299), 1, Point(400, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(500, 1299), 1, Point(500, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 4:
				layer->createDiJi(Point(320, 1200), 2, Point(320, 700), 5, -1, 2);
				layer->createDiJi(Point(100, 1200), 2, Point(100, 700), 2, -1, 5);
				layer->createDiJi(Point(540, 1200), 2, Point(540, 700), 2, -1, 5);
				break;
			case 5:
				layer->createDiJi(Point(320, 1200), 3, Point(320, 800), 4, -1, 3);
				layer->createDiJi(Point(100, 1299), 1, Point(100, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(200, 1299), 1, Point(200, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(300, 1299), 1, Point(300, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(400, 1299), 1, Point(400, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(500, 1299), 1, Point(500, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 6:
				layer->createDiJi(Point(150, 1200), 3, Point(150, 800), 4, -1, 3);
				layer->createDiJi(Point(490, 1200), 3, Point(490, 800), 4, -1, 3);
				break;
			case 7:
				layer->createDiJi(Point(320, 1200), 3, Point(320, 800), 4, -1, 3);
				layer->createDiJi(Point(150, 1200), 2, Point(150, 800), 5, -1, 3);
				layer->createDiJi(Point(490, 1200), 2, Point(490, 800), 5, -1, 3);
				break;
			case 8:
				layer->scheduleOnce(schedule_selector(GameScene::boss_come), 2);
				break;

			default:
				break;
			}
		}
		if(number <= 7)//小于第六波才会刷随机飞机
		{
			coutTime += dt;
			if(coutTime >= 6)//随机飞机出现计时器
			{
				coutTime = 0;
				randomCreateDiJi(layer);
			}
		}
	}
}
void DijiUpdate::update3(float dt, cocos2d::Layer* _layer)
{
	GameScene* layer = (GameScene*)_layer;
	if(number < 8)
	{
		if(!hasDji(layer->diJis))
		{
			number++;
			switch(number)
			{
			case 1:
				layer->createDiJi(Point(540, 1200), 0, Point(540, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(430, 1200), 1, Point(430, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(100, 1200), 0, Point(100, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(210, 1200), 1, Point(210, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 2:
				layer->createDiJi(Point(320, 1200), 2, Point(320, 800), 5, -1, 2);
				layer->createDiJi(Point(540, 1200), 0, Point(-500, -500), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(100, 1200), 0, Point(1460, -500), 6, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 3:
				layer->createDiJi(Point(320, 1100), 2, Point(320, 800), 5, -1, 2);
				layer->createDiJi(Point(100, 1299), 1, Point(100, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(200, 1299), 1, Point(200, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(300, 1299), 1, Point(300, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(400, 1299), 1, Point(400, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(500, 1299), 1, Point(500, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 4:
				layer->createDiJi(Point(320, 1200), 2, Point(320, 700), 5, -1, 2);
				layer->createDiJi(Point(100, 1200), 2, Point(100, 700), 2, -1, 5);
				layer->createDiJi(Point(540, 1200), 2, Point(540, 700), 2, -1, 5);
				break;
			case 5:
				layer->createDiJi(Point(320, 1200), 3, Point(320, 800), 4, -1, 3);
				layer->createDiJi(Point(100, 1299), 1, Point(100, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(200, 1299), 1, Point(200, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(300, 1299), 1, Point(300, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(400, 1299), 1, Point(400, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(500, 1299), 1, Point(500, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 6:
				layer->createDiJi(Point(150, 1200), 3, Point(150, 800), 4, -1, 3);
				layer->createDiJi(Point(490, 1200), 3, Point(490, 800), 4, -1, 3);
				break;
			case 7:
				layer->createDiJi(Point(320, 1200), 3, Point(320, 800), 4, -1, 3);
				layer->createDiJi(Point(150, 1200), 2, Point(150, 800), 5, -1, 3);
				layer->createDiJi(Point(490, 1200), 2, Point(490, 800), 5, -1, 3);
				break;
			case 8:
				layer->scheduleOnce(schedule_selector(GameScene::boss_come), 2);
				break;

			default:
				break;
			}
		}
		if(number <= 7)//小于第六波才会刷随机飞机
		{
			coutTime += dt;
			if(coutTime >= 6)//随机飞机出现计时器
			{
				coutTime = 0;
				randomCreateDiJi(layer);
			}
		}
	}
}
void DijiUpdate::update4(float dt, cocos2d::Layer* _layer)
{
	GameScene* layer = (GameScene*)_layer;
	if(number < 8)
	{
		if(!hasDji(layer->diJis))
		{
			number++;
			switch(number)
			{
			case 1:
				layer->createDiJi(Point(540, 1200), 0, Point(540, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(430, 1200), 1, Point(430, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(100, 1200), 0, Point(100, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(210, 1200), 1, Point(210, -700), 9, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 2:
				layer->createDiJi(Point(320, 1200), 2, Point(320, 800), 5, -1, 2);
				layer->createDiJi(Point(540, 1200), 0, Point(-500, -500), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(100, 1200), 0, Point(1460, -500), 6, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 3:
				layer->createDiJi(Point(320, 1100), 2, Point(320, 800), 5, -1, 2);
				layer->createDiJi(Point(100, 1299), 1, Point(100, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(200, 1299), 1, Point(200, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(300, 1299), 1, Point(300, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(400, 1299), 1, Point(400, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(500, 1299), 1, Point(500, -700), 6, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 4:
				layer->createDiJi(Point(320, 1200), 2, Point(320, 700), 5, -1, 2);
				layer->createDiJi(Point(100, 1200), 2, Point(100, 700), 2, -1, 5);
				layer->createDiJi(Point(540, 1200), 2, Point(540, 700), 2, -1, 5);
				break;
			case 5:
				layer->createDiJi(Point(320, 1200), 3, Point(320, 800), 4, -1, 3);
				layer->createDiJi(Point(100, 1299), 1, Point(100, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(200, 1299), 1, Point(200, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(300, 1299), 1, Point(300, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(400, 1299), 1, Point(400, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				layer->createDiJi(Point(500, 1299), 1, Point(500, -700), 7, -1, 1+rand()%3+0.1*(rand()%10));
				break;
			case 6:
				layer->createDiJi(Point(150, 1200), 3, Point(150, 800), 4, -1, 3);
				layer->createDiJi(Point(490, 1200), 3, Point(490, 800), 4, -1, 3);
				break;
			case 7:
				layer->createDiJi(Point(320, 1200), 3, Point(320, 800), 4, -1, 3);
				layer->createDiJi(Point(150, 1200), 2, Point(150, 800), 5, -1, 3);
				layer->createDiJi(Point(490, 1200), 2, Point(490, 800), 5, -1, 3);
				break;
			case 8:
				layer->scheduleOnce(schedule_selector(GameScene::boss_come), 2);
				break;

			default:
				break;
			}
		}
		if(number <= 7)//小于第六波才会刷随机飞机
		{
			coutTime += dt;
			if(coutTime >= 6)//随机飞机出现计时器
			{
				coutTime = 0;
				randomCreateDiJi(layer);
			}
		}
	}
}
/**

return true:屏幕还有飞机
*/
bool DijiUpdate::hasDji(std::list<b2Body*> dijis)
{
	std::list<b2Body*>::iterator itr;
	for(itr = dijis.begin(); itr != dijis.end(); ++itr)
	{
		DiJiSprite* diji = (DiJiSprite*)((b2Body*)*itr)->GetUserData();
		if(diji->level > 1)
			return true;
	}
	return false;
}

void DijiUpdate::randomCreateDiJi(cocos2d::Layer* _layer)
{
	GameScene* layer = (GameScene*)_layer;
	int _level = 0;
	int _randomL = rand()%10;
	if(_randomL > 4)
		_level = 1;
	int _random = rand()%10;
	if(_random >= 8)
	{
		for(int i = 0; i < 5; ++i)
		{
			float randomNumber = (float)(rand()%20)/10.0f+1.0f;
			layer->createDiJi(Point(750+i*120, 500),_level ,Point(200, 500) ,5,90, randomNumber);
		}
	}
	else if(_random >= 6)
	{
		for(int i = 0; i < 5; ++i)
		{
			float randomNumber = (float)(rand()%20)/10.0f+1.0f;
			layer->createDiJi(Point(-100-i*120, 500),_level ,Point(440, 500) ,5,90, randomNumber);
		}
	}
	else if(_random >= 4)
	{
		for(int i = 0; i < 5; ++i)
		{
			float randomNumber = (float)(rand()%20)/10.0f+1.0f;
			layer->createDiJi(Point(-100-i*100, 800+i*70),_level ,Point(400, 500) ,5,35, randomNumber);
		}
	}
	else if(_random >= 2)
	{
		for(int i = 0; i < 5; ++i)
		{
			float randomNumber = (float)(rand()%20)/10.0f+1.0f;
			layer->createDiJi(Point(750+i*100, 800+i*70),_level ,Point(240, 500) ,5,145, randomNumber);
		}
	}
	else
	{
		for(int i = 0; i < 5; ++i)
		{
			float randomNumber = (float)(rand()%20)/10.0f+1.0f;
			layer->createDiJi(Point(100+i*120, 1100),_level ,Point(100+i*120, -700) ,5,90, randomNumber);
		}
	}
}

