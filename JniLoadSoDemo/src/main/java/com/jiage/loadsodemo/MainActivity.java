package com.jiage.loadsodemo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import com.jiage.jnindkbuild.Native;
import mt.mtxx.image.JNI;

/**
 * 本demo演示加载已经编译好的so,无头文件
 *
 * 加载libmtimage-jni.so出错,要android6.0以下才行
 * /data/app/com.xxx/lib/arm/libmtimage-jni.so: has text relocations
 */
public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private ImageView mImv;
    private Bitmap mBitmap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.bt_change_color).setOnClickListener(this);
        mImv = findViewById(R.id.imv);
        mBitmap = BitmapFactory.decodeResource(getResources(), R.drawable.xiongmao);

        mImv.setImageBitmap(mBitmap);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.bt_change_color:
                if (true) {
                    String str = new Native().getString();
                    Toast.makeText(this, str, Toast.LENGTH_SHORT).show();
                    return;
                }
                JNI jni = new JNI();

                int width = mBitmap.getWidth();
                int height = mBitmap.getHeight();
                int[] pixels = new int[width * height];
                //获取所有像素的颜色信息，此时pixels已经存储了原图所有像素的颜色信息
                mBitmap.getPixels(pixels, 0, width, 0, 0, width, height);

                //arg0:图片的所有像素的颜色信息
                //arg1:宽
                //arg2:高
                //本地方法执行完毕后，pixels中存储的是特效处理后的所有像素的颜色信息
                jni.StyleLomoC(pixels, width, height);

                //使用特效处理后的颜色信息创建一张新的位图
                Bitmap newBmp = Bitmap.createBitmap(pixels, width, height, mBitmap.getConfig());
                mImv.setImageBitmap(newBmp);

                break;
        }
    }
}
