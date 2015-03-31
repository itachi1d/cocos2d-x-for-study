// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2015-03-15 16:37:07 by jiangtao> */

/* @file Main_Layer.h
 * $Id: Main_Layer.h 2015-03-15 08:30:18 jiangtao 
 *
 * @author:Stone Jiang<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef MAIN_LAYER_H
#define MAIN_LAYER_H

#include "CSB_Layer.h"

class MainMenuLayer
	: public CSB_Layer
{
	typedef CSB_Layer Base;
	typedef MainMenuLayer Self;
public:
	MainMenuLayer ();
	virtual ~MainMenuLayer ();
	std::string get_csb_filename ();
	void set_callback (Node*);
	CREATE_FUNC (Self);
public:
	void highScore(cocos2d::Ref* pSender,ui::TouchEventType type);
	void gameStart(cocos2d::Ref* pSender,ui::TouchEventType type);
	void returnMain(cocos2d::Ref* pSender,ui::TouchEventType type);
	void shop(cocos2d::Ref* pSender,ui::TouchEventType type);
	void buy(cocos2d::Ref* pSender,ui::TouchEventType type);
};

#endif /* MAIN_LAYER_H */
