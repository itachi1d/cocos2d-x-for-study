#include "MusicManager.h"

bool MusicManager::onSound = true;
bool MusicManager::onEffect = true;
bool MusicManager::noPlaySound = false;

void MusicManager::loadMusic()
{
	onEffect = UserDefault::getInstance()->getBoolForKey("5",true);
	onSound = UserDefault::getInstance()->getBoolForKey("6",true);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"BackOnTrack.mp3"					//���ر�������
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"menuLoop.mp3"					//���ر�������
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"CantLetGo.mp3"					//���ر�������
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//������Ч
				"explode_11.mp3"
			);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//������Ч
				"playSound_01.mp3"
			);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//������Ч
				"quitSound_01.mp3"
			);
}

void MusicManager::resumeBackgroundMusic()//������������
{
	onSound = true;
	UserDefault::getInstance()->setBoolForKey("6", onSound);
	UserDefault::getInstance()->flush();
	//������������
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	return;
}
void MusicManager::pauseBackgroundMusic()//��ͣ��������
{
	onSound = false;
	UserDefault::getInstance()->setBoolForKey("6", onSound);
	UserDefault::getInstance()->flush();
	//��ͣ��������
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	return;
}

void MusicManager::playExplosionEffect()//��Ч
{
	if(onEffect == false)
	{
		return;
	}
	//��ͣ��������
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explode_11.mp3");	//������Ч
	return;
}
void MusicManager::playFlyLayerEffect()//����ؿ�ʱ����Ч
{
	if(onEffect == false)
	{
		return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("playSound_01.mp3");	//������Ч
	return;
}
void MusicManager::playPauseMenuEffect()//��ͣ�˵��е���˵�ʱ����Ч
{
	if(onEffect == false)
	{
		return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("quitSound_01.mp3");	//������Ч
	return;
}
void MusicManager::playMenuLayerMusic()//�˵���������
{
	if(onSound == false)
	{
		return;
	}
	//���ű�������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"menuLoop.mp3",
		true
	);
	return;
}
void MusicManager::playGameLayerMusic()
{
	if(onSound == false)
	{
		return;
	}
	//���ű�������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"BackOnTrack.mp3",
		true
	);
	return;

}
void MusicManager::playFlyLayerMusic()//FlyLayer�ı�������
{
	if(onSound == false)
	{
		return;
	}
	//���ű�������
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"CantLetGo.mp3",
		true
	);
	return;
}
