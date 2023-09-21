/**
 *  jni可利用java对象锁进行同步.
 *
 *  同步是多线程程序设计最终的特征，JNI 监视器允许原生代码利用Java对象同步，
 *  虚拟机保证存取监视器的线程能够安全执行，而其他线程等待监视器对象变成可用状态
 *
 *  MonitorEnter函数的调用应该与对 MonitorExit的调用相匹配，从而避免代码出现死锁。
 *
 */

#include "common.h"

//进入管程，抢占锁
void enter_monitor(JNIEnv *env, jobject instance) {
    if (env->MonitorEnter(instance) != JNI_OK) {
        LOGE("%s: MonitorEnter() failed", __FUNCTION__);
    }
}

//退出管程，释放锁
void exit_monitor(JNIEnv *env, jobject instance) {
    if (env->ExceptionOccurred()) {
        LOGE("ExceptionOccurred()...");
        if (env->MonitorExit(instance) != JNI_OK) {
            LOGE("%s: MonitorExit() failed", __FUNCTION__);
        }
    }

    if (env->MonitorExit(instance) != JNI_OK) {
        LOGE("%s: MonitorExit() failed", __FUNCTION__);
    }
}

extern "C" JNIEXPORT void JNICALL Java_com_jiage_demo_JNIUtil_native_1jni_1sync_1count
        (JNIEnv *env, jobject instance) {

    jclass cls = env->GetObjectClass(instance);
    jfieldID fieldID = env->GetFieldID(cls, "count", "I");


    //抢占instance锁--对应java层的JNIUtil对象锁;
    //如果没有这部分同步代码的话，对count的操作是不安全的
    enter_monitor(env, instance);

    /* synchronized block */
    int val = env->GetIntField(instance, fieldID);
    val++;
    LOGI("jni--> count=%d", val);
    env->SetIntField(instance, fieldID, val);

    //释放instance锁
    exit_monitor(env, instance);


}
