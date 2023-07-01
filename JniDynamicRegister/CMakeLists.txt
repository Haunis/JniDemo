
cmake_minimum_required(VERSION 3.4.1)

#add_library(Dynamic SHARED src/main/jni/dynamic.c)
add_library(Dynamic SHARED src/main/jni/dynamic.cpp)

# 从系统查找依赖库
find_library(log-lib log)

# 配置库的链接（依赖关系）
target_link_libraries(Dynamic ${log-lib})