package com.jiage.jnidynamicregister;

public class DynamicUtils {
    static {
        System.loadLibrary("Dynamic");
    }
    public static native String getString(String str);

}
