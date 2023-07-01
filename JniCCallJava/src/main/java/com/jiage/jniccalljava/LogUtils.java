package com.jiage.jniccalljava;

import android.text.TextUtils;
import android.util.Log;

import java.util.Locale;


public class LogUtils {
    private static final String mTag = "TAG";

    public static void v(String msg) {
        Log.v(generateTag(""), msg);
    }

    public static void v(String tag, String msg) {
        Log.v(generateTag(tag), msg);
    }

    public static void i(String msg) {
        Log.i(generateTag(""), msg);
    }

    public static void i(String tag, String msg) {
        Log.i(generateTag(tag), msg);
    }

    public static void d(String msg) {
        Log.d(generateTag(""), msg);
    }

    public static void d(String tag, String msg) {
        Log.d(generateTag(tag), msg);
    }

    public static void w(String msg) {
        Log.w(generateTag(""), msg);
    }

    public static void w(String tag, String msg) {
        Log.w(generateTag(tag), msg);
    }

    public static void e(String msg) {
        Log.e(generateTag(""), msg);
    }

    public static void e(String tag, String msg) {
        Log.e(generateTag(tag), msg);
    }

    private static String generateTag(String tag) {
        try {
            StackTraceElement caller = getCallerStackTraceElement();
            String className = caller.getClassName(); // 获取到类名
            className = className.substring(className.lastIndexOf(".") + 1);
            String methodName = caller.getMethodName();

            long threadId = Thread.currentThread().getId();
            if (TextUtils.isEmpty(tag)) {
                return String.format(Locale.CHINA, "%d-%s.%s()", threadId, className, methodName);
            } else {
                return String.format(Locale.CHINA, "%d-%s-%s.%s()", threadId, tag, className, methodName);
            }
//            return "t"+threadId;
        } catch (IndexOutOfBoundsException e) {
            Log.d(mTag, e.toString());
            return mTag;
        }
    }

    private static StackTraceElement getCallerStackTraceElement() {
        StackTraceElement[] elements = Thread.currentThread().getStackTrace();
        StackTraceElement element = elements[5];
//        Log.d("TAG", element.getClassName() + "  :  " + element.getMethodName());

//        Log.d("TAG","------------------------------------------------------------------");
//        for (StackTraceElement element : elements) {
//            Log.d("TAG", element.getClassName() + "  :  " + element.getMethodName());
//        }
//        Log.d("TAG","------------------------------------------------------------------");
//        return Thread.currentThread().getStackTrace()[4];

        return element;
    }
}

