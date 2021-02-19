package com.jiage.jniencode;

/**
 * @author Haunis 2019/1/21.
 */
public class CodeUtil {
    static {
        System.loadLibrary("code_util");
    }

    public static native String encode(String str);

    public static native String decode(String str);
}
