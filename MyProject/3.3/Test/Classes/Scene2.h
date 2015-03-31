#pragma once
#ifndef _Scene2_h_
#define _Scene2_h_

#include "SceneInterface.h"

class Scene2 :
	public SceneInterface
{
public:
	Scene2(void);
	~Scene2(void);

	void pushThisScene();
};

class Display:
	public CCLayer
{
public:
	Display();
	~Display();

	void createPic(Point point);
	void setTouchListener();
	void change(float dt);
	void back();

private:
	CCLabelTTF* p_lable_;
	Texture2D *texture;
	std::list<Sprite*> sprites;
	float t;
	bool canMove;
	bool isTouch;
	Sprite* _sprite;
};

#endif