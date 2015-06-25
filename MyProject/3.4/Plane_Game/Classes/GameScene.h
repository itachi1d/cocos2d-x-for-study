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
	Point contentVeclecty(Point);//��������
	void PlayerMove();//���������Լ������ӵ����ƶ�
	void update(float dt);
	void bgsRun(float dt);//��������
	void shotBullets(float dt);//ÿ֡�ų��ӵ�
	void addremoveBullets();//�ж��ӵ��Ƿ���磬�������deleteBullets
	void createDiJi(Point point, int _level, Point tarGetPoint, float veclecty,float angle,float startShutTime);//�����л�
	void addDeleteBullet(b2Body *body);//���ӵ�����deleteBullets��������ײ�л���������
	void addremoveDiJi();//�жϵл��Ƿ�y<-200|y>500��true����deleteDiJis
	void destoryDiJis();//���deleteDiJis�еĵл�
	void destoryBullets();//���deleteBullets�е��ӵ�
	void subDiJiLife(b2Body *, b2Body *);//�л����ӵ����к��Ѫ�������Լ��ж�Ѫ������0�����deleteDiji
	void subDiJiLife(b2Body *diJiBody, float damege);
	void showBoomParticle(Point point, int level);//��ʾ�л���ը��������Ч
	void showBinGoParticle(Point point);//��ʾ��ͨ�ӵ����ел���������Ч
	void showJGBinGoParticle(Point point, int tag);
	void initJGbullet();//��ʼ�������ӵ���ͼ
	void destoryJGbullet();//���ؼ�����ͼ
	void showJGbullet();//��ʾ������ͼ
	void updateJGbullet();//��⼤���ӵ���ͼ�Ƿ������л����������̣�
	void initShotAnima();//��ʼ������Ч��
	void addDijiUpdate(float dt);//ÿ֡���л��������жϸ���
	void stopShutBullet();//ֹͣ����ӵ�(����������ͼ�������������Ч����ʧ)
	bool fuHuo();//�����������1�򷵻�false 
	void fuHuoing(float dt);//�����޵��ڵ��ж�
	void quXiaoWudi(float dt);//ȡ���޵к���˸״̬
	void playPlayerAnima();//������ҷɻ���β���涯��
	void updateJGShutAnimaSize();//���ż����ӵ����������ı�����Ч����С
	void max_click(cocos2d::Ref* pSender,ui::TouchEventType type);//���´���
	void addAllRemoveBullets();//�����Ļ�����ӵ�
	void show_max_texiao();//MAXһ˲�����Ч
	void resumeBGmusic(float dt);//�𽥷Ŵ󱳾�����
	void pauseBGmusic();//ȡ����������
	void douDong(float dt);//��Ļ����
	void stopDouDong();//ֹͣ����
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
	void showPlayerWin(float dt);//��ʾʤ���˵�
	void showPause(float dt);//��ʾ��ͣ�˵�
	void showFail(float dt);//��ʾʧ�ܲ˵�
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
	std::list<b2Body*> diJis;//��Ҫ�л�
	std::vector<b2Body*> deleteDiJis;//Ҫɾ���ĵл�

	SpriteBatchNode *bulletBatch;
	SpriteBatchNode *diJiBulletBatch;

	Boss_Update *bossUpdate;

	Vector<SpriteFrame*> playerAnmia;//��ҷɻ���β���涯��
	Vector<SpriteFrame*> wudis;//�޵���˸����

	std::list<b2Body*> bullets;//�ӵ�
    Rect playerRect;
	bool isBoss;
	bool isFuHuoing;//�Ƿ��ڸ����޵���
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
	float playerVeclecty;//�����ٶ�
	float shutOnceTime;//������ʱ���ۼӱ���
	float shutTime;

	EventListenerTouchAllAtOnce *touchListener;//�����ƶ��ɻ�����

	
	std::vector<b2Body*> deleteBullets;//��Ҫɾ�����ӵ�
	std::list<JGbullet*> JGbullets;//������ͼ����
	std::list<Money*> moneys;//������ͼ����
	std::vector<ParticleSystem*> JGbinggos;
	std::vector<ParticleSystem*> desJGbinggos;

	ParticleBatchNode *boombatch;//��ը��Ч
	ParticleBatchNode *binGobatch;//��ͨ�ӵ����е��˵�������Ч
	ParticleBatchNode *JGbatch;//������е��˵�������Ч
	ParticleBatchNode *penshebatch;//���������������Ч
	
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
