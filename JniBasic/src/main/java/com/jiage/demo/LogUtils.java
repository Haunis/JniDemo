package com.jiage.demo;

import android.text.TextUtils;
import android.util.Log;

/**
 * Created by JiaJia on 2018/5/18.
 */

public class LogUtils {
    private static String mTag = "TAG";

    public static void i(String msg) {
        Log.i(generateTag(), msg);
    }

    public static void i(String tag, String msg) {
        mTag = tag;
        Log.i(generateTag(), msg);
    }

    public static void d(String msg) {
        Log.d(generateTag(), msg);
    }

    public static void d(String tag, String msg) {
        mTag = tag;
        Log.d(generateTag(), msg);
    }

    public static void w(String msg) {
        Log.w(generateTag(), msg);
    }

    public static void w(String tag, String msg) {
        mTag = tag;
        Log.w(generateTag(), msg);
    }

    public static void e(String msg) {
        Log.e(generateTag(), msg);
    }

    private static String generateTag() {
        StackTraceElement caller = getCallerStackTraceElement();
        String tag = "%s.%s()"; // 占位符
        String tagPrefix = mTag;
        try {
            String callerClazzName = caller.getClassName(); // 获取到类名
            callerClazzName = callerClazzName.substring(callerClazzName.lastIndexOf(".") + 1);
            tag = String.format(tag, callerClazzName, caller.getMethodName()); // 替换
        } catch (IndexOutOfBoundsException e) {
            Log.d(tagPrefix, e.toString());
            return tagPrefix;
        }
        tag = TextUtils.isEmpty(tagPrefix) ? tag : tagPrefix + "" + tag;
        return tag;
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

