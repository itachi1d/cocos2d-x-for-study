LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := CityRacingCPP/main.cpp \
                   CityRacingCPP/AppDelegate.cpp \
                   CityRacingCPP/CityRacingSceneManager.cpp \
                   CityRacingCPP/StartLayer.cpp \
                   CityRacingCPP/ChooseCarLayer.cpp \
                   CityRacingCPP/GameLayer.cpp \
                   CityRacingCPP/MyCar.cpp \
                   CityRacingCPP/PlayerCar.cpp \
                   CityRacingCPP/EnemyCar.cpp \
                   CityRacingCPP/CollisionTest.cpp \
                   CityRacingCPP/CarFatherClass.cpp \
                   CityRacingCPP/Coin.cpp \
                   CityRacingCPP/Rocket.cpp \
                   CityRacingCPP/ChooseLevelLayer.cpp \
                   CityRacingCPP/Constant.cpp \
                   CityRacingCPP/ShopLayer.cpp \
                   CityRacingCPP/PHBLayer.cpp \
                   CityRacingCPP/HelpLayer.cpp \
                   CityRacingCPP/GameOverLayer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
 LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
 LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
 $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
 $(call import-module,extensions)
