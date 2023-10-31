package com.jiage.jniccalljava;


// src/main/java:   javah -jni com.jiage.jniccalljava.Utils
public class Utils {
    public int count = 10;
    public String name = "张三";

    static {
        System.loadLibrary("call_java_util");
    }

    public Utils() {
        LogUtils.e("java--> Utils 构造 ...");
    }

    public native void native_func();

    public native static void native_static_func();


    public static void printString(String msg) {
        LogUtils.d("java--> printString: " + msg);
    }

    public void printD(String msg) {
        LogUtils.d("java--> printD:  " + msg);
    }

    public void printD(int i) {
        LogUtils.d("java--> printD: " + i);
    }
}
