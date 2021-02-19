LOCAL_PATH := $(call my-dir)

##########将.lib/libdemo6.so复制到obj目录下##########
include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS  := lib/libdemo6.so
# include $(BUILD_PREBUILT) #erro,不能和LOCAL_PREBUILT_LIBS一块使用 
include $(BUILD_MULTI_PREBUILT)


##########编译libHelloJava.so############
include $(CLEAR_VARS)
LOCAL_MODULE    := libHelloJava
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/ #加入头文件路径
LOCAL_SRC_FILES := NativeJni.c
#LOCAL_LDLIBS    := -llog -ljnigraphics
LOCAL_SHARED_LIBRARIES := libdemo6 #使用mm编译的so
LOCAL_SHARED_LIBRARIES += liblog #使用系统库 liblog


LOCAL_MODULE_PATH := $(LOCAL_PATH)/out_lib

include $(BUILD_SHARED_LIBRARY)
