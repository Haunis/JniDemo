cmake编译时,c文件夹命名可以任意
mm编译时,c文件夹可以任意
ndk编译时,c文件夹命名必须是 jni

注意事项:
    如果main/java同级目录含有jni文件夹的话,android studio编译不过会提示使用cmake或者ndk-build编译
    所以为了方便,不在main/java同级目录创建jni文件夹

-----------------------本demo三种方式编译so---------------------------
1.本demo使用cmake编译:
    jni_cmake可以不改为jni
    1.将build.gradle打开相关注释
    2.删除jniLibs下的so,保证安装的是cmake编译的so
    3.点三角形直接run到机器上就行

2.本demo使用mm编译的so:
    1.注释buidld.gradle cmake相关
    2.源码环境下编译出so
    3.将so拷贝至jniLibs/arm下

3.本demo使用ndk-build编译的so:
    1.注释buidld.gradle cmake相关
    2.在jni_ndk/jni下使用ndk-build编译出so
    3.将编译出的jni_ndk/libs/armeabi-v7a/***.so拷贝至jniLibs/arm下
