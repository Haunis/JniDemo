/**
 * 参考：
 *      https://juejin.cn/post/6844904041235873799#heading-12
 *
 *  局部与全局引用(jni引用java对象)
 *      引用在 Java 程序设计中扮演非常重要的角色。
 *      虚拟机通过追踪类实例的引用并收回不再引用的垃圾来管理类实例的使用期限。
 *      因为原生代码不是一个管理环境，因此 JNI 提供了一组函数允许原生代码显式地管理对象引用及使用期间原生代码。
 *      JNI 支持三种引用: 局部引用、全局引用和弱全局引用
 *
 *      这里的引用说的是jni对java对象的引用，不包括jni对jni对象的引用
 *
 *
 *  局部引用：
 *      大多数 JNI 函数返回局部引用。局部应用不能在后续的调用中被缓存及重用，主要是因为它们的使用期限仅限于原生方法，
 *      一旦原生方法返回，局部引用即被释放。
 *      例如: FindClass函数返回一个局部引用，当原生方法返回时，它被自动释放，也可以用 DeleteLocalRef 函数显式的释放原生代码。
 *
 *      JNIEnv和jobject instance提全局后只在当前线程有效。
 *
 *  全局引用：
 *      全局引用在原生方法的后续调用过程中依然有效，除非它们被原生代码显式释放
 *
 *  弱全局引用：
 *      与全局引用一样，弱全局引用在原生方法的后续调用依然有效。与全局引用不同，弱全局引用并不阻止潜在的对象被垃圾收回
 *      弱全局引用的有效性检验: IsSameObject()检验一个弱全局引用是否仍然指向活动的类实例.
 */

#include "common.h"
#include <string>


typedef enum {
    REF_FLAG_NONE,
    REF_FLAG_LOCAL,
    REF_FLAG_GLOBAL,
    REF_FLAG_WEAK
} my_ref_flag;

using namespace std; //string不是基本数据类型。要引入<string>头文件和std标准明明空间才可以使用



namespace my_reference {
    jobject g_instance_jniutil;
    my_ref_flag g_ref_flag = REF_FLAG_NONE;

    //instance: MainActivity 对象
    void update_java_ui(JNIEnv *env, jobject instance) {
        jclass JNIUtilClass = env->GetObjectClass(instance);
        // 拿到JNIUtil的updateUI 方法
        const char *sig = "()V";
        jmethodID updateUI = env->GetMethodID(JNIUtilClass, "updateUI", sig);

        env->CallVoidMethod(instance, updateUI);
    }
}

class Student {

public:
    string name;
    int age;

public:
    Student(string name, int age) {
        this->name = name;
        this->age = age;
        LOGI("jni--> Student 构造 ...");
    }

    void study() {
        LOGI("jni--> Student study ...");
    }
};


//测试局部引用
jclass g_person_class_local; //虽然被提升到全局，但是该引用是无效的
Student *g_student; // jni本身对象不受影响
extern "C" JNIEXPORT void JNICALL
Java_com_jiage_demo_JNIUtil_native_1set_1local_1ref(JNIEnv *env, jobject instance) {
    LOGE("jni--> 设置局部引用 .....");
    my_reference::g_ref_flag = REF_FLAG_LOCAL;

    LOGI("-----------------设置jni 引用---------------------");
    if (g_student == NULL)g_student = new Student("张三", 18);//jni指针，提全局有效！！！

    LOGI("-----------------设置instance 引用---------------------");
    if (my_reference::g_instance_jniutil == NULL) {
        my_reference::g_instance_jniutil = instance; //不能跨线程传递
//        g_instance_jniutil = env->NewGlobalRef(instance);//这样子才可以跨线程传递
    }
    my_reference::update_java_ui(env, my_reference::g_instance_jniutil);

    LOGI("-----------------设置person local 引用---------------------");
    if (g_person_class_local == NULL) {
        const char *person_class = "com/jiage/demo/Person";
        g_person_class_local = env->FindClass(person_class); //jni方法调用完就释放，提升至全局也没用。。jni方法使用该引用无效
        LOGI("g_person_class_local == null 执行了。");
    }
}

//测试全局引用
jclass g_person_class_gobal;
extern "C" JNIEXPORT void JNICALL
Java_com_jiage_demo_JNIUtil_native_1set_1global_1ref(JNIEnv *env, jobject instance) {
    LOGE("jni--> 设置全局引用...");
    my_reference::g_ref_flag = REF_FLAG_GLOBAL;

    ////////////////////////////////////////////////////////////////////////////
    if (my_reference::g_instance_jniutil != NULL) {
        my_reference::update_java_ui(env, my_reference::g_instance_jniutil);
    }
    ////////////////////////////////////////////////////////////////////////////

    if (g_person_class_gobal == NULL) {
        //1. 提升全局解决不能重复使用问题
        const char *person_class = "com/jiage/demo/Person";
        jclass jclass1 = env->FindClass(person_class);//jclass1提全局没有用...
        g_person_class_gobal = static_cast<jclass>(env->NewGlobalRef(jclass1));
        LOGI("g_person_class_gobal == null 执行了。");
    }
}

//测试弱全局引用
jclass g_person_class_weak;
extern "C" JNIEXPORT void JNICALL
Java_com_jiage_demo_JNIUtil_native_1set_1weak_1global_1ref(JNIEnv *env, jobject) {
    LOGE("jni--> 设置弱全局引用....");
    my_reference::g_ref_flag = REF_FLAG_WEAK;

    if (g_person_class_weak == NULL) {
        //1. 提升全局解决不能重复使用问题
        const char *person_class = "com/jiage/demo/Person";
        jclass jclass1 = env->FindClass(person_class);
        // g_person_class_local = static_cast<jclass>(env->NewGlobalRef(jclass1));
        g_person_class_weak = static_cast<jclass>(env->NewWeakGlobalRef(jclass1));
        LOGI("jni g_person_class_weak == null 执行了。");
    }
}

extern "C"
JNIEXPORT void JNICALL Java_com_jiage_demo_JNIUtil_native_1test_1jni_1ref
        (JNIEnv *env, jobject instance) {
    LOGE("jni--> test_jni_ref, g_ref_flag=%d", my_reference::g_ref_flag);
    jclass person_class;
    switch (my_reference::g_ref_flag) {
        case REF_FLAG_NONE:
            LOGE("未设置引用 ！！！！！");
            return;
        case REF_FLAG_LOCAL:
            person_class = g_person_class_local;
            g_student->study();//ok
            my_reference::update_java_ui(env, my_reference::g_instance_jniutil);//ok
            break;
        case REF_FLAG_GLOBAL:
            person_class = g_person_class_gobal;
            break;
        case REF_FLAG_WEAK:
            person_class = g_person_class_weak;
            break;
    }

    //Java Person 构造方法实例化
    const char *sig = "()V";
    const char *method = "<init>";//Java 构造方法标识
    jmethodID init = env->GetMethodID(person_class, method, sig);
    //创建java对象; jni函数里的NewObject无需手动释放，jvm自动管理
    jobject person_obj = env->NewObject(person_class, init);


//    env->DeleteLocalRef(g_person_class_local);
//    delete g_student;
//
//    env->DeleteGlobalRef(g_person_class_gobal); //显式释放主动删除局部引用
//    g_person_class_gobal = NULL;
//
//    env->DeleteWeakGlobalRef(g_person_class_weak);
//    g_person_class_weak = NULL;
}


