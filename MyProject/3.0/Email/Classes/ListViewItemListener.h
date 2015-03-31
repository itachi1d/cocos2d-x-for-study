#include "cocos2d.h"
#include "UIListView.h"
#include "EMail.h"

using namespace cocos2d;

class ListViewItemListener
{
public:
	void showContent(Ref* sender , ui::TouchEventType type);
	void back(Ref* sender , ui::TouchEventType type);
	void changeType0(Ref* sender , ui::TouchEventType type);
	void changeType1(Ref* sender , ui::TouchEventType type);
	void close(Ref* sender , ui::TouchEventType type);
};