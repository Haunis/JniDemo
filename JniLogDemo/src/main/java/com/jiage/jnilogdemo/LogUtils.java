package com.jiage.jnilogdemo;

import android.util.Log;

/**
 * @author Haunis 2019/1/26.
 */
public class LogUtils {
    private static final String TAG = "JIA";

    public static void i(String msg) {
        Log.i(TAG, msg);
    }

    public static void d(String msg) {
        Log.d(TAG, msg);
    }

    public static void w(String msg) {
        Log.w(TAG, msg);
    }
}
