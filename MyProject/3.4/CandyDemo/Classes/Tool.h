#ifndef __TOOL_H__
#define __TOOL_H__
#include "cocos2d.h"
#include "Perf.h"

class Tool
 {
 public:
	static std::string toString(int x)
	{
		std::stringstream ss;
		ss<<x;
		std::string no;
		ss>>no;
		return no;
	}
	static int toInt(std::string str)
	{
		int var;
		std::stringstream ss;
		ss<<str;
		ss>>var;
		return var;
	}

	static Point world_to_true(MyPoint point)
	{
		return Point(point.true_x, point.true_y);
	}

	static MyPoint true_to_world(Point point)
	{
		return MyPoint((point.x-zero_point.x-TILED_WIDTH/2)/TILED_WIDTH, (point.y-zero_point.y-TILED_HEIGHT/2)/TILED_HEIGHT);
	}
	/*static std::string GBKToUTF8( const char* strGBK ) 
	{ 
		using namespace std; 
		int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);   
		wchar_t* wstr = new wchar_t[len+1];   
		memset(wstr, 0, len+1);   
		MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);   
		len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);   
		char* str = new char[len+1];   
		memset(str, 0, len+1);   
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);   
		string strTemp = str;   
		if(wstr) delete[] wstr;   
		if(str) delete[] str;   
		return strTemp;  
	} */
 };

#endif