package com.jiage.jnidynamicregister;

public class DynamicUtils {
    static {
        System.loadLibrary("Dynamic");
    }

    public native void getString1();

    public static native String getString2(String str);

}
