package com.jiage.jniccalljava;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {


    private Utils mUtils;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mUtils = new Utils();
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.bt_jni_func:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        mUtils.native_func();
                    }
                }).start();
                break;
            case R.id.bt_jni_static_func:
                Utils.native_static_func();
                break;
            case R.id.bt_set_instance_null:
                mUtils = null;
                LogUtils.d("已经将mUtils置为null: " + mUtils);
                break;
        }
    }

}
