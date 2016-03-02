LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   hellocpp/AppDelegate.cpp \
                   hellocpp/GameSceneManager.cpp \
                   hellocpp/GameLayer.cpp \
                   hellocpp/GDData.cpp \
                   hellocpp/LevelLayer.cpp \
                   hellocpp/MenuLayer.cpp \
                   hellocpp/FlyLayer.cpp \
                   hellocpp/ChoiceCubeLayer.cpp \
                   hellocpp/MusicLayer.cpp \
                   frameHelp/SpriteManager.cpp \
                   frameHelp/PauseCode.cpp \
                   frameHelp/MusicManager.cpp \
                   frameHelp/LevelLayerHelp.cpp \
                   frameHelp/MenuLayerHelp.cpp \
                   frameHelp/ChoiceCubeLayerHelp.cpp \
                   frameHelp/MusicLayerHelp.cpp \
                   objectHelp/Barrier.cpp \
                   objectHelp/JumpCube.cpp \
                   objectHelp/FlyObject.cpp \
                   objectHelp/RectBarrier.cpp \
                   objectHelp/TriangleBarrier.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static



include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,extensions)
# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)

