#include <android/log.h>
//定义输出的TAG
//const char * LOG_TAG = "JIA";
#define LOG_TAG "JIA" //定义宏 ,相当于Java里的封装，但C没有封装这个概念
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);

#include "com_jiage_jnidynamicregister_DynamicUtils.h"

JNIEXPORT jstring JNICALL Java_com_jiage_jnidynamicregister_DynamicUtils_getString
        (JNIEnv *env, jclass clazz, jstring string) {
    const char *c_string = (*env)->GetStringUTFChars(env, string, NULL);
    LOGE("jni string-->%s", c_string);
    char *str = "msg from dynamic register11";
    return (**env).NewStringUTF(env, str);

}








