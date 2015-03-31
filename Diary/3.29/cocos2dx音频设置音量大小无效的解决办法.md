# 音频设置音量大小不起作用

## 今天项目需求背景音乐声音需要调节音量大小，发现SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);并不起作用，查看源文件，发现这个方法并没有实现，要解决这个问题：
1.查看http://m.blog.csdn.net/blog/xie1xiao1jun/40864585。

2.将本文件痛目录的两个文件（MciPlayer.h;SimpleAudioEngine.cpp）覆盖项目cocos2d\cocos\audio\win32\目录下的两个同名文件