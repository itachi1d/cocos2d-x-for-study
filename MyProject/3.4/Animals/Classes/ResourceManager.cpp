#include "ResourceManager.h"
#include "Tool.h"
#include "cocos-ext.h"
#include "tinyxml2/tinyxml2.h"

ResourceManager* ResourceManager::Instance()
{
	if(!resourceManager)
	{
		resourceManager = new ResourceManager();
		resourceManager->isReadJson = false;
		resourceManager->texture = Director::getInstance()->getTextureCache();
		resourceManager->frameCache = SpriteFrameCache::sharedSpriteFrameCache();
	}
	return resourceManager;
}

void ResourceManager::destoryGameLayerResource()
{
	if(!frameCache)
		return;
	std::string name;
	for(int i = 1; i <= 6; ++i)
	{		
		name = "res/map" + Tool::toString(i) +".png";
		texture->removeTextureForKey(name);
		name = "res/map" + Tool::toString(i) +".plist";
		frameCache->removeSpriteFramesFromFile(name);

		name = "res/map" + Tool::toString(i) +"_1.png";
		texture->removeTextureForKey(name);
		name = "res/map" + Tool::toString(i) +"_1.plist";
		frameCache->removeSpriteFramesFromFile(name);
	}
}

void ResourceManager::initAnimats()
{
	ResourceManager::initAnimation("daxiang", vector_daxiang);
	ResourceManager::initAnimation("houzi", vector_houzi);
	ResourceManager::initAnimation("tuoniao", vector_tuoniao);
	ResourceManager::initAnimation("banma", vector_banma);
	ResourceManager::initAnimation("luotuo", vector_luotuo);
	ResourceManager::initAnimation("shizi", vector_shizi);
	ResourceManager::initAnimation("yezhu", vector_yezhu);
	ResourceManager::initAnimation("xiniu", vector_xiniu);
	ResourceManager::initAnimation("xiongmao", vector_xiongmao);
	ResourceManager::initAnimation("kongong", vector_kongong);
	ResourceManager::initAnimation("wugui", vector_wugui);
}

void ResourceManager::initAnimation(std::string animaName, Vector<SpriteFrame*> &vector)
{
	std::string frameName;
	int i = 1;
	while(true)
	{
		frameName = animaName + Tool::toString(i) + ".png";
		if(!ResourceManager::Instance()->frameCache->getSpriteFrameByName(frameName))
			break;
		vector.pushBack(ResourceManager::Instance()->frameCache->getSpriteFrameByName(frameName));
		i++;
	}
}

void ResourceManager::loadJson()
{
	if(isReadJson)
		return;
	rapidjson::Document d1;
	std::string contentStr = FileUtils::getInstance()->getStringFromFile("res/Animal.json");
	d1.Parse<0>(contentStr.c_str());
	//打印JSon文件的内容
	printf("%s\n",contentStr.c_str());
  
	const rapidjson::Value& c = d1["addCout"];
	if (c.IsArray()) 
	{
		init_cout = c[(unsigned)0].GetInt();
		add_cout = c[(unsigned)1].GetInt();
		add_coutVar = c[(unsigned)2].GetInt();
	}
	//获取JSon中数组的方法
	const rapidjson::Value& v = d1["animal"];

	if (v.IsArray()) 
	{
		//这里一定要注意  变量i 一定要是   unsigned int  不然会报错
		for (unsigned int i = 0; i< v.Size(); ++i) 
		{   
			const rapidjson::Value &val = v[i];
			//log("%s",val.Size());
			if (val.IsArray()) 
			{
				for(unsigned int j = 0; j<val.Size(); ++j)
				{
					const rapidjson::Value &value = val[j];
					switch (j)
					{
					case 0:
						animal_Name[i] = value.GetString();
						break;
					case 1:
						animal_Speed[i] = value.GetInt();
						break;
					case 2:
						animal_SpeedVar[i] = value.GetInt();
						break;
					case 3:
						animal_Speedcout[i] = value.GetInt();
						break;
					default:
						break;
					}
				}
			}
		}
      
	}
	isReadJson = true;
}

ResourceManager* ResourceManager::resourceManager = NULL;
Vector<SpriteFrame*> ResourceManager::vector_daxiang;
Vector<SpriteFrame*> ResourceManager::vector_houzi;
Vector<SpriteFrame*> ResourceManager::vector_tuoniao;
Vector<SpriteFrame*> ResourceManager::vector_banma;
Vector<SpriteFrame*> ResourceManager::vector_luotuo;
Vector<SpriteFrame*> ResourceManager::vector_shizi;
Vector<SpriteFrame*> ResourceManager::vector_yezhu;
Vector<SpriteFrame*> ResourceManager::vector_xiniu;
Vector<SpriteFrame*> ResourceManager::vector_xiongmao;
Vector<SpriteFrame*> ResourceManager::vector_kongong;
Vector<SpriteFrame*> ResourceManager::vector_wugui;