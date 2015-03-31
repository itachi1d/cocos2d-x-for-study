#include "CanShu.h"

Rect bgRect3(2, 3, 640, 958);
Rect bgRect2(644, 3, 640, 958);
Rect bgRect1(1286, 3, 640, 958);

Rect playerRect4(0, 0, 1, 1);
Rect playerRect1_1(2, 2, 120, 95);
Rect playerRect1_2(124, 2, 120, 95);
Rect playerRect2_1(246, 2, 120, 95);
Rect playerRect2_2(368, 2, 120, 95);
Rect playerRect3_1(490, 2, 85, 110);
Rect playerRect3_2(577, 2, 85, 110);
Rect ziDanRect1(279, 2, 60, 17);
Rect ziDanRect2(252, 2, 25, 50);

Rect JiGziDanLeftRect(924, 924, 7, 50);
Rect JiGziDanCenterRect(924, 924, 5, 50);
Rect JiGziDanRightRect(924, 924, 7, 50);
Rect JiGziDanLeftViewRect(24, 5, 10, 480);
Rect JiGziDanCenterViewRect(5, 5, 5, 480);
Rect JiGziDanRightViewRect(56, 5, 10, 480);

Rect diJiRect0(736, 2, 70, 70);
Rect diJiRect1(664, 2, 70, 70);
Rect diJiRect2(808, 2, 140, 92);
Rect diJiRect3(2, 114, 187, 154);
Rect diJiRect4(191, 114, 163, 300);

Rect DiJi_Bullet0(341, 2, 15, 14);
Rect DiJi_Bullet1(358, 2, 70, 23);
Rect DiJi_Bullet2(430, 2, 61, 15);
Rect DiJi_Bullet3(493, 2, 23, 19);
Rect DiJi_Bullet4(518, 2, 41, 12);
Rect DiJi_Bullet5(561, 2, 26, 28);
Rect DiJi_Bullet6(589, 2, 30, 11);
Rect DiJi_Bullet7(621, 2, 23, 23);


Rect DiJi_Shut0(2, 2, 22, 36);

Rect shutAnimation1(468, 2, 91, 127);
Rect shutAnimation2(561, 2, 91, 127);
Rect JGbinGoAnimation1(68, 2, 120, 30);
Rect JGbinGoAnimation2(190, 2, 120, 30);

Rect sdAnimation1(96, 2, 50, 480);
Rect sdAnimation2(560, 560, 50, 480);
Rect sdAnimation3(560, 560, 50, 480);
Rect sdAnimation4(148, 2, 50, 480);
Rect sdAnimation5(560, 560, 50, 480);
Rect sdAnimation6(560, 560, 50, 480);
Rect sdAnimation7(200, 2, 50, 480);


bool isSoundOpen = true;
int bulletType = 2;
int bulletLevel = 0;
int playerLife = 3;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
std::string boom_sound = "music/boom.ogg";
std::string bg_sound2 = "music/bg2.ogg";
std::string max_sound = "music/max.ogg";
std::string maxing1_sound = "music/maxing1.ogg";
#endif
std::string boom_sound = "music/boom.mp3";
std::string bg_sound2 = "music/bg2.mp3";
std::string max_sound = "music/max.mp3";
std::string maxing1_sound = "music/maxing1.mp3";