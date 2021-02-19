package com.jiage.jniencode;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText mEtPwd;
    private Button mBtEncode;
    private Button mBtDecode;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mEtPwd = findViewById(R.id.et_pwd);
        mBtEncode = findViewById(R.id.bt_encode);
        mBtDecode = findViewById(R.id.bt_decode);

        mBtEncode.setOnClickListener(this);
        mBtDecode.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.bt_encode:
                mEtPwd.setText(CodeUtil.encode(mEtPwd.getText().toString()));
                break;
            case R.id.bt_decode:
                mEtPwd.setText(CodeUtil.decode(mEtPwd.getText().toString()));
                break;
        }
    }
}
