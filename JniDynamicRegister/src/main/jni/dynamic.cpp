
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

#define TAG "jni_tag_cpp"
// __VA_ARGS__ 代表 ...的可变参数
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG,  __VA_ARGS__);
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG,  __VA_ARGS__);

const char *classPathName = "com/jiage/jnidynamicregister/DynamicUtils";

extern "C"  //支持 C 语言
JNIEXPORT void JNICALL //告诉虚拟机，这是jni函数
func1(JNIEnv *env, jobject instance) {
    LOGE("func1 called: %s", "11111")
}

jstring func2(JNIEnv *env, jobject instance, jstring s) {
    const char *c_string = env->GetStringUTFChars(s, NULL);

    LOGE("func2 called: %s", c_string)
    env->ReleaseStringUTFChars(s, c_string);  //释放

    return env->NewStringUTF("msg from jni");
}

static const JNINativeMethod mMethods[] = {
        {"getString1", "()V",                                    (void *) func1},
        {"getString2", "(Ljava/lang/String;)Ljava/lang/String;", (void *) func2}
};

/**
 * 该函数定义在jni.h头文件中，System.loadLibrary()时会调用JNI_OnLoad()函数
 */
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *pVoid) {
    LOGE("OnLoad...")

    //通过虚拟机 创建全新的env
    JNIEnv *jniEnv = nullptr;
    jint result = vm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6);
    if (result != JNI_OK) {
        return JNI_ERR; // 主动报错
    }
    jclass javaClass = jniEnv->FindClass(classPathName);
    jniEnv->RegisterNatives(javaClass, mMethods,
                            sizeof(mMethods) / sizeof(JNINativeMethod));//动态注册的数量

    return JNI_VERSION_1_6;
}







