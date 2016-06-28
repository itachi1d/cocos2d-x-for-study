#include "MainDataMgr.h"

MainDataMgr* MainDataMgr::s_mainData;

MainDataMgr* MainDataMgr::getInstance()
{
	if (!s_mainData)
	{
		s_mainData = new MainDataMgr();
	}
	return s_mainData;
}
