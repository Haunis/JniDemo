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
jobject g_instance_jni;
jobject g_instance_java;

//instance: MainActivity 对象
void update_java_ui(JNIEnv *env, jobject instance) {
    jclass JNIUtilClass = env->GetObjectClass(instance);
    // 拿到JNIUtil的updateUI 方法
    const char *sig = "()V";
    jmethodID updateUI = env->GetMethodID(JNIUtilClass, "updateUI", sig);

    env->CallVoidMethod(instance, updateUI);
}

void *func(void *pVoid) {
    LOGI("jni-> func ...");

    // 调用的话，一定需要JNIEnv *env
    // JNIEnv *env 无法跨越线程，只有JavaVM才能跨越线程

    JNIEnv *env = NULL; // 全新的env
    int result = g_jvm->AttachCurrentThread(&env, 0); //把native的线程，附加到JVM
    if (result != 0) {
        return 0;
    }

//    update_java_ui(env, g_instance_jniutil); //error; 直接提全局的g_instance_ori不能跨线程传输
    update_java_ui(env, g_instance_jni);

    // 解除附加到 JVM 的native线程
    g_jvm->DetachCurrentThread();

    return 0;
}


extern "C" JNIEXPORT void JNICALL Java_com_jiage_demo_JNIUtil_native_1start_1thread
        (JNIEnv *env, jobject instance) {
    LOGI("jni--> start thread, env=%#x, instance=%#x", env, instance);
    if (g_instance_java != NULL) {
        update_java_ui(env, g_instance_java);
    }
    //获取jvm
    env->GetJavaVM(&g_jvm);

    // 提全局； 不会被释放，所以可以在线程里面用
    // g_instance不能和instance同名，否则提全局无效
    g_instance_jni = env->NewGlobalRef(instance);
    g_instance_java = instance; //不能跨线程传输，也不能被其他jni方法调用

    // 如果是非全局的，函数一结束，就被释放了
    pthread_t tid;
    pthread_create(&tid, 0, func, instance);
    pthread_join(tid, 0);

}


extern "C" JNIEXPORT void JNICALL Java_com_jiage_demo_JNIUtil_native_1rm_1global_1ref
        (JNIEnv *env, jobject instance) {
    LOGI("native_rm_global_ref, env=%#x, instance=%#x", env, instance);

    //MainActivity.onDestroy()里调用的话会error;
    //但如果是非MainActivity.onDestroy()就ok
//    if (g_instance_jniutil != NULL)update_java_ui(env, g_instance_jniutil);
    if (g_instance_jni != NULL)update_java_ui(env, g_instance_jni);

    if (NULL != g_instance_jni) {
        env->DeleteGlobalRef(g_instance_jni);
        g_instance_jni = NULL;
    }

}