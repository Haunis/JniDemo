#include "com_jiage_jnindkbuild_Native.h"
//
// Created by haunis on 20-2-26.
//
JNIEXPORT jstring JNICALL Java_com_jiage_jnindkbuild_Native_getString
        (JNIEnv * env, jclass j){
    char * str = "hello from jni, build by ndk";
    return (**env).NewStringUTF(env,str);

}

