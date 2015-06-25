#ifndef _GAME_SCENE_
#define _GAME_SCENE_
#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "MyContactFilter.h"
#include "MyContactListener.h"
#include "JGbullet.h"
#include "Myb2RayCastCallback.h"
#include "BulletSprite.h"
#include "DijiUpdate.h"
#include "PlayerSprite.h"
#include "Boss_Update.h"
#include "Money.h"

USING_NS_CC;
class GameScene : public cocos2d::Layer
{
public:
	~GameScene();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	//~GameScene(){delete world; delete filter; delete listener; delete dijiUpdate;};
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void initPropScene();
	void initPhysics();
	void initPlayer();
	void initPlayerAnima();
	void initParticleBatch();
	void setTouchListener();
	Point contentVeclecty(Point);//主角限速
	void PlayerMove();//更新主角以及激光子弹的移动
	void update(float dt);
	void bgsRun(float dt);//背景滚动
	void shotBullets(float dt);//每帧放出子弹
	void addremoveBullets();//判断子弹是否出界，出界加入deleteBullets
	void createDiJi(Point point, int _level, Point tarGetPoint, float veclecty,float angle,float startShutTime);//创建敌机
	void addDeleteBullet(b2Body *body);//将子弹加入deleteBullets（用于碰撞敌机后消除）
	void addremoveDiJi();//判断敌机是否y<-200|y>500，true加入deleteDiJis
	void destoryDiJis();//清除deleteDiJis中的敌机
	void destoryBullets();//清除deleteBullets中的子弹
	void subDiJiLife(b2Body *, b2Body *);//敌机被子弹打中后的血量减少以及判断血量少于0后加入deleteDiji
	void subDiJiLife(b2Body *diJiBody, float damege);
	void showBoomParticle(Point point, int level);//显示敌机爆炸的粒子特效
	void showBinGoParticle(Point point);//显示普通子弹打中敌机的粒子特效
	void showJGBinGoParticle(Point point, int tag);
	void initJGbullet();//初始化激光子弹视图
	void destoryJGbullet();//隐藏激光视图
	void showJGbullet();//显示激光视图
	void updateJGbullet();//检测激光子弹视图是否碰到敌机（碰到缩短）
	void initShotAnima();//初始化喷射效果
	void addDijiUpdate(float dt);//每帧检查敌机数量并判断更新
	void stopShutBullet();//停止射击子弹(包括激光视图与喷射等粒子特效的消失)
	bool fuHuo();//复活，命数少于1则返回false 
	void fuHuoing(float dt);//复活无敌期的判断
	void quXiaoWudi(float dt);//取消无敌和闪烁状态
	void playPlayerAnima();//播放玩家飞机机尾火焰动画
	void updateJGShutAnimaSize();//随着激光子弹的升级而改变喷射效果大小
	void max_click(cocos2d::Ref* pSender,ui::TouchEventType type);//按下大招
	void addAllRemoveBullets();//清空屏幕所有子弹
	void show_max_texiao();//MAX一瞬间的特效
	void resumeBGmusic(float dt);//逐渐放大背景音乐
	void pauseBGmusic();//取消背景音乐
	void douDong(float dt);//屏幕抖动
	void stopDouDong();//停止抖动
	int getGK();
	b2World* getWorld();
	b2Body* getPlayerBody();
	PlayerSprite *getPlayer();
	void removeListener();
	void setCanCorcarlt(float dt);
	void setCancorcarlt(bool );
	void setCanCorcarltTrue(float dt);
	void updateMoneyMove(float dt);
	void baozouUpdate(float dt);
	void boss_come(float dt);
	void setISboss(float dt);
	void showBossBoom1(float dt);
	void showBossBoom2(float dt);
	void showPlanOut(float dt);
	void showPlayerWin(float dt);//显示胜利菜单
	void showPause(float dt);//显示暂停菜单
	void showFail(float dt);//显示失败菜单
	void initbgs();
	void clickPause(cocos2d::Ref* pSender,ui::TouchEventType type);

	void Main_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	void resume_button(cocos2d::Ref* pSender,ui::TouchEventType type);
	
	Texture2D *feiji;
	Texture2D *boom;
	Texture2D *shot;
	Texture2D *penshe;
	Texture2D *bulletsTexture;
	Texture2D *shutAnimaTexture;
	std::list<b2Body*> diJis;//主要敌机
	std::vector<b2Body*> deleteDiJis;//要删除的敌机

	SpriteBatchNode *bulletBatch;
	SpriteBatchNode *diJiBulletBatch;

	Boss_Update *bossUpdate;

	Vector<SpriteFrame*> playerAnmia;//玩家飞机机尾火焰动画
	Vector<SpriteFrame*> wudis;//无敌闪烁动画

	std::list<b2Body*> bullets;//子弹
    Rect playerRect;
	bool isBoss;
	bool isFuHuoing;//是否在复活无敌期
    CREATE_FUNC(GameScene);
private:
	
	b2World *world;
	b2Body *playerBody;
	float bgsVeclecty;
	PlayerSprite *player;
	Sprite *bg1;
	Sprite *bg2;
	Sprite *bg3;
	Sprite *shutSprite;
	Point touchMovePoint;
	Point tagetTouchPoint;
	bool isShootJGbullet;

	ValueMap binGonplistData;
	ValueMap boomPlistData;
	ValueMap jgBingoPlistData;

	MyContactFilter *filter;
	MyContactListener *listener;
	Myb2RayCastCallback rayCastCallback;
	float playerVeclecty;//主角速度
	float shutOnceTime;//射击间隔时间累加变量
	float shutTime;

	EventListenerTouchAllAtOnce *touchListener;//触摸移动飞机监听

	
	std::vector<b2Body*> deleteBullets;//需要删除的子弹
	std::list<JGbullet*> JGbullets;//激光视图精灵
	std::list<Money*> moneys;//激光视图精灵
	std::vector<ParticleSystem*> JGbinggos;
	std::vector<ParticleSystem*> desJGbinggos;

	ParticleBatchNode *boombatch;//爆炸特效
	ParticleBatchNode *binGobatch;//普通子弹打中敌人的粒子特效
	ParticleBatchNode *JGbatch;//激光打中敌人的粒子特效
	ParticleBatchNode *penshebatch;//激光喷射的粒子特效
	
	bool isCanCortarl;
	
	DijiUpdate *dijiUpdate;
	
	float baozou_time;
	bool isBaozou;
	
	int guanka;
	int max_cout;
	Text* max_text;
	Text* life_text;
	bool isGameOver;
public:
	Button* max_button;
	int bg_vec;
	
};

#endif
