LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/Components/AnimationComponent.cpp \
				   ../../Classes/Components/PositionComponent.cpp \
				   ../../Classes/Components/RenderComponent.cpp \
				   ../../Classes/Components/TextureComponent.cpp \
				   ../../Classes/Components/TouchComponent.cpp \
				   ../../Classes/Components/VelocityComponent.cpp \
				   ../../Classes/Evolve/Component/Component.cpp \
				   ../../Classes/Evolve/Component/ComponentType.cpp \
				   ../../Classes/Evolve/Entity/DelayedEntityProcessingSystem.cpp \
				   ../../Classes/Evolve/Entity/DelayedEntitySystem.cpp \
				   ../../Classes/Evolve/Entity/Entity.cpp \
				   ../../Classes/Evolve/Entity/EntityProcessingSystem.cpp \
				   ../../Classes/Evolve/Entity/EntitySystem.cpp \
				   ../../Classes/Evolve/Manager/ComponentTypeManager.cpp \
				   ../../Classes/Evolve/Manager/EntityManager.cpp \
				   ../../Classes/Evolve/Manager/GroupManager.cpp \
				   ../../Classes/Evolve/Manager/SystemBitManager.cpp \
				   ../../Classes/Evolve/Manager/SystemManager.cpp \
				   ../../Classes/Evolve/Manager/TagManager.cpp \
				   ../../Classes/Evolve/World/World.cpp \
				   ../../Classes/Layers/AnimationLayer.cpp \
				   ../../Classes/Layers/BaseLayer.cpp \
				   ../../Classes/Layers/HUDLayer.cpp \
				   ../../Classes/Layers/UILayer.cpp \
				   ../../Classes/Scenes/CombatScene.cpp \
				   ../../Classes/Scenes/HeroScene.cpp \
                   ../../Classes/Scenes/LoadingScene.cpp \
				   ../../Classes/Scenes/MainScene.cpp \
				   ../../Classes/Scenes/StoreScene.cpp \
				   ../../Classes/Systems/MovementSystem.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
