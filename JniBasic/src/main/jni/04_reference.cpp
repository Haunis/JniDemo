/**
 * 参考：
 *      https://juejin.cn/post/6844904041235873799#heading-12
 *
 *  局部与全局引用
 *      引用在 Java 程序设计中扮演非常重要的角色。
 *      虚拟机通过追踪类实例的引用并收回不在引用的垃圾来管理类实例的使用期限。
 *      因为原生代码不是一个管理环境，因此 JNI 提供了一组函数允许原生代码显式地管理对象引用及使用期间原生代码。
 *      JNI 支持三种引用: 局部引用、全局引用和弱全局引用
 *
 *
 *  局部引用：
 *      大多数 JNI 函数返回局部引用。局部应用不能在后续的调用中被缓存及重用，主要是因为它们的使用期限仅限于原生方法，
 *      一旦原生方法返回，局部引用即被释放。例如: FindClass 函数返回一个局部引用，当原生方法返回时，它被自动释放，
 *      也可以用 DeleteLocalRef 函数显式的释放原生代码
 *
 *  全局引用：
 *      全局引用在原生方法的后续调用过程中依然有效，除非它们被原生代码显式释放
 *
 *  弱全局引用：
 *      与全局引用一样，弱全局引用在原生方法的后续调用依然有效。与全局引用不同，弱全局引用并不阻止潜在的对象被垃圾收回
 *      弱全局引用的有效性检验: IsSameObject()检验一个弱全局引用是否仍然指向活动的类实例.
 */

#include "common.h"

//测试局部引用
jclass personClass; //虽然被提升到全局，但是该引用是无效的
extern "C" JNIEXPORT void JNICALL
Java_com_jiage_demo_JNIUtil_native_1test_1local_1ref(JNIEnv *env, jobject) {
    LOGD("测试局部引用, personClass");
    if (personClass == NULL) {
        const char *person_class = "com/jiage/demo/Person";
        personClass = env->FindClass(person_class); //jni方法调用完就释放，提升至全局也没用。。
        LOGD("personClass == null 执行了。");
    }
    //Java Person 构造方法实例化
    const char *sig = "()V";
    const char *method = "<init>";//Java 空构造方法标识
    jmethodID init = env->GetMethodID(personClass, method, sig);
    //创建出来
    jobject person_obj = env->NewObject(personClass, init);

//    env->DeleteLocalRef(personClass);
}

//测试全局引用
jclass g_person_class;
extern "C" JNIEXPORT void JNICALL
Java_com_jiage_demo_JNIUtil_native_1test_1global_1ref(JNIEnv *env, jobject) {
    LOGD("测试全局引用");

    if (g_person_class == NULL) {
        //1. 提升全局解决不能重复使用问题
        const char *person_class = "com/jiage/demo/Person";
        jclass jclass1 = env->FindClass(person_class);//jclass1提全局没有用...
        g_person_class = static_cast<jclass>(env->NewGlobalRef(jclass1));
        LOGD("g_person_class == null 执行了。");
    }

    //Java Person 构造方法实例化
    const char *sig = "()V";
    const char *method = "<init>";//Java 构造方法标识
    jmethodID init = env->GetMethodID(g_person_class, method, sig);
    //创建出来
    env->NewObject(g_person_class, init);//会调用java Person对象的构造方法

    //2. 显式释放主动删除全局引用
//    env->DeleteGlobalRef(g_person_class);
//    g_person_class = NULL;
}

//测试弱全局引用
jclass g_weak_person_class;
extern "C" JNIEXPORT void JNICALL
Java_com_jiage_demo_JNIUtil_native_1test_1weak_1global_1ref(JNIEnv *env, jobject) {
    LOGD("jni 测试弱全局引用....");

    if (g_weak_person_class == NULL) {
        //1. 提升全局解决不能重复使用问题
        const char *person_class = "com/jiage/demo/Person";
        jclass jclass1 = env->FindClass(person_class);
        // personClass = static_cast<jclass>(env->NewGlobalRef(jclass1));
        g_weak_person_class = static_cast<jclass>(env->NewWeakGlobalRef(jclass1));
        LOGD("jni g_weak_person_class == null 执行了。");
    }

    //Java Person 构造方法实例化
    const char *sig = "()V";
    const char *method = "<init>";//Java 构造方法标识
    jmethodID init = env->GetMethodID(g_weak_person_class, method, sig);
    //创建出来
    env->NewObject(g_weak_person_class, init);

    //2. 显式释放主动删除局部引用
    env->DeleteWeakGlobalRef(g_weak_person_class);
    g_weak_person_class = NULL;
}
