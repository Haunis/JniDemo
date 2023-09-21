#include "com_jiage_demo_JNIUtil.h"
#include <android/log.h>
#include <stdlib.h>

#define LOG_TAG "JIA"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG, __VA_ARGS__)



/*定义C函数实现JNIUtil中的本地方法getStr
 *函数名的格式：Java_包名_类名_本地方法名
 *
 *env:JNINativeInterface结构体的二级指针，这是NDK提供的一个结构体，
 *  内部封装了很多函数指针，帮助程序员在开发JNI时实现一些常见需求
 *
 *thiz：JNIUtil对象
 */
JNIEXPORT jstring JNICALL
Java_com_jiage_demo_JNIUtil_getStr(JNIEnv *env, jobject thiz, jstring js) {
//定义C的字符串
    char *cstr = "中文和English";
    const char *c_string = NULL;
//    c_string = env->GetStringUTFChars(js, NULL); //c++
    c_string = (*env)->GetStringUTFChars(env, js, NULL); //c

    /*把C的字符串转换成java的字符串
      jstring     (*NewStringUTF)(JNIEnv*, const char*);
     */
    jstring jstr = (*env)->NewStringUTF(env, cstr);
    return jstr;
}

JNIEXPORT jint JNICALL Java_com_jiage_demo_JNIUtil_add
        (JNIEnv *env, jobject thiz, jint i, jint j) {
    return i + j;
}

JNIEXPORT jintArray JNICALL Java_com_jiage_demo_JNIUtil_transmitArray
        (JNIEnv *env, jobject thiz, jintArray array) {
    /*
     * 获取数组的首地址
     *
     * 函数GetIntArrayElements是个函数指针,函数如下:
     * jint*   (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
     * jint 就是int
     * jboolean 表示是否保留jintArray的拷贝，目前所有情况都传0表示不保留
     */
    int *arr_addr = (*env)->GetIntArrayElements(env, array, 0);
    LOGE("arr_addr:%#x", arr_addr);

    //获取数组的长度
    jsize length = (*env)->GetArrayLength(env, array);

    for (int i = 0; i < length; i++) {
        LOGE("jni log 原始数组>>：%d", *(arr_addr + i));//调用Android封装好的log
    }

    //直接将arr_addr指向的区域重新赋值,再返回给java行不通......
//    for (int i = 0; i < length; i++) {
//        *(arr_addr + i) = *(arr_addr + i) + 100;
//    }

    //创建需要返回的c数组
    jint c_int_array[length];
    for (int i = 0; i < length; i++) {
        c_int_array[i] = *(arr_addr + i) + 100;
    }
    // 将c数组转化成java需要的数组;
    // 转化后arr_addr指针指向的区域值保持不变,但array会另外开辟一个空间存储c_int_array
    (*env)->SetIntArrayRegion(env, array, 0, length, c_int_array);

    for (int i = 0; i < length; i++) {
        LOGE("jni log 转化后>>：%d", *(arr_addr + i)); //原指针arr_addr保存的值不变
    }

    int *arr_addr2 = (*env)->GetIntArrayElements(env, array, 0);
    LOGE("arr_addr:%#x", arr_addr2);//arr_addr2已改变,和arr_addr不同
    jsize length2 = (*env)->GetArrayLength(env, array);//获取数组的长度
    for (int i = 0; i < length2; i++) {
        LOGE("jni log 重新取数组地址后：%d", *(arr_addr2 + i));//新内存区域的值已经改变
    }
    return array;

}