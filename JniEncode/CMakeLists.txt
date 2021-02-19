cmake_minimum_required(VERSION 3.6)

add_library( # Sets the name of the library.
        code_util # 生成的so库名称，此处生成的so文件名称是libxjni.so

        # Sets the library as a shared library.
        # STATIC：静态库，是目标文件的归档文件，在链接其它目标的时候使用
        # SHARED：动态库，会被动态链接，在运行时被加载
        # MODULE：模块库，是不会被链接到其它目标中的插件，但是可能会在运行时使用dlopen-系列的函数动态链接
        SHARED

        # Provides a relative path to your source file(s).
        # 资源文件，可以多个，
        # 资源路径是相对路径，相对于本CMakeLists.txt所在目录
        src/main/jni/code_util.c)

# 从系统查找依赖库
find_library( # Sets the name of the path variable.
        # android系统每个类型的库会存放一个特定的位置，而log库存放在log-lib中
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        # android系统在c环境下打log到logcat的库
        log)

target_link_libraries( # Specifies the target library.
        # 目标库
        code_util

        # Links the target library to the log library
        # included in the NDK.
        # 依赖于
        ${log-lib})