LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES  = hellocpp/main.cpp
# [[[cog
# import list_classes
# cpps, includes = list_classes.listCppPaths()
#
# #### Write list of C++ files found
#
# cog.outl()
# for f in cpps:
#   cog.outl('LOCAL_SRC_FILES += %s' % f)
#
# #### Write list of subdirectories with source files found
#
# cog.outl()
# cog.outl('LOCAL_C_INCLUDES  = $(LOCAL_PATH)/../../Classes')
#
# #### Delete next 2 lines of code if you don't need list of subdirectories
#
# for d in includes:
#  cog.outl('LOCAL_C_INCLUDES += $(LOCAL_PATH)/%s' % d)
#
# cog.outl()
# ]]]

LOCAL_SRC_FILES += ../../Classes/AppDelegate.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Manager/Input_Manager.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Manager/Scene_Manager.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Manager/Sound_Manager.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/GameScene_Intro.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/MainTitle/GameScene_MainTitle.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/MainTitle/UI/GameUI_MainTitle.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/MainTitle/UI/GameUI_MainTitle_Invite.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/MainTitle/UI/GameUI_MainTitle_Rank.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/MainTitle/UI/GameUI_MainTitle_RoomList.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/MainTitle/UI/GameUI_MainTitle_Setting.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/MainTitle/UI/GameUI_MainTitle_Store.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/Match/GameScene_Match.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/Match/Layer/GameLayer_Match_Main.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/Match/Layer/GameLayer_Match_UI.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/Match/Map/Match_Map.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/Match/Othello/Othello_Logic.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/Match/Unit/Unit_Base.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/Match/Unit/Unit_Black.cpp
LOCAL_SRC_FILES += ../../Classes/Game/Scene/Match/Unit/Unit_White.cpp
LOCAL_SRC_FILES += ../../Classes/Game/UILayer_WaitBlack.cpp
LOCAL_SRC_FILES += ../../Classes/Game/UI_Utility.cpp
LOCAL_SRC_FILES += ../../Classes/Native/Native_Helper.cpp
LOCAL_SRC_FILES += ../../Classes/Network/Json/json_reader.cpp
LOCAL_SRC_FILES += ../../Classes/Network/Json/json_value.cpp
LOCAL_SRC_FILES += ../../Classes/Network/Json/json_writer.cpp
LOCAL_SRC_FILES += ../../Classes/Network/Room_Manager.cpp
LOCAL_SRC_FILES += ../../Classes/Network/Web/WebCommunication.cpp
LOCAL_SRC_FILES += ../../Classes/Social/Facebook/Binder/Facebook_Binder_Android.cpp
LOCAL_SRC_FILES += ../../Classes/Social/Facebook/Binder/Facebook_Binder_IOS.cpp
LOCAL_SRC_FILES += ../../Classes/Social/Facebook/Facebook_Manager.cpp

LOCAL_C_INCLUDES  = $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Game
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Game/Manager
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Game/Scene
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Game/Scene/MainTitle
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Game/Scene/MainTitle/UI
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Game/Scene/Match
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Game/Scene/Match/Layer
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Game/Scene/Match/Map
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Game/Scene/Match/Othello
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Game/Scene/Match/Unit
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Native
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Network
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Network/Json
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Network/Web
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Social
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Social/Facebook
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Social/Facebook/Binder

# [[[end]]]

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
