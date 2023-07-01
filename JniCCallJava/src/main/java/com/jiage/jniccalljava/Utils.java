package com.jiage.jniccalljava;

import android.util.Log;

public class Utils {
    static {
        System.loadLibrary("call_java_util");
    }

    public Utils() {
        LogUtils.e("Utils 构造 ...");
    }

    public native void callC();

    public static void printString(String msg) {
        LogUtils.d("msg = " + msg);
    }

    public void printD(String msg) {
        LogUtils.d("msg = " + msg);
    }

    public void printD(int i) {
        LogUtils.d("i = " + i);
    }
}
