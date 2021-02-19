package com.jiage.demo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.bt_get_c_str).setOnClickListener(this);
        findViewById(R.id.bt_jni_add).setOnClickListener(this);
        findViewById(R.id.bt_transmit_array).setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        JNIUtil util = new JNIUtil();
        switch (view.getId()) {
            case R.id.bt_get_c_str:
                String strFromC = util.getStr("3");
                LogUtils.d("strFromC:" + strFromC);
                Toast.makeText(this, strFromC, Toast.LENGTH_SHORT).show();
                break;
            case R.id.bt_jni_add:
                int retAdd = util.add(3, 4);
                LogUtils.d("retAdd=" + retAdd);
                break;
            case R.id.bt_transmit_array:
                int[] array = new int[]{1, 2, 3, 4, 5};
                printArray(array);
                int[] result = util.transmitArray(array);
                LogUtils.i("----------after------------------ ");
                printArray(result);
                break;
        }
    }

    private void printArray(int[] array) {
        for (int i : array) {
            LogUtils.i(i + "");
        }
    }
}
