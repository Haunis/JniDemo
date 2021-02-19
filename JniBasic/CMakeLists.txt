cmake_minimum_required(VERSION 3.6)

###############方式1##############
#add_library(jnibasic SHARED src/main/jni/xjni.c) #生成libjnibasic.so
#target_link_libraries(jnibasic log) #链接liblog.so


###############方式2##############
aux_source_directory(src/main/jni/ DIR_LIB_SRC) #将"src/main/jni/"下源文件保存到变量DIR_LIB_SRC
add_library(jnibasic SHARED ${DIR_LIB_SRC})
find_library(log-lib log) #寻找liblog.so 保存到变量log-lib
target_link_libraries(jnibasic ${log-lib})