package com.jiage.jnilogdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

/**
 * 在C里面输出log，在c文件里使用Android封装好的函数就可以了
 */
public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    static {
        System.loadLibrary("GetString");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button btCallC = findViewById(R.id.bt_call_c);
        btCallC.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.bt_call_c:
                String result = getCString();
//                LogUtils.i("result : " + result);
                break;
        }
    }

    public native String getCString();
}
