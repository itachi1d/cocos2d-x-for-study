#pragma once
#include "cocos2d.h"
#include "MyContactListener.h"
#include "MyContactFiler.h"
#include <Box2D\Box2D.h>
USING_NS_CC;


class GameScene:public LayerColor
{
public:
	~GameScene(){delete world; delete contactlistener; delete contactFilter;};
	static cocos2d::Scene* createScene();
	void initMap();
	void initPhysics();
	void initPlay();
	void initButton();
    virtual bool init(); 
	std::set<b2Fixture *> contactsWithPlayer;
	void runAction();
	void jumpAction();
	void goRunAction();
	void gojumpAction();
	void goDownAction();
	void stopRunAction();
	void stopjumpAction();
	void stopDownAction();
	void update(float dt);
	void updatePlayer(float dt);
	void updateLayer(float dt);
	void setTouchListener();
	int getGameState();
	void playerJump();
	void playerHighJump(float VeclocityY);
	bool isCanJump();
	void playerDown();
	bool isCanDown();
	void hasUpBody(float dt);//判断主角上方是否有障碍物，用来判断下滚是否可以使用跳跃或起身
	void comeBackMain(Ref* p);
	void resetGame(Ref* p);
	void nextGame(Ref* p);
	void goOnGame(Ref* p);
	void stopGame(Ref* p);
	void isCanThoughDown();//用来阻止以站立的姿势通过小道
	void initToughMenus();
	void initEndMenus();
	void initStopMenus();
	void backButtonListener();
	CREATE_FUNC(GameScene);
	enum GameState
	{
		ready, running, stop, end
	};
	enum PlayerState
	{
		run, jump, down
	};
	int playState;
	int gameState;
	bool isThough;
	bool isCanUp;
private:
	MyContactListener *contactlistener;
	MyContactFiler *contactFilter;
	Texture2D *playerImage;
	Texture2D *itemsImage;
	b2World *world;
	b2Body *hcrBody;
	b2Body *ciBody;
	Vector<SpriteFrame*> jumps;
	Vector<SpriteFrame*> runs;
	float playerVelocity;
	float MaxPlayerVelocity;
	float layerVelocity;
	float layerMoveLen;
	float ciSpeed;
	float downTime;
	MenuItemSprite *stopButton;
	Menu *thoughMenu;
	Menu *endMenu;
	Menu *stopMenu;
	bool buttonDowning;
	bool buttonUping;
	bool isSlow;

	Point touchUpPoint;
	Point touchDownPoint;
	Point touchSlowPoint;
	
	
};