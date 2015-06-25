#ifndef _STARTSCENE_
#define _STARTSCENE_
#include "CSB_Layer.h"

class StartScene
	: public CSB_Layer
{
	typedef CSB_Layer Base;
	typedef StartScene Self;
public:
	StartScene ();
	virtual ~StartScene ();
	std::string get_csb_filename ();
	void set_callback (Node*);
	CREATE_FUNC (Self);
public:
	void plistImageAsyncCallback(cocos2d::Texture2D* texture, int i);
	void changeScene(float time);
};
#endif