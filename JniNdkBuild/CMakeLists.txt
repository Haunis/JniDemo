# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 编译生成so库
add_library( # Sets the name of the library.
        # 生成的so库名称，此处生成的so文件名称是libnative-lib.so;位置：app/build/intermediates/cmake/debug/obj
        HelloJava

        # Sets the library as a shared library.
        # STATIC：静态库，是目标文件的归档文件，在链接其它目标的时候使用
        # SHARED：动态库，会被动态链接，在运行时被加载
        # MODULE：模块库，是不会被链接到其它目标中的插件，但是可能会在运行时使用dlopen-系列的函数动态链接
        SHARED

        # Provides a relative path to your source file(s).
        # 资源文件，可以多个，资源路径是相对路径，相对于本CMakeLists.txt所在目录
        src/main/jni_cmake/NativeJni.c)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

# 从系统查找依赖库
find_library( # Sets the name of the path variable.
        # 变量名
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        # so库的名字，liblog.so; 在android /system/lib/liblog.so
        log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

# 配置库的链接（依赖关系）
target_link_libraries( # Specifies the target library.

        # 目标库; libHelloJava.so依赖 ${log-lib}，也就是liblog.so
        HelloJava

        # Links the target library to the log library
        # included in the NDK.
        # 依赖于
        ${log-lib} )