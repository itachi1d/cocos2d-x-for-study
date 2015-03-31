
#include "cocos2d.h"
USING_NS_CC;
class MainMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	void replaceSceleGKScene();
	void goOnGame();
	void chickSoundButton(Node *node);
    void backButtonListener();
	void initEscMenu();
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};