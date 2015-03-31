#include "Scene3.h"
#include "A.h"
#include "SceneSelect.h"
#include "RTscene.h"

Scene3::Scene3(void)
{
}


Scene3::~Scene3(void)
{
}

void Scene3::pushThisScene()
{
	CCLayer* p_display=new Layer3();
	p_display->autorelease();
	
	
	addChild(p_display);
	CCDirector::sharedDirector()->replaceScene(this);
}

Layer3::Layer3():isMove(false)
{
	for(int i = 0; i < 20; ++i)
	{
		std::stringstream ss;
		ss<<i+1;
		std::string str;
		ss>>str;
		LabelTTF *scene = LabelTTF::create("Scene"+str,"Arial",30.0f);
		addChild(scene, 10);
		scene->setTag(i+1);
		scene->setAnchorPoint(Point(0, 1));
		scene->setPosition(0, 640 - 25*i);
		list.push_back(scene);
	}
	setTouchListener();
}
Layer3::~Layer3()
{
	
}

bool Layer3::init()
{
	if(!Layer::init())
	{
		return false;
	}          
	return 1;
}

void Layer3::setTouchListener()
{
	EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touche, Event* event){

		Point touPoint = this->convertToNodeSpace(touche->getLocation());
		po = touPoint;
		std::list<LabelTTF*>::iterator itr;
		bool flag = false;
		for(itr = list.begin(); itr != list.end();++itr)
		{			
			LabelTTF *scene = (LabelTTF*)*itr;
			Size size = scene->getContentSize();
			Point p = scene->getPosition();
			Rect rect = Rect(p.x, p.y - size.height, size.width, size.height);
			if(rect.containsPoint(touPoint))
			{
				tag = scene->getTag();
				flag = true;
				break;
			}

		}
		if(!flag)
			tag = -1;
		return true;
	};

	touchListener->onTouchMoved = [=](Touch* touche, Event* event){
		isMove = true;
		Point touPoint = this->convertToNodeSpace(touche->getLocation());
		if(touPoint.y < po.y)
		{
			float cout = touPoint.y - po.y;
			po = touPoint;
		
			std::list<LabelTTF*>::iterator itr;
			for(itr = list.begin(); itr != list.end();++itr)
			{
				LabelTTF *scene = (LabelTTF*)*itr;
				scene->setPositionY(scene->getPositionY()+cout/10);
			}
		}
	};
	touchListener->onTouchEnded = [=](Touch* touche, Event* event){
		if(isMove)
		{
			std::list<LabelTTF*>::iterator itr;
			for(itr = list.begin(); itr != list.end();++itr)
			{
				LabelTTF *scene = (LabelTTF*)*itr;
				scene->runAction(MoveTo::create(0.2f, Point(0, 640 - 25*(scene->getTag()-1))));
				isMove = false;
			}
		}
		else if(tag != -1)
		{
			//´ò¿ªscene
			std::stringstream ss;
			ss<<tag;
			std::string s;
			ss>>s;
			std::string str = "scene"+s;
			RTscene *p_scene = new RTscene();
			p_scene->pushThisScene(str);
			p_scene->release();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Layer3::back()
{
	CCScene* pScene = CCScene::create();
	CCLayer* pLayer=SceneSelect::create();

	pScene->addChild(pLayer);
	Director::getInstance()->replaceScene(pScene);
}

