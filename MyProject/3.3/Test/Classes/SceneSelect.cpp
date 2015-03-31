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
				_name = "�ȼ�";
				break;
			case 2:
				_name = "�������辭��";
				break;
			case 3:
				_name = "��Ѫ";
				break;
			case 4:
				_name = "�˺�";
				break;
			case 5:
				_name = "����";
				break;
			case 6:
				_name = "�ٶ�";
				break;
			case 7:
				_name = "����";
				break;
			case 8:
				_name = "ɱ��";
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
	hero1->setObject(String::create("3"), "�ȼ�");
	hero2->setObject(String::create("2"), "�ȼ�");
	hero3->setObject(String::create("5"), "�ȼ�");
	hero4->setObject(String::create("1"), "�ȼ�");

	hero1->setObject(String::create("10"), "�������辭��");
	hero2->setObject(String::create("200"), "�������辭��");
	hero3->setObject(String::create("300"), "�������辭��");
	hero4->setObject(String::create("400"), "�������辭��");

	hero1->setObject(String::create("100"), "��Ѫ");
	hero2->setObject(String::create("200"), "��Ѫ");
	hero3->setObject(String::create("300"), "��Ѫ");
	hero4->setObject(String::create("400"), "��Ѫ");

	hero1->setObject(String::create("123"), "�˺�");
	hero2->setObject(String::create("234"), "�˺�");
	hero3->setObject(String::create("345"), "�˺�");
	hero4->setObject(String::create("456"), "�˺�");

	hero1->setObject(String::create("111"), "����");
	hero2->setObject(String::create("222"), "����");
	hero3->setObject(String::create("333"), "����");
	hero4->setObject(String::create("444"), "����");

	hero1->setObject(String::create("555"), "�ٶ�");
	hero2->setObject(String::create("666"), "�ٶ�");
	hero3->setObject(String::create("777"), "�ٶ�");
	hero4->setObject(String::create("888"), "�ٶ�");

	hero1->setObject(String::create("234"), "����");
	hero2->setObject(String::create("343"), "����");
	hero3->setObject(String::create("353"), "����");
	hero4->setObject(String::create("213"), "����");

	hero1->setObject(String::create("232"), "ɱ��");
	hero2->setObject(String::create("23"), "ɱ��");
	hero3->setObject(String::create("23"), "ɱ��");
	hero4->setObject(String::create("343"), "ɱ��");

	root->setObject(hero1, "1");
	root->setObject(hero2, "2");
	root->setObject(hero3, "3");
	root->setObject(hero4, "4");

	std::string writeableList = FileUtils::getInstance()->sharedFileUtils()->getWritablePath();
	std::string path = writeableList+"text.plist";
	std::string s = path.c_str();
	root->writeToFile(path.c_str());
}