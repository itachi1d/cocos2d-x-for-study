LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := geolib/BNGen_geolib.cpp \
				   bnGeolibHelper/BNPolyObject.cpp \
				   bnGeolibHelper/CalUtil.cpp \
				   bnGeolibHelper/WDHelp.cpp \
				   bnGeolibHelper/IsNotCut.cpp \
				   gamecpp/main.cpp \
                   gamecpp/AppDelegate.cpp \
                   gamecpp/GameSceneManager.cpp \
                   gamecpp/ChoiceLayer.cpp \
                   gamecpp/LevelLayer.cpp \
                   gamecpp/SetLayer.cpp \
                   gamecpp/MyFCData.cpp \
                   gamecpp/GameLayer.cpp \
                   gamecpp/WelcomeLayer.cpp \
                   gamecpp/HelpLayer.cpp \
                   bnBox2DHelp/CirclePhyObject.cpp \
                   bnBox2DHelp/EdgePhyObject.cpp \
                   bnBox2DHelp/PhyObject.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

$(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
