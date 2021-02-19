/*
 	Created by haunis on 20-2-26.
	函数命名:类所在路径+方法名,即在Android Studio Copy Reference即是	
*/
#include <android/log.h>
#include "com_jiage_jnindkbuild_Native.h"
#include <my_add.h>
//定义输出的TAG
//const char * LOG_TAG = "JIA";
#define LOG_TAG "JIA"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__) 
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__) 
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__) 
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__) 
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__) 


JNIEXPORT jstring JNICALL Java_com_jiage_jnindkbuild_Native_getString
        (JNIEnv * env, jclass j){
	char *str = "hello from jni, build by mm";
	int ret = my_add(3,4);
	LOGE("jni log: ret= %d, send=%s", ret,str);
	return (**env).NewStringUTF(env,str);

}

