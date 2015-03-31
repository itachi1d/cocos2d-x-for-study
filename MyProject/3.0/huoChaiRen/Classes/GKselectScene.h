

#include "cocos2d.h"
USING_NS_CC;
class GKselectScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	void initTitle();
	void initGuanKa();

	void goToGame(int guanKa);
	void initButton();
	void comeBackMain();
	void NextYeMian();
	void returnYeMian();
	void backButtonListener();
	//void onEnter();
	
    CREATE_FUNC(GKselectScene);
private:
	Texture2D *itemImage;
};