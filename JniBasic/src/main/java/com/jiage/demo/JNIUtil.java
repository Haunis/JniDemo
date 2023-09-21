package com.jiage.demo;

/**
 * @author Haunis 2019/1/19.
 * 在JniNdkBuild/src/main/java执行 javah -jni com.jiage.demo.JNIUtil
 */
public class JNIUtil {

    static {
        System.loadLibrary("jnibasic");//加载Demo\JNI1\build\intermediates\cmake\debug\obj\arm64-v8a\libhello.so
    }

    //Java 将数据传递到 native 中
    public native void java2jni(
            boolean b,
            byte b1,
            char c,
            short s,
            long l,
            float f,
            double d,
            String name,
            int age,
            int[] i,
            String[] strs,
            Person person,
            boolean[] bArray
    );

    //java 调用 native方法
    public native String jni2java_str(String s);

    public native int jni2java_int(int x, int y);

    public native int[] jni2java_intarr(int[] array);



    //获取native创建的java对象
    public native Person jni2java_obj();


    public native void native_test_exception(String name);

    //给jni使用
    public void testException() throws NullPointerException {
        throw new NullPointerException("JNIUtil testException NullPointerException");
    }

    //jni测试局部引用
    public native void test_local_ref();

    //jni测试全局引用
    public native void test_global_ref();

    //jni测试全局引用
    public native void test_weak_global_ref();

}
