package com.jiage.demo;

/**
 * @author Haunis 2019/1/19.
 * 在JniNdkBuild/src/main/java执行 javah -jni com.jiage.jnindkbuild.Native
 */
public class JNIUtil {

    static {
        System.loadLibrary("jnibasic");//加载Demo\JNI1\build\intermediates\cmake\debug\obj\arm64-v8a\libhello.so
    }

    public native String getStr(String s);

    public native int add(int x, int y);

    public native int[] transmitArray(int[] array);
}
