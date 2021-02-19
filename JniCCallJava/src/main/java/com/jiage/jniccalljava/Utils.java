package com.jiage.jniccalljava;

import android.util.Log;

public class Utils {
    static {
        System.loadLibrary("call_java_util");
    }

    public native void callC();

    public static void printString(String msg){
        Log.d("JIA", msg);
    }

    public void printD(String msg) {
        Log.d("JIA", msg);
    }

    public void printD(int i) {
        Log.d("JIA", i + "");
    }
}
