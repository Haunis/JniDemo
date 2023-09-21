package com.jiage.jnindkbuild;


import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

/**
 * 1. cmake编译：
 *      a.删除libs
 *      b.注释掉build.gradle里: sourceSets、splits
 *      c.打开build.gradle里: externalNativeBuild、externalNativeBuild
 *
 * 2.mm编译:
 *      a.打开build.gradle里: sourceSets、splits
 *      b.注释掉build.gradle里: externalNativeBuild、externalNativeBuild
 *      c.将源码jni_mm拷贝到源码下
 *      d.在源码下执行编译:
 *          source build/envsetup.sh
 *          lunch
 *          mm -B
 *      e.拷贝生成的arm64-v8a到libs下
 *
 * 3.ndk编译
 *      a.打开build.gradle里: sourceSets、splits
 *      b.注释掉build.gradle里: externalNativeBuild、externalNativeBuild
 *      c.jni_ndk下执行： ~/Android/Sdk/ndk/21.4.7075529/ndk-build
 *      d.拷贝生成的arm64-v8a到libs下
 *
 */
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
                Log.d("TAG", "nativeStr --->  " + nativeStr);
                Toast.makeText(this, nativeStr, Toast.LENGTH_SHORT).show();
                break;
        }
    }
}
