#pragma once

#include "SceneInterface.h"

class Scene3 :
	public SceneInterface
{
public:
	Scene3(void);
	~Scene3(void);

	void pushThisScene();
};

class Layer3:
	public Layer
{
public:
	Layer3();
	~Layer3();
	bool init();
	void setTouchListener();
	void back();

private:
	std::list<LabelTTF*> list;
	bool isMove;
	int tag;
	Point po;
};