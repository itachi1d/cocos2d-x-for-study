#include "cocos2d.h"
#include "UIListView.h"
#include "EMail.h"

using namespace cocos2d;

class GameScene : public Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	void loadItem(int);
	void loadXML();
	void updateListView();
	void addListItem(EMail*);
	int type;
	ui::ListView *list;
	CREATE_FUNC(GameScene);
private:
	std::map<int, EMail*> map;
};