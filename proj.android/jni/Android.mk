LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/EntitySystem/Components/AnimationComponent.cpp \
				   ../../Classes/EntitySystem/Component.cpp \
				   ../../Classes/EntitySystem/Components/PositionComponent.cpp \
				   ../../Classes/EntitySystem/ComponentType.cpp \
				   ../../Classes/EntitySystem/ComponentTypeManager.cpp \
				   ../../Classes/EntitySystem/Components/RenderComponent.cpp \
				   ../../Classes/EntitySystem/Components/RotationComponent.cpp \
				   ../../Classes/EntitySystem/Components/TextureComponent.cpp \
				   ../../Classes/EntitySystem/Components/TouchComponent.cpp \
				   ../../Classes/EntitySystem/DelayedEntitySystem.cpp \
				   ../../Classes/EntitySystem/DelayedEntityProcessingSystem.cpp \
				   ../../Classes/EntitySystem/Entity.cpp \
				   ../../Classes/EntitySystem/EntityManager.cpp \
				   ../../Classes/EntitySystem/EntityProcessingSystem.cpp \
				   ../../Classes/EntitySystem/EntitySystem.cpp \
				   ../../Classes/EntitySystem/GroupManager.cpp \
				   ../../Classes/EntitySystem/SystemBitManager.cpp \
				   ../../Classes/EntitySystem/SystemManager.cpp \
				   ../../Classes/EntitySystem/TagManager.cpp \
				   ../../Classes/EntitySystem/World.cpp \
				   ../../Classes/Layers/AnimationLayer.cpp \
				   ../../Classes/Layers/BaseLayer.cpp \
				   ../../Classes/Layers/HUDLayer.cpp \
				   ../../Classes/Layers/UILayer.cpp \
				   ../../Classes/Scenes/CombatScene.cpp \
				   ../../Classes/Scenes/HeroScene.cpp \
                   ../../Classes/Scenes/LoadingScene.cpp \
				   ../../Classes/Scenes/MainScene.cpp \
				   ../../Classes/Scenes/StoreScene.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
