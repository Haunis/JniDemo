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

二.使用源码环境编译so库:
    参考Android.mk进行编译编译,c文件和头文件和cmake的一样

三.使用ndk-build编译so:
    文件夹命名必须为jni
    在jni下执行ndk-build命令即可(jni文件夹在任何路径均可执行ndk-build生成so)

--------------------------------2.使用so--------------------------------
一.使用cmake编译的so:
    直接install即可,会自动将so库拷贝值安装目录下

二.使用源码环境编译的so:
     1.在java同级目录创建文件夹:jniLibs/armeabi-v7a
     2.在armeabi-v7a下放入libHelloJava.so
     这样,install apk时,会自动将libHelloJava.so拷贝到/data/app/com.jiage.jnindkbuild/lib/arm里
     或者在build.gradle指定so库所在路径,如项目根目录的JniNdkBuild/libs

     注意事项:
     本模块集成了cmake,为了取消cmake编译,需要将build.gradle中cmake相关内容注释,并将jni文件夹重新命名


三.使用ndk-build编译的so库: 和使用源码环境编译的so库方式一样