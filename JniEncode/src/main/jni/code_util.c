#include "com_jiage_jniencode_CodeUtil.h"
#include <malloc.h>
#include<string.h>

//将jstring 转换成 c里的string
char *Jstring2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid,
                                                            strencode); // String .getByte("GB2312");
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte *ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);         //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);  //
    return rtn;
}

JNIEXPORT jstring JNICALL
Java_com_jiage_jniencode_CodeUtil_encode(JNIEnv *env, jobject thiz, jstring jstr) {
    char *cpass = Jstring2CStr(env, jstr);
    int i;
    for (i = 0; i < strlen(cpass); i++) {
        *(cpass + i) = *(cpass + i) + 1;
    }
    return (*env)->NewStringUTF(env, cpass);
}


JNIEXPORT jstring JNICALL
Java_com_jiage_jniencode_CodeUtil_decode(JNIEnv *env, jobject thiz, jstring jstr) {
    char *cpass = Jstring2CStr(env, jstr);
    int i;
    for (i = 0; i < strlen(cpass); i++) {
        *(cpass + i) = *(cpass + i) - 1;
    }
    return (*env)->NewStringUTF(env, cpass);
}


