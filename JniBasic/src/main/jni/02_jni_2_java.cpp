/**
 * jni 返回数据到 java
 */

#include "common.h"

// --------------------------1. 接收string，返回string----------------------------
extern "C"  //支持 C 语言
JNIEXPORT jstring JNICALL //告诉虚拟机，这是jni函数
Java_com_jiage_demo_JNIUtil_jni2java_1str(JNIEnv *env, jobject thiz, jstring js) {

    const char *c_string = NULL;
    c_string = env->GetStringUTFChars(js, NULL); //c++
// c_string = (*env)->GetStringUTFChars(env, js, NULL); //c
    LOGI("jni--> java string = %s", c_string);

    //定义C的字符串
    char *cstr = "msg_from_jni";
    //把C的字符串转换成java的字符串
    jstring jstr = env->NewStringUTF(cstr);
    return jstr;
}

// --------------------------2. 接收int，返回int----------------------------
extern "C" JNIEXPORT jint JNICALL Java_com_jiage_demo_JNIUtil_jni2java_1int
        (JNIEnv *env, jobject thiz, jint i, jint j) {
    LOGI("jni--> java data: i=%d, j=%d", i, j);
    return i + j;
}

// --------------------------3. 接收int数组，返回int数组----------------------------
extern "C" JNIEXPORT jintArray JNICALL Java_com_jiage_demo_JNIUtil_jni2java_1intarr
        (JNIEnv *env, jobject thiz, jintArray array) {
    /*
     * 获取数组的首地址
     *
     * 函数GetIntArrayElements是个函数指针,函数如下:
     * jint*   (*GetIntArrayElements)(JNIEnv*, jintArray, jboolean*);
     * jint 就是int
     * jboolean 表示是否保留jintArray的拷贝，目前所有情况都传0表示不保留
     */
    int *arr_addr = env->GetIntArrayElements(array, 0);
    LOGE("jni arr_addr:%#x", arr_addr);

    //获取数组的长度
    jsize length = env->GetArrayLength(array);

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
    env->SetIntArrayRegion(array, 0, length, c_int_array);

    for (int i = 0; i < length; i++) {
        LOGE("jni log 转化后>>：%d", *(arr_addr + i)); //原指针arr_addr保存的值不变
    }

    int *arr_addr2 = env->GetIntArrayElements(array, 0);
    LOGE("arr_addr:%#x", arr_addr2);//arr_addr2已改变,和arr_addr不同
    jsize length2 = env->GetArrayLength(array);//获取数组的长度
    for (int i = 0; i < length2; i++) {
        LOGE("jni log 重新取数组地址后：%d", *(arr_addr2 + i));//新内存区域的值已经改变
    }
    return array;
}

// --------------------------4. 接收void，返回java对象----------------------------
//jni创建java对象，并返回给Java层
extern "C" JNIEXPORT jobject JNICALL Java_com_jiage_demo_JNIUtil_jni2java_1obj
        (JNIEnv *env, jobject instance) {
    //1. 拿到 Java 类的全路径
    const char *person_java = "com/jiage/demo/Person";
    const char *method = "<init>"; // Java构造方法的标识

    //2. 找到需要处理的 Java 对象 class
    jclass j_person_class = env->FindClass(person_java);

    //3. 拿到空参构造方法
    jmethodID person_constructor = env->GetMethodID(j_person_class, method, "()V");

    //4. 创建对象
    jobject person_obj = env->NewObject(j_person_class, person_constructor);

    //5. 拿到 setName 方法的签名，并拿到对应的 setName 方法
    const char *nameSig = "(Ljava/lang/String;)V";
    jmethodID nameMethodId = env->GetMethodID(j_person_class, "setName", nameSig);

    //6. 拿到 setAge 方法的签名，并拿到 setAge 方法
    const char *ageSig = "(I)V";
    jmethodID ageMethodId = env->GetMethodID(j_person_class, "setAge", ageSig);

    //7. 正在调用 Java 对象的方法
    const char *name = "张三";
    jstring newStringName = env->NewStringUTF(name);
    env->CallVoidMethod(person_obj, nameMethodId, newStringName);
    env->CallVoidMethod(person_obj, ageMethodId, 28);

    const char *sig = "()Ljava/lang/String;";
    jmethodID jtoString = env->GetMethodID(j_person_class, "toString", sig);
    jobject obj_string = env->CallObjectMethod(person_obj, jtoString);
    jstring perStr = static_cast<jstring >(obj_string); //jobject 强转成jstring
    const char *itemStr2 = env->GetStringUTFChars(perStr, NULL);
    LOGD("Jni Person: %s", itemStr2);
    return person_obj;
}




