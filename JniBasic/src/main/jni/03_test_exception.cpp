#include "common.h"

//测试异常； jni调用java层方法，java层方法抛出异常
extern "C" JNIEXPORT void JNICALL Java_com_jiage_demo_JNIUtil_native_1test_1exception
        (JNIEnv *env, jobject instance, jstring name) {
    const char *j_name = env->GetStringUTFChars(name, NULL);
    LOGD("Jni test_exception called, name=%s .... ", j_name);

    jclass clazz = env->GetObjectClass(instance);//拿到当前类的class
    jmethodID mid = env->GetMethodID(clazz, "testException", "()V");//执行 Java 测试抛出异常的代码
    env->CallVoidMethod(instance, mid); // 执行会抛出一个异常
    jthrowable exc = env->ExceptionOccurred(); // 检测是否发生异常
    if (exc) {//如果发生异常
        env->ExceptionDescribe(); // 打印异常信息
        env->ExceptionClear(); // 清除掉发生的异常
        jclass newExcCls = env->FindClass("java/lang/IllegalArgumentException");
        env->ThrowNew(newExcCls, "JNI 中发生了一个异常信息"); // 返回一个新的异常到 Java
    }

    //释放
    env->ReleaseStringUTFChars(name, j_name);
}
