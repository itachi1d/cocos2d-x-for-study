#ifndef __RESOURCE_H__
#define __RESOURCE_H__
#include "cocos2d.h"
using namespace cocos2d;
class ResourceManager
{
public:
	static ResourceManager* Instance();
	void destoryGameLayerResource();
	static void initAnimats();
	static void initAnimation(std::string animaName, Vector<SpriteFrame*> &vector);
	void loadJson();
public:
	SpriteFrameCache *frameCache;
	TextureCache *texture; 
	
private:
	static ResourceManager* resourceManager;
	bool isReadJson;
public:
	static Vector<SpriteFrame*> vector_daxiang;
	static Vector<SpriteFrame*> vector_houzi;
	static Vector<SpriteFrame*> vector_tuoniao;
	static Vector<SpriteFrame*> vector_banma;
	static Vector<SpriteFrame*> vector_luotuo;
	static Vector<SpriteFrame*> vector_shizi;
	static Vector<SpriteFrame*> vector_yezhu;
	static Vector<SpriteFrame*> vector_xiniu;
	static Vector<SpriteFrame*> vector_xiongmao;
	static Vector<SpriteFrame*> vector_kongong;
	static Vector<SpriteFrame*> vector_wugui;

public:
	std::string animal_Name[11];
	int animal_Speed[11];//基础速度
	int animal_SpeedVar[11];//速度波动值
	int animal_Speedcout[11];//每关速度增长值

	int init_cout;//初始动物数量
	int add_cout;//每关增加动物的数量
	int add_coutVar;//每关增加动物的数量的波动值
};

#endif