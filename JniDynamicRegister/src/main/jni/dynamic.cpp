
//#include "com_jiage_jnidynamicregister_DynamicUtils.h"

//JNIEXPORT jstring JNICALL Java_com_jiage_jnidynamicregister_DynamicUtils_getString
//        (JNIEnv *env, jclass clazz) {
//
//    char *str = "msg from dynamic register11";
//    return (**env).NewStringUTF(env, str);
//
//}

#include <jni.h>
#include <string>
#include <android/log.h>

#include <iostream>

#define TAG "native-lib"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG,  __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG,  __VA_ARGS__);

/**
 * TODO 动态注册
*/

/**
 * 对应java类的全路径名，.用/代替
 */
//const char *classPathName = "com/devyk/ndk_sample/MainActivity";
const char *classPathName = "com/jiagejnidynamicregister/DynamicUtils";

extern "C"  //支持 C 语言
JNIEXPORT void JNICALL //告诉虚拟机，这是jni函数
native_dynamicRegister(JNIEnv *env, jobject instance, jstring name) {
    const char *j_name = env->GetStringUTFChars(name, NULL);
    LOGD("动态注册: %s", j_name)
//释放
    env->ReleaseStringUTFChars(name, j_name);
}

/* 源码结构体
 * typedef struct {
    const char* name;
    const char* signature;
    void*       fnPtr;
    } JNINativeMethod;
 */
static const JNINativeMethod jniNativeMethod[] = {
        {"dynamicRegister", "(Ljava/lang/String;)V", (void *) (native_dynamicRegister)}
};

/**
 * 该函数定义在jni.h头文件中，System.loadLibrary()时会调用JNI_OnLoad()函数
 */
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *javaVm, void *pVoid) {
    //通过虚拟机 创建爱你全新的 evn
    JNIEnv *jniEnv = nullptr;
    jint result = javaVm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6);
    if (result != JNI_OK) {
        return JNI_ERR; // 主动报错
    }
    jclass mainActivityClass = jniEnv->FindClass(classPathName);
    jniEnv->RegisterNatives(mainActivityClass, jniNativeMethod,
                            sizeof(jniNativeMethod) / sizeof(JNINativeMethod));//动态注册的数量

    return JNI_VERSION_1_6;
}







