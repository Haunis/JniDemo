package com.jiage.jniccalljava;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

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
            case R.id.bt_call_c:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        mUtils.callC();
                    }
                }).start();
                break;
            case R.id.bt_set_instance_null:
                mUtils = null;
                LogUtils.d("已经将mUtils置为null: " + mUtils);
                break;
        }
    }

}
