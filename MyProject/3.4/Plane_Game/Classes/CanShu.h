#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define PTM_RATIO 32
#define BGS_VELOCITY 150;//背景滚动速度
#define PLAYER_MAX_VELOCITY 2000//玩家飞机最大速度(Point)
#define PLAYER_MIN_VELOCITY 600//玩家飞机最小速度(Point)
#define BULLET_VELOCITY 40//普通子弹速度(b2Vec2)
#define JG_BULLET_VELOCITY 100//激光子弹速度(b2Vec2)
#define BULLET_ONCE_TIME 0.1//每发射一次子弹的间隔(秒)
#define BULLET_TWICE_TIME 0.3//每发射两次次子弹的间隔(秒)
#define DIJI_RATION_SPEED 100//敌机改变方向的转速

//--------------敌机射击子弹的间隔---------------
#define DIJI_BULLET_ONCE_TIME_0 1
#define DIJI_BULLET_ONCE_TIME_1 1
#define DIJI_BULLET_ONCE_TIME_2 0.5
#define DIJI_BULLET_ONCE_TIME_3 0.2
#define DIJI_BULLET_ONCE_TIME_4 0.05
#define DIJI_BULLET_ONCE_TIME_5 0.3
#define DIJI_BULLET_ONCE_TIME_6 0.1
#define DIJI_BULLET_ONCE_TIME_7 0.02
#define DIJI_BULLET_ONCE_TIME_8 0.07

//--------------敌机射出的子弹的速度--------------
#define DIJI_BULLET_SPEED_TYPE_0 3
#define DIJI_BULLET_SPEED_TYPE_1 7
#define DIJI_BULLET_SPEED_TYPE_2 10
#define DIJI_BULLET_SPEED_TYPE_3 12
#define DIJI_BULLET_SPEED_TYPE_4 14
#define DIJI_BULLET_SPEED_TYPE_5 16
#define DIJI_BULLET_SPEED_TYPE_6 20
#define DIJI_BULLET_SPEED_TYPE_7 25
#define DIJI_BULLET_SPEED_TYPE_8 30
//--------------MAX伤害---------------------------
#define MAX_DAMEGE1 7000 //大招一每秒伤害

extern int guanqia;
extern int through_gq;
extern int plane_type;
enum Game_Mode
{
	BOSS_MODE,
	NORMAL_MODE

};
extern Game_Mode game_mode;


extern Rect bgRect1;
extern Rect bgRect2;
extern Rect bgRect3;

extern Rect playerRect1_1;
extern Rect playerRect1_2;
extern Rect playerRect2_1;
extern Rect playerRect2_2;
extern Rect playerRect3_1;
extern Rect playerRect3_2;
extern Rect playerRect4;
extern Rect ziDanRect1;
extern Rect ziDanRect2;
extern Rect JiGziDanLeftRect;
extern Rect JiGziDanCenterRect;
extern Rect JiGziDanRightRect;

extern Rect JiGziDanLeftViewRect;
extern Rect JiGziDanCenterViewRect;
extern Rect JiGziDanRightViewRect;


extern Rect diJiRect0;
extern Rect diJiRect1;
extern Rect diJiRect2;
extern Rect diJiRect3;
extern Rect diJiRect4;

extern Rect DiJi_Bullet0;
extern Rect DiJi_Bullet1;
extern Rect DiJi_Bullet2;
extern Rect DiJi_Bullet3;
extern Rect DiJi_Bullet4;
extern Rect DiJi_Bullet5;
extern Rect DiJi_Bullet6;
extern Rect DiJi_Bullet7;

extern Rect DiJi_Shut0;

extern Rect shutAnimation1;
extern Rect shutAnimation2;
extern Rect JGbinGoAnimation1;
extern Rect JGbinGoAnimation2;
extern Rect sdAnimation1;
extern Rect sdAnimation2;
extern Rect sdAnimation3;
extern Rect sdAnimation4;
extern Rect sdAnimation5;
extern Rect sdAnimation6;
extern Rect sdAnimation7;

extern std::string boom_sound;
extern std::string max_sound;
extern std::string maxing1_sound;
extern std::string bg_sound2;

extern bool isSoundOpen;
extern int bulletType;
extern int bulletLevel;
extern int playerLife;
