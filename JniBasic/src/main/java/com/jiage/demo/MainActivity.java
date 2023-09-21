package com.jiage.demo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public void onClick(View view) {
        JNIUtil util = new JNIUtil();
        switch (view.getId()) {
            case R.id.bt_java2jni://java传数据到jni
                util.java2jni(true,
                        (byte) 1,
                        ',',
                        (short) 3,
                        4,
                        3.3f,
                        2.2d,
                        "DevYK",
                        28,
                        new int[]{1, 2, 3, 4, 5, 6, 7},
                        new String[]{"1", "2", "4"},
                        new Person("张三", 20),
                        new boolean[]{false, true}
                );
                break;
            case R.id.bt_get_c_str: //java传string到jni， jni返回string
                String strFromC = util.jni2java_str("msg_from_java");
                LogUtils.d("java--> strFromC:" + strFromC);
                Toast.makeText(this, strFromC, Toast.LENGTH_SHORT).show();
                break;
            case R.id.bt_jni_add://java传int到jni， jni返回int
                int retAdd = util.jni2java_int(3, 4);
                LogUtils.d("java--> retAdd=" + retAdd);
                break;
            case R.id.bt_jni2java_intarr://传递数组到jni，jni返回新数组
                int[] array = new int[]{1, 2, 3, 4, 5};
                printArray(array);
                int[] result = util.jni2java_intarr(array);
                LogUtils.i("------------- java --------------- ");
                printArray(result);
                break;
            case R.id.bt_get_java_obj:
                Person p = util.jni2java_obj();
                LogUtils.i("java--> p = " + p);
                break;
            case R.id.bt_test_exception:
                util.native_test_exception("测试异常");
                break;
            case R.id.bt_test_local_ref: //jni 局部引用class对象
                util.test_local_ref();//执行2次,jni会crash
                break;
            case R.id.bt_test_global_ref://jni全局引用class对象
                util.test_global_ref();
                break;
            case R.id.bt_test_weak_global_ref://jni弱全局引用
                util.test_weak_global_ref();
                break;



            case R.id.bt_force_gc:
                System.gc();
                break;
        }
    }

    private void printArray(int[] array) {
        for (int i : array) {
            LogUtils.i(i + "");
        }
    }


}
