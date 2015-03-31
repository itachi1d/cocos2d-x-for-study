#pragma once
#ifndef _SceneSelect_h_
#define _SceneSelect_h_

#include <string>
#include <vector>

#include "cocos2d.h"
#include "extensions/cocos-ext.h""

USING_NS_CC;
USING_NS_CC_EXT;

class SceneSelect :
	public Layer,public TableViewDataSource,public TableViewDelegate
{
public:
	SceneSelect(void);
	~SceneSelect(void);

	bool init();
	void createSceneWithIndex(unsigned short int index );
	void menuCloseCallback(CCObject* pSender);
	void setRandomNumber();
	void loadXML();
	void saveXML();

	CREATE_FUNC(SceneSelect);

    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);

	
private:
	CCSize win_size_;
	std::vector<std::string> cell_items_;
	unsigned int cell_num_;
	int a[20];
};

#endif