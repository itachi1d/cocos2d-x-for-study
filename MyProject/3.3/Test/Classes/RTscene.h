#include "cocos2d.h"
#include "SceneInterface.h"
using namespace cocos2d;
class RTscene : public SceneInterface
{
public:
	 RTscene(void);
	~RTscene(void);

	void pushThisScene(std::string _str);
	void pushThisScene();
};

class RTlayer : public Layer
{
public:
	RTlayer();
	~RTlayer();
	void onEnter();
	std::string str;
private:

};