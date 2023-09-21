/**
 *
 * 虚拟机不知道原生线程，因此它们不能与 Java 构建直接通信。
 * 为了与应用的依然活跃部分交互，原生线程应该先附着在虚拟机上
 *
 * JavaVM 是虚拟机在JNI 层的代表，一个进程只有一个 JavaVM，所有的线程共用一个JavaVM。
 *
 * jvm->AttachCurrentThread(&env,0);//把native线程附着到JVM上
 * jvm->DetachCurrentThread();//解除附着到JVM的native线程
 */

#include "common.h"
#include <pthread.h>

JavaVM *g_jvm;
//jobject instance; //不同和局部引用同名
jobject g_instance;

void *func(void *pVoid) {
    LOGI("jni-> func ...");

    // 调用的话，一定需要JNIEnv *env
    // JNIEnv *env 无法跨越线程，只有JavaVM才能跨越线程

    JNIEnv *env = NULL; // 全新的env
    int result = g_jvm->AttachCurrentThread(&env, 0); //把native的线程，附加到JVM
    if (result != 0) {
        return 0;
    }

    if (g_instance == nullptr) {
        LOGE("jni--> g_instance is null");
    } else {
        LOGE("jni--> g_instance not null, addr=%p", g_instance);
    }

    jclass JNIUtilClass = env->GetObjectClass(g_instance);
    // 拿到JNIUtil的updateUI 方法
    const char *sig = "()V";
    jmethodID updateUI = env->GetMethodID(JNIUtilClass, "updateUI", sig);

    env->CallVoidMethod(g_instance, updateUI);

    // 解除附加到 JVM 的native线程
    g_jvm->DetachCurrentThread();

    return 0;
}


extern "C" JNIEXPORT void JNICALL Java_com_jiage_demo_JNIUtil_native_1start_1thread
        (JNIEnv *env, jobject instance) {
    LOGI("jni--> start thread");

    //获取jvm
    env->GetJavaVM(&g_jvm);

    // 提全局； 不会被释放，所以可以在线程里面用
    // g_instance不能和instance同名，否则提全局无效
    g_instance = env->NewGlobalRef(instance);

    // 如果是非全局的，函数一结束，就被释放了
    pthread_t tid;
    pthread_create(&tid, 0, func, instance);
    pthread_join(tid, 0);

}


extern "C" JNIEXPORT void JNICALL Java_com_jiage_demo_JNIUtil_native_1rm_1global_1ref
        (JNIEnv *env, jobject instance) {
    if (NULL != instance) {
        env->DeleteGlobalRef(instance);
        instance = NULL;
    }

}