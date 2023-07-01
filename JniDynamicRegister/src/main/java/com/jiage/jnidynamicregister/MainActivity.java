package com.jiage.jnidynamicregister;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

/**
 * 动态绑定不需要.h头文件
 */
public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.bt_click:
                new DynamicUtils().getString1();

                String str = DynamicUtils.getString2("msg from java");
                Log.d("TAG", "nativeStr--> " + str);
                Toast.makeText(this, str, Toast.LENGTH_SHORT).show();
                break;
        }
    }
}