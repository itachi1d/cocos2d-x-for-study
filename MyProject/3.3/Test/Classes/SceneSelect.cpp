#include "SceneSelect.h"
#include "SceneInterface.h"
#include "CustomTableViewCell.h"
#include "Scene2.h"
#include "Scene1.h"
#include "Scene3.h"

SceneSelect::SceneSelect(void)
	:win_size_(CCSizeMake(0.f,0.f))
{
}


SceneSelect::~SceneSelect(void)
{
}
bool SceneSelect::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	          

	win_size_=CCDirector::sharedDirector()->getWinSize();

	cell_items_.push_back("scene_1");
	cell_items_.push_back("scene_2");
	cell_items_.push_back("scene_3");

	cell_num_=cell_items_.size();

	TableView* table_view=TableView::create(this,CCSizeMake(win_size_.width/2,win_size_.height));
	table_view->setDirection(ScrollView::Direction::VERTICAL);
	table_view->setPosition(0,0);
	table_view->setDelegate(this);
	this->addChild(table_view);
	table_view->reloadData();

	CCLayerColor* background = CCLayerColor::create(ccc4(100,100,100,150));
	background->setContentSize(table_view->getViewSize());
    addChild(background, 1);
	 std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	setRandomNumber();
	saveXML();
	loadXML();
	for(int j = 1; j <= 8; j++)
	{
		std::string _name;
		switch (j)
		{
		case 1:
			_name = "level";
			break;
		case 2:
			_name = "experience";
			break;
		case 3:
			_name = "life";
			break;
		case 4:
			_name = "damage";
			break;
		case 5:
			_name = "agile";
			break;
		case 6:
			_name = "speed";
			break;
		case 7:
			_name = "defuat";
			break;
		case 8:
			_name = "murderous";
			break;
		default:
			break;
		}
	
		LabelTTF *scene = LabelTTF::create(_name,"Arial",20.0f);
		addChild(scene, 10);
		scene->setColor(Color3B::RED);
		scene->setPosition(20+j*80, 400);
	}

	return 1;
}

ssize_t SceneSelect::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
	return cell_num_;
}

TableViewCell* SceneSelect::tableCellAtIndex(TableView* table,ssize_t idx)
{
	TableViewCell* cell=table->dequeueCell();
	if(!cell)
	{
		cell =new CustomTableViewCell();
		cell->autorelease();
		
		CCLabelTTF* lable=CCLabelTTF::create(cell_items_[cell_num_-idx-1].c_str(),"Arial",40.0f);
		lable->setAnchorPoint(Vec2::ZERO);
		lable->setPosition(Vec2::ZERO);
		lable->setTag(cell_num_-idx-1);
		cell->addChild(lable);
	}
	else
	{
	}
	return cell;
}

CCSize SceneSelect::tableCellSizeForIndex(TableView* table,ssize_t idx)
{
	return CCSizeMake(win_size_.width,40);
}

void SceneSelect::tableCellTouched(TableView* table,TableViewCell* cell)
{
	CCLOG("cell touched at index: %i", cell->getIdx());
	createSceneWithIndex(cell_num_-cell->getIdx()-1);
}

void SceneSelect::createSceneWithIndex(unsigned short int index)
{
	CCDirector::sharedDirector()->purgeCachedData();
	SceneInterface* p_scene=NULL;
	switch (index)
	{
	case 0:
		p_scene=new Scene1();
		break;
	case 1:
		p_scene=new Scene2();
		break;
	case 2:
		p_scene=new Scene3();
		break;
	default:
		break;
	}

	if(p_scene)
	{
		p_scene->pushThisScene();
		p_scene->release();
	}
}

void SceneSelect::menuCloseCallback( CCObject* pSender )
{
	 CCDirector::sharedDirector()->end();
}
void SceneSelect::setRandomNumber()
{
	srand((int)time(NULL));
	for(int i = 0; i < 20; ++i)
	{
		a[i] = rand()%100;
	}
	int size = 20;
	for(int i = 0; i < size; ++i)
	{
		for(int j = i+1; j < size; ++j)
		{
			if(a[i] > a[j])
			{
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	int x = 50;
	for(int i = 0; i < size; ++i)
	{
		std::stringstream ss;
		ss<<a[i];
		std::string str;
		ss>>str;
		LabelTTF *lable = LabelTTF::create(str, "Arial", 20);
		addChild(lable, 20);
		lable->setPosition(x, 500);
		x += 40;
	}
}

void SceneSelect::loadXML()
{
	std::string writeableList = FileUtils::getInstance()->sharedFileUtils()->getWritablePath();
	std::string path = writeableList+"text.plist";
	Dictionary *rootDict = Dictionary::createWithContentsOfFile(path.c_str());
	Dictionary* data1;
	for(int i = 1; i <= 4;)
	{
		std::stringstream ss;
		ss<<i;
		std::string no;
		ss>>no;
		data1 = dynamic_cast<Dictionary*>(rootDict->objectForKey(no));
		for(int j = 1; j <= 8; j++)
		{
			std::string _name;
			switch (j)
			{
			case 1:
				_name = "等级";
				break;
			case 2:
				_name = "升级所需经验";
				break;
			case 3:
				_name = "气血";
				break;
			case 4:
				_name = "伤害";
				break;
			case 5:
				_name = "敏捷";
				break;
			case 6:
				_name = "速度";
				break;
			case 7:
				_name = "防御";
				break;
			case 8:
				_name = "杀气";
				break;
			default:
				break;
			}
			String *str1 = dynamic_cast<String*>(data1->objectForKey(_name));
			std::string str = str1->getCString();
			LabelTTF *scene = LabelTTF::create(str,"Arial",20.0f);
			addChild(scene, 10);
			scene->setPosition(20+j*80, 50+i*80);
		}
		++i;
	}
}
void SceneSelect::saveXML()
{
	auto root = Dictionary::create();
	auto hero1 = Dictionary::create();
	auto hero2 = Dictionary::create();
	auto hero3 = Dictionary::create();
	auto hero4 = Dictionary::create();
	hero1->setObject(String::create("3"), "等级");
	hero2->setObject(String::create("2"), "等级");
	hero3->setObject(String::create("5"), "等级");
	hero4->setObject(String::create("1"), "等级");

	hero1->setObject(String::create("10"), "升级所需经验");
	hero2->setObject(String::create("200"), "升级所需经验");
	hero3->setObject(String::create("300"), "升级所需经验");
	hero4->setObject(String::create("400"), "升级所需经验");

	hero1->setObject(String::create("100"), "气血");
	hero2->setObject(String::create("200"), "气血");
	hero3->setObject(String::create("300"), "气血");
	hero4->setObject(String::create("400"), "气血");

	hero1->setObject(String::create("123"), "伤害");
	hero2->setObject(String::create("234"), "伤害");
	hero3->setObject(String::create("345"), "伤害");
	hero4->setObject(String::create("456"), "伤害");

	hero1->setObject(String::create("111"), "敏捷");
	hero2->setObject(String::create("222"), "敏捷");
	hero3->setObject(String::create("333"), "敏捷");
	hero4->setObject(String::create("444"), "敏捷");

	hero1->setObject(String::create("555"), "速度");
	hero2->setObject(String::create("666"), "速度");
	hero3->setObject(String::create("777"), "速度");
	hero4->setObject(String::create("888"), "速度");

	hero1->setObject(String::create("234"), "防御");
	hero2->setObject(String::create("343"), "防御");
	hero3->setObject(String::create("353"), "防御");
	hero4->setObject(String::create("213"), "防御");

	hero1->setObject(String::create("232"), "杀气");
	hero2->setObject(String::create("23"), "杀气");
	hero3->setObject(String::create("23"), "杀气");
	hero4->setObject(String::create("343"), "杀气");

	root->setObject(hero1, "1");
	root->setObject(hero2, "2");
	root->setObject(hero3, "3");
	root->setObject(hero4, "4");

	std::string writeableList = FileUtils::getInstance()->sharedFileUtils()->getWritablePath();
	std::string path = writeableList+"text.plist";
	std::string s = path.c_str();
	root->writeToFile(path.c_str());
}