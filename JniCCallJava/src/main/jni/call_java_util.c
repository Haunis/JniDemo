#include "com_jiage_jniccalljava_Utils.h"
#include <android/log.h>
#include <unistd.h>

#define LOG_TAG "jni_tag_c"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);


JNIEXPORT void JNICALL Java_com_jiage_jniccalljava_Utils_callC(JNIEnv *env, jobject thiz) {

    LOGE("jni called, sleeping... ");

    usleep(3 * 1000 * 1000);

    //1.获取字节码文件,第二个参数类似java里的包名，但c不识别包名。所以用“/”代替
    jclass jclazz = (*env)->FindClass(env, "com/jiage/jniccalljava/Utils");

    /*2.获取方法id;
     *第三个参数是方法名，第四个参数是方法签名--方法名和方法签名确定这个唯一函数
     */
    jmethodID method_id_string = (*env)->GetMethodID(env, jclazz, "printD",
                                                     "(Ljava/lang/String;)V");
    jmethodID method_id_int = (*env)->GetMethodID(env, jclazz, "printD", "(I)V");

    jmethodID method_id_string_static = (*env)->GetStaticMethodID(env, jclazz, "printString",
                                                                  "(Ljava/lang/String;)V");
    /*
     * 3.调用方法 ; (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
     * 第二个参数是java中该方法的对象，就是thiz
     * 返回值是void所以是CallVoidMethod
     */
    (*env)->CallVoidMethod(env, thiz, method_id_string, (*env)->NewStringUTF(env, "msg_from_jni"));
    (*env)->CallVoidMethod(env, thiz, method_id_int, 100);

    for (int i = 0; i < 2; i++) {
        (*env)->CallStaticVoidMethod(env, jclazz, method_id_string_static,
                                     (*env)->NewStringUTF(env, "msg_from_jni static"));
//        usleep(1 * 1000 * 1000);
//        jclazz = 0;//置为空
    }


#define printD(...) (*env)->CallVoidMethod(env, thiz, method_id_int, __VA_ARGS__);//在文件头和此位置定义宏都行;
    printD(200);//就是宏展开

}


