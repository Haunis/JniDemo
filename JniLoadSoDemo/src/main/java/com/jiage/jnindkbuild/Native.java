package com.jiage.jnindkbuild;

public class Native {
    static {
        System.loadLibrary("HelloJava");
    }
    public static native String getString();
}
