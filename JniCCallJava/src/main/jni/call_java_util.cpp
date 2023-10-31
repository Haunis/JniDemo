/**
 * jni调用java层方法、获取java层对象的成员变量
 *
 * 注意事项：
 *      https://blog.csdn.net/xingfeng2010/article/details/65214614
 *      在static的native方法里，java传来的instance不是对象，而是类！！！因此不能使用该instance调用java非static方法
 *
 *  env->findClass("com.xxx.xxx")和env->GetObjectClass(instance)的区别：
 *      https://blog.csdn.net/liu_12345_liu/article/details/131154935
 *      https://blog.csdn.net/yizhongliu/article/details/107516539
 *      findClass: 在jni新线程如pthread_create中使用就会报错，因为没有堆栈帧，所以findClass()会到系统类加载器
 *                 而不是到应用关联的类加载器寻找，因此会报"ClassNotFoundException"
 *      GetObjectClass: 使用java对象的实例找到对应的class，提全局后可以跨线程使用。注意env不能跨线程！！！
 *
 * jni调用java代码步骤
 *      1. 找类： FindClass函数传入类名com/zyx/jnidemo/JNIUtils来找到类
 *      2. 找方法： GetStaticMethodID函数传入类的变量、方法名 和 方法签名来找到方法
 *      3. 调用方法： 通过JNIEnv对象的CallStaticObjectMethod函数传入类、方法和两个对应的参数来完成调用
 *
 * 1. 获取字节码
 *      1.1 通过类的名称(包名，但是要用"/"替换'".")来获取jclass。
 *           注意: 该方法在跨线程中使用env无效！！！
 *           jclass FindClass(const char* clsName)
 *           比如：jclass clazz = env->FindClass("com/zyx/jnidemo/JNIUtils");
 *      1.2 通过对象实例来获取jclass，相当于Java中的getClass()函数
 *           注意: 该obj不能是静态jni方法传来的！！！！
 *           jclass GetObjectClass(jobject obj)
 *      1.3通过jclass可以获取其父类的jclass对象
 *          jclass getSuperClass(jclass obj)
 *
 *
 * 2.获取属性和方法的签名
 *      获取属性:
 *           jfieldID GetFieldID(jclass clazz, const char* name, const char* sig)
 *      获取静态属性:
 *           jfieldID GetStaticFieldID(jclass clazz, const char* name, const char* sig)
 *      获取个方法:
 *           jmethodID GetMethodID(jclass clazz, const char* name, const char* sig)
 *      获取静态方法:
 *           jmethodID GetStaticMethodID(jclass clazz, const char* name, const char* sig)
 *           比如：jmethodID methodId = env->GetStaticMethodID(clazz,"getJavaInfo", "(Ljava/lang/String;I)Ljava/lang/String;");
 *
 * 3.调用方法
 *      env->CallStaticXXXMethod(JNIEnv, jclass, jmethodID, ...);
 *      env->CallXXXMethod(JNIEnv, jobject, jmethodID, ...);
 *
 * 4.构造一个对象
 *      jobject NewObject(jclass clazz, jmethodID methodID, ...)
 *      jobject NewObjectA(jclass clazz, jmethodID methodID, const jvalue* args)
 *      jobject NewObjectV(jclass clazz, jmethodIDmethodID,va_list args)
 *
 *
 */
#include "com_jiage_jniccalljava_Utils.h"
#include <android/log.h>
#include <unistd.h>

#define LOG_TAG "jni_tag_cpp"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__);
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);


//调用java静态方法
void call_java_static_method(JNIEnv *env, jobject cls) {
    //1.获取字节码文件,第二个参数类似java里的包名，但c不识别包名。所以用“/”代替
//    jclass clazz = env->GetObjectClass(cls); //如果是静态jni方法调用到此处会报错，因为cls是class！！！
    jclass clazz = env->FindClass("com/jiage/jniccalljava/Utils");

    //2.获取方法签名
    const char *sig = "(Ljava/lang/String;)V";//java方法参数是String，返回值是void

    //3.获取方法签名
    jmethodID mid = env->GetStaticMethodID(clazz, "printString", sig);

    //4.调用java方法
    env->CallStaticVoidMethod(clazz, mid, env->NewStringUTF("msg_from_jni static, cpp"));
}

//调用java非静态方法
void call_java_method(JNIEnv *env, jobject instance) {
    //////////////// 调用java printD(String arg) ///////////////////
    //1.获取字节码文件,第二个参数类似java里的包名，但c不识别包名。所以用“/”代替
    jclass clazz = env->FindClass("com/jiage/jniccalljava/Utils");

    //2.获取方法签名
    const char *sig_string = "(Ljava/lang/String;)V";

    //3.获取方法签名
    jmethodID mid = env->GetMethodID(clazz, "printD", sig_string);

    //4.调用java方法
    env->CallVoidMethod(instance, mid, env->NewStringUTF("msg_from_jni, cpp"));


    //////////////// 调用java printD(int arg) ///////////////////

    const char *sig_int = "(I)V";
    jmethodID mid_int = env->GetMethodID(clazz, "printD", sig_int);
    env->CallVoidMethod(instance, mid_int, 100);

#define printD(...) env->CallVoidMethod(instance, mid_int, __VA_ARGS__);//在文件头和此位置定义宏都行;
    printD(200);//就是宏展开
}

//获取java对象成员变量
void get_java_field(JNIEnv *env, jobject instance) {
    jclass clazz = env->GetObjectClass(instance);
    jfieldID jid = env->GetFieldID(clazz, "count", "I");
    int val = env->GetIntField(instance, jid);
    LOGI("val = %d", val);

    jid = env->GetFieldID(clazz, "name", "Ljava/lang/String;");
    jstring js_name = (jstring) env->GetObjectField(instance, jid);
    const char *name = env->GetStringUTFChars(js_name, NULL);
    LOGI("name = %s", name);
}

extern "C" //支持C语言编码风格
JNIEXPORT void JNICALL
Java_com_jiage_jniccalljava_Utils_native_1func(JNIEnv *env, jobject instance) {

    LOGE("jni--> native_func ...%p", instance);
    call_java_static_method(env, instance);
    call_java_method(env, instance);
    get_java_field(env, instance);
}

extern "C"
JNIEXPORT void JNICALL Java_com_jiage_jniccalljava_Utils_native_1static_1func
        (JNIEnv *env, jclass cls) {
    LOGE("jni--> native_static_func ...%p", cls);//和native_func的instance地址都不一样!!!!
    call_java_static_method(env, cls);

//    call_java_method(env, instance); //error; 这里的instance不是对象，而是类...不能用该instance调用java非static方法

}


