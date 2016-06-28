#pragma one
#include "AData.h"

class MainDataMgr
{
public:
	bool soundFlag;
	bool musicFlag;
public:
	static MainDataMgr* s_mainData;
public:
	static MainDataMgr* getInstance();
private:
	MainDataMgr() : soundFlag(true), musicFlag(true){};
};