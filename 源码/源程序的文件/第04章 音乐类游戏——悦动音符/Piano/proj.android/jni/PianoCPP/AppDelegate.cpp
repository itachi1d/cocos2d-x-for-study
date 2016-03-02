#include "AppDelegate.h"
#include "GameSceneManager.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{

}

//��ʼ������
bool AppDelegate::applicationDidFinishLaunching()
{
    //��ȡ����
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    //��������glview�����´���
    if(!glview)
    {
    	glview = GLView::create("Test Cpp");
    }
    //���û�����GLView
    director->setOpenGLView(glview);
    //����Ŀ��ֱ���,��ķֱ��ʵ���Ļ���Զ����»��������׽��ж�ֱ�������Ӧ
    glview->setDesignResolutionSize(960,540,ResolutionPolicy::SHOW_ALL);
	//����Ϊ��ʾFPS����Ϣ
    director->setDisplayStats(false);
    //ϵͳģ��ʱ����
    director->setAnimationInterval(1.0 / 60);

    //������ӭ����
    auto scene = new GameSceneManager;
    scene->createLogoScene();
    //��������ӭ������ʾ
    director->runWithScene(scene->logoScene);
    return true;
}

//����������̨ʱ���ô˷���
void AppDelegate::applicationDidEnterBackground()
{
	//ֹͣ����
    Director::getInstance()->stopAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();//��ͣ��������
}

//���������ǰ̨ʱ����
void AppDelegate::applicationWillEnterForeground()
{
	//��ʼ����
    Director::getInstance()->startAnimation();
    //����������Ļ�Ҫ��������һ�俪ʼ��������
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();//��ʼ��������
}
