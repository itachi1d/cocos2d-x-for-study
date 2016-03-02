#include "MusicManager.h"

bool MusicManager::onSound = true;
bool MusicManager::onEffect = true;
bool MusicManager::noPlaySound = false;

void MusicManager::loadMusic()
{
	onEffect = UserDefault::getInstance()->getBoolForKey("5",true);
	onSound = UserDefault::getInstance()->getBoolForKey("6",true);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"BackOnTrack.mp3"					//¼ÓÔØ±³¾°ÒôÀÖ
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"menuLoop.mp3"					//¼ÓÔØ±³¾°ÒôÀÖ
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
							"CantLetGo.mp3"					//¼ÓÔØ±³¾°ÒôÀÖ
						);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//¼ÓÔØÒôÐ§
				"explode_11.mp3"
			);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//¼ÓÔØÒôÐ§
				"playSound_01.mp3"
			);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(				//¼ÓÔØÒôÐ§
				"quitSound_01.mp3"
			);
}

void MusicManager::resumeBackgroundMusic()//¼ÌÐø±³¾°ÒôÀÖ
{
	onSound = true;
	UserDefault::getInstance()->setBoolForKey("6", onSound);
	UserDefault::getInstance()->flush();
	//¼ÌÐø±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	return;
}
void MusicManager::pauseBackgroundMusic()//ÔÝÍ£±³¾°ÒôÀÖ
{
	onSound = false;
	UserDefault::getInstance()->setBoolForKey("6", onSound);
	UserDefault::getInstance()->flush();
	//ÔÝÍ£±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	return;
}

void MusicManager::playExplosionEffect()//ÒôÐ§
{
	if(onEffect == false)
	{
		return;
	}
	//ÔÝÍ£±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explode_11.mp3");	//²¥·ÅÒôÐ§
	return;
}
void MusicManager::playFlyLayerEffect()//½øÈë¹Ø¿¨Ê±µÄÒôÐ§
{
	if(onEffect == false)
	{
		return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("playSound_01.mp3");	//²¥·ÅÒôÐ§
	return;
}
void MusicManager::playPauseMenuEffect()//ÔÝÍ£²Ëµ¥ÖÐµã»÷²Ëµ¥Ê±µÄÒôÐ§
{
	if(onEffect == false)
	{
		return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("quitSound_01.mp3");	//²¥·ÅÒôÐ§
	return;
}
void MusicManager::playMenuLayerMusic()//²Ëµ¥±³¾°ÒôÀÖ
{
	if(onSound == false)
	{
		return;
	}
	//²¥·Å±³¾°ÒôÀÖ
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
	//²¥·Å±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"BackOnTrack.mp3",
		true
	);
	return;

}
void MusicManager::playFlyLayerMusic()//FlyLayerµÄ±³¾°ÒôÀÖ
{
	if(onSound == false)
	{
		return;
	}
	//²¥·Å±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic
	(
		"CantLetGo.mp3",
		true
	);
	return;
}
