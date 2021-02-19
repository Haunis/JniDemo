package com.jiage.jnindkbuild;


import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.bt_test:
                String nativeStr = new Native().getString();
                Log.d("TAG", "nativeStr: " + nativeStr);
                Toast.makeText(this, nativeStr, Toast.LENGTH_SHORT).show();
                break;
        }
    }
}
