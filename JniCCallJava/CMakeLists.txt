cmake_minimum_required(VERSION 3.6)

# 资源路径是相对路径，相对于本CMakeLists.txt所在目录
add_library(call_java_util SHARED src/main/jni/call_java_util.c)

#寻找liblog.so 保存到变量log-lib
find_library(log-lib log)

target_link_libraries(call_java_util ${log-lib})