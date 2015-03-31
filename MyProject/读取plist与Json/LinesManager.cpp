#include "LinesManager.h"
#include "cocos-ext.h"
#include "tinyxml2/tinyxml2.h"

using namespace cocos2d;
void LinesManager::loadJson()
{
	rapidjson::Document d1;
	std::string contentStr = FileUtils::getInstance()->getStringFromFile("settings/threads.json");
	d1.Parse<0>(contentStr.c_str());
	//打印JSon文件的内容
	printf("%s\n",contentStr.c_str());
  
	//获取JSon中数组的方法
	const rapidjson::Value& v = d1["content"];
	if (v.IsArray()) 
	{
		//这里一定要注意  变量i 一定要是   unsigned int  不然会报错
		for (unsigned int i = 0; i< v.Size(); ++i) 
		{   
			const rapidjson::Value &val = v[i];
			//log("%s",val.Size());
			for(unsigned int j = 0; j<val.Size(); ++j)
			{
				const rapidjson::Value &value = val[j];
				lines[i][j] = value.GetInt();
			}
		}
      
	}
}
void LinesManager::loadPlist()
{
	//std::string writeableList = FileUtils::getInstance()->sharedFileUtils()->getWritablePath();
	//std::string path = writeableList+"text.plist";
	Dictionary *rootDict = Dictionary::createWithContentsOfFile("ruitsPosition.plist");
	Dictionary* data1;
	Dictionary* data2;
	std::string node1;
	std::string node2;
	for(int i = 1; i <= 5;)
	{
		node1 = LinesManager::toString(i);
		data1 = dynamic_cast<Dictionary*>(rootDict->objectForKey(node1));
		for(int j = 1; j <= 3; j++)
		{
			node2 = node1+"_"+LinesManager::toString(j);
			data2 = dynamic_cast<Dictionary*>(data1->objectForKey(node2));
			
			int no = LinesManager::toInt((dynamic_cast<String*>(data2->objectForKey("no")))->getCString());
			int x = LinesManager::toInt((dynamic_cast<String*>(data2->objectForKey("x")))->getCString());
			int y = LinesManager::toInt((dynamic_cast<String*>(data2->objectForKey("y")))->getCString());
			int index = LinesManager::toInt((dynamic_cast<String*>(data2->objectForKey("index")))->getCString());
			RuitFrame frame(no, x, y, index);
			switch (i)
			{
			case 1:
				index1.push_back(frame);
				break;
			case 2:
				index2.push_back(frame);
				break;
			case 3:
				index3.push_back(frame);
				break;
			case 4:
				index4.push_back(frame);
				break;
			case 5:
				index5.push_back(frame);
				break;
			default:
				break;
			}			
		}
		++i;
	}
}
LinesManager::LinesManager()
{
}
LinesManager::~LinesManager()
{
}
LinesManager* LinesManager::lineManager = NULL;