package com.jiage.demo;

import android.os.Looper;

/**
 * @author Haunis 2019/1/19.
 * 在JniNdkBuild/src/main/java执行 javah -jni com.jiage.demo.JNIUtil
 */
public class JNIUtil {
    public int count;

    static {
        System.loadLibrary("jnibasic");//加载Demo\JNI1\build\intermediates\cmake\debug\obj\arm64-v8a\libhello.so
    }

    //////////////////////////// 1.Java将数据传递到native，jni无返回 ////////////////////////////////
    public native void native_java2jni(
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

    //////////////////////////// 2.Java将数据传递到native，jni有返回 ////////////////////////////////
    public native String native_jni2java_str(String s);

    public native int native_jni2java_int(int x, int y);

    public native int[] native_jni2java_intarr(int[] array);

    public native Person native_jni2java_obj(); //jni返回java对象


    //////////////////////////// 3.测试 jni 异常 ////////////////////////////////
    public native void native_test_exception(String name);

    //给jni使用
    public void testException() throws NullPointerException {
        throw new NullPointerException("JNIUtil testException NullPointerException");
    }

    //////////////////////////// 4. jni局部引用和全局引用 ////////////////////////////////
    //jni测试局部引用
    public native void native_test_local_ref();

    //jni测试全局引用
    public native void native_test_global_ref();

    //jni测试全局引用
    public native void native_test_weak_global_ref();

    //////////////////////////// 5.jni 同步： 锁java对象  ////////////////////////////////
    public native void native_jni_sync_count();

    public void test_jni_sync() {
        for (int i = 0; i < 10; i++) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    count(); //java层对count 加1
                    native_jni_sync_count(); // jni层对count 加 1
                }
            }).start();
        }
    }

    private void count() {
        synchronized (this) {
            count++;
            LogUtils.d("java--> count=" + count);
        }
    }

    //////////////////////////// 6.jni开启子线程 ////////////////////////////////
    public native void native_start_thread();

    public native void native_rm_global_ref(); //删除jni全局引用

    public void updateUI() {
        if (Looper.getMainLooper() == Looper.myLooper()) {
            LogUtils.d("java--> run ui thread ...");
        } else {
            LogUtils.d("java--> run sub thread ...");
        }
    }

}
