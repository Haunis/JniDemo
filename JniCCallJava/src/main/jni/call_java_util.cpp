#include "com_jiage_jniccalljava_Utils.h"
#include <android/log.h>
#include <unistd.h>

#define LOG_TAG "jni_tag_cpp"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);

/**
 * jni调用java代码
 * 1. 找类： FindClass函数传入类名com/zyx/jnidemo/JNIUtils来找到类
 * 2. 找方法： GetStaticMethodID函数传入类的变量、方法名 和 方法签名来找到方法
 * 3. 调用方法： 通过JNIEnv对象的CallStaticObjectMethod函数传入类、方法和两个对应的参数来完成调用
 *
 * 1. 获取字节码
 * 1.1 通过类的名称(包名，但是要用"/"替换'".")来获取jclass。
 *      jclass FindClass(const char* clsName)
 *      比如：jclass clazz = env->FindClass("com/zyx/jnidemo/JNIUtils");
 * 1.2 通过对象实例来获取jclass，相当于Java中的getClass()函数
 *      jclass GetObjectClass(jobject obj)
 * 1.3通过jclass可以获取其父类的jclass对象
 *      jclass getSuperClass(jclass obj)
 *
 *
 * 2.获取属性和方法
 * 获取属性:
 *      jfieldID GetFieldID(jclass clazz, const char* name, const char* sig)
 * 获取静态属性:
 *      jfieldID GetStaticFieldID(jclass clazz, const char* name, const char* sig)
 * 获取个方法:
 *      jmethodID GetMethodID(jclass clazz, const char* name, const char* sig)
 * 获取静态方法:
 *      jmethodID GetStaticMethodID(jclass clazz, const char* name, const char* sig)
 *      比如：jmethodID methodId = env->GetStaticMethodID(clazz,"getJavaInfo", "(Ljava/lang/String;I)Ljava/lang/String;");
 *
 * 3.调用方法
 *   env->CallStaticXXXMethod(JNIEnv, jclass, jmethodID, ...);
 *   env->CallXXXMethod(JNIEnv, jobject, jmethodID, ...);
 *
 * 4.构造一个对象
 *  jobject NewObject(jclass clazz, jmethodID methodID, ...)
 *  jobject NewObjectA(jclass clazz, jmethodID methodID, const jvalue* args)
 *  jobject NewObjectV(jclass clazz, jmethodIDmethodID,va_list args)
 *
 *
 */

//extern "C" JNIEXPORT void JNICALL Java_com_jiage_jniccalljava_Utils_callC(JNIEnv *env, jobject thiz) { //ok
JNIEXPORT void JNICALL Java_com_jiage_jniccalljava_Utils_callC(JNIEnv *env, jobject thiz) { //这样也ok

    LOGE("jni called ,sleeping ...");

    usleep(3 * 1000 * 1000);

    //1.获取字节码文件,第二个参数类似java里的包名，但c不识别包名。所以用“/”代替
    jclass jclazz = env->FindClass("com/jiage/jniccalljava/Utils");

    /*2.获取方法id;
     *第三个参数是方法名，第四个参数是方法签名--方法名和方法签名确定这个唯一函数
     */
    jmethodID method_id_string = env->GetMethodID(jclazz, "printD", "(Ljava/lang/String;)V");
    jmethodID method_id_int = env->GetMethodID(jclazz, "printD", "(I)V");

    jmethodID method_id_string_static = env->GetStaticMethodID(jclazz, "printString",
                                                               "(Ljava/lang/String;)V");
    /*
     * 3.调用方法 ; (*CallVoidMethod)(JNIEnv*, jobject, jmethodID, ...);
     * 第二个参数是java中该方法的对象，就是thiz
     * 返回值是void所以是CallVoidMethod
     */
    env->CallVoidMethod(thiz, method_id_string, env->NewStringUTF("msg_from_jni, cpp"));
    env->CallVoidMethod(thiz, method_id_int, 100);

    for (int i = 0; i < 2; i++) {
        env->CallStaticVoidMethod(jclazz, method_id_string_static,
                                  env->NewStringUTF("msg_from_jni static, cpp"));
//        usleep(1 * 1000 * 1000);
//        jclazz = 0;//置为空
    }


#define printD(...) env->CallVoidMethod(thiz, method_id_int, __VA_ARGS__);//在文件头和此位置定义宏都行;
    printD(200);//就是宏展开

}


