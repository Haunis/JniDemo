LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := HelloJava
LOCAL_SRC_FILES := NativeJni.c
#LOCAL_LDLIBS    := -llog -ljnigraphics
LOCAL_MODULE_PATH := $(LOCAL_PATH)/bin

include $(BUILD_SHARED_LIBRARY)
