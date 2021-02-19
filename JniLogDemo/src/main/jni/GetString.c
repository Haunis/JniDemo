#include "com_jiage_jnilogdemo_MainActivity.h"

#include <android/log.h>
//定义输出的TAG
//const char * LOG_TAG = "JIA";
#define LOG_TAG "JIA" //定义宏 ,相当于Java里的封装，但C没有封装这个概念
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__);

JNIEXPORT jstring JNICALL Java_com_jiage_jnilogdemo_MainActivity_getCString
        (JNIEnv *env, jobject thiz) {
    char *p = "hello From c 名字";
    jstring jstr = (*env)->NewStringUTF(env, p);

//    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "hello native log 随意的文字");
    LOGD("debgu 级输出");
    LOGI("info 级别输出");

    return jstr;
}

