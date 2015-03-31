#include "cocos2d.h"
#include "SceneInterface.h"
using namespace cocos2d;
class Scene1 : public SceneInterface
{
public:
	 Scene1(void);
	~Scene1(void);

	void pushThisScene();
};

class TimeLayer:
	public Layer
{
public:
	TimeLayer();
	~TimeLayer();

	void showTime(float dt);
	void stopTime();
	void startTime();
	void back();

private:
	int Seconds;
	int Minute;
	int Hour;
	LabelTTF *timeLabel;
};

class OhterLayer:
	public Layer
{
public:
	OhterLayer();
	~OhterLayer();

	void setTouchListener();
private:
	Sprite *sprite;
};