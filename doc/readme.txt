以JniNdkBuild为例

--------------------------------1.编译so--------------------------------
一.使用cmake编译so:
    1.环境配置
        Tools→SDK Manager→SDK tools → LLDB，Cmake，NDK均要下载
    2.创建要和c++通信的java文件
        如:com.jiage.jnindkbuild.Native
    3.使用java文件生成.h头文件
        在包名同级目录:javah -jni 包名.类名
        如在JniNdkBuild/src/main/java执行 javah -jni com.jiage.jnindkbuild.Native
        生成的头文件存在同级目录 src/main/java/com_jiage_jnindkbuild_Native.h
    4.创建C文件
        a.在包名同级目录(src/main/java),新建JNI文件夹
        b.在JNI文件夹中拷入刚刚生成的.h头文件
        c.新建.c文件,并在头部引入.h文件的文件名   #include "com_jiage_jnindkbuild_Native.h"
        d.实现头文件方法 Java_com_jiage_jnindkbuild_Native_getString()
    5.根目录创建CMakeLists.txt
    6.配置build.gradle

    注意事项：新增cpp或更名cpp文件后，要删除module下.cxx缓存文件，否则新的cpp文件不会被加入编译

二.使用源码环境编译so库:
    参考Android.mk进行编译,c文件和头文件和cmake的一样
    source build/envsetup.sh
    lunch
    mm -B

三.使用ndk-build编译so:
    文件夹命名必须为jni
    在jni下执行ndk-build命令即可(jni文件夹在任何路径均可执行ndk-build生成so)
    ~/Android/Sdk/ndk/21.4.7075529/ndk-build


--------------------------------2.使用so--------------------------------
一.使用cmake编译的so:
    直接install即可,会自动将so库拷贝值安装目录下

二.使用源码环境编译的so:
     方式一：
         1.在java同级目录创建文件夹:jniLibs/armeabi-v7a
         2.在armeabi-v7a下放入libHelloJava.so
         这样,install apk时,会自动将libHelloJava.so拷贝到/data/app/com.jiage.jnindkbuild/lib/arm里
     方式二：
     在build.gradle指定so库所在路径,如项目根目录的JniNdkBuild/libs

     注意事项:
     本模块集成了cmake,为了取消cmake编译,需要将build.gradle中cmake相关内容注释,并将jni文件夹重新命名


三.使用ndk-build编译的so库: 和使用源码环境编译的so库方式一样



--------------------------------3.jni基础知识--------------------------------
一.方法签名:
javap -s xxx.class
1.1 基本数据类型方法签名
    JNI类型               Java类型          类型签名
    jboolean              boolean           Z (B被btye使用)
    jbyte                 byte              B
    jchar                 char              C
    jshort                short             S
    jint                  int               I
    jlong                 long              J (L表示类的签名)
    jfloat                float             F
    jdouble               double            D
    void                  void              V

1.2 引用数据类型方法签名
    类的方法签名：L + /包名/类名+ ;, 如String是: L/java/lang/String;
    数组的方法签名: "[数据类型签名"，如int[]是: [I
    多维数组方法签名： 多个[+类型签名

完整的签名是 "(参数类型签名)+返回值类型签名"
    比如 public native String getJavaInfo(String info,int index){}
    对应的签名是：(Ljava/lang/String;I)Ljava/lang/String;


二、jni引用类型
与基本数据类型不同，引用类型对原生方法时不透明的，引用类型映射如下表所示。它们的内部数据结构并不直接向原生代码公开

Java 类型                原生类型

Java.lang.Class         jclass
Java.lang.Throwable     jthrowable
Java.lang.String        jstring
Other object            jobject
Java.lang.Object[]      jobjectArray
boolean[]               jbooleanArray
byte[]                  jbyteArray
char[]                  jcharArray
short[]                 jshortArray
int[]                   jintArray
long[]                  jlongArray
float[]                 jfloatArray
double[]                jdoubleArray
Other arrays            jarray

三、JNIEnv 和 JavaVm
JNIEnv :
    JNIEnv 表示 Java 调用 native 语言的环境，是一个封装了几乎全部 JNI 方法的指针。
    JNIEnv 只在创建它的线程生效，不能跨线程传递，不同线程的 JNIEnv 彼此独立。
    native 环境中创建的线程，如果需要访问 JNI，必须要调用 AttachCurrentThread 关联，并使用 DetachCurrentThread 解除链接。

JavaVm :
    JavaVM 是虚拟机在 JNI 层的代表，一个进程只有一个 JavaVM，所有的线程共用一个JavaVM。

四、代码风格
C:       (*env)->NewStringUTF(env, “Hellow World!”);
C++:     env->NewStringUTF(“Hellow World!”);


