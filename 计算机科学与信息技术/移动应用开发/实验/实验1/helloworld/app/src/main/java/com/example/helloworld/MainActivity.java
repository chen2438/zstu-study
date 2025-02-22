package com.example.helloworld;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // onCreate() 方法在活动第一次创建时被调用。
        // savedInstanceState 是一个 Bundle，它包含了活动的前一个实例的状态
        super.onCreate(savedInstanceState);
        // 调用了父类（AppCompatActivity）的 onCreate() 方法
        setContentView(R.layout.activity_main);
        // 设置了活动的用户界面布局
        Log.d("MainActivity", "onCreate");
        // 打印一条调试信息
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.d("MainActivity", "onStart");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d("MainActivity", "onResume");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.d("MainActivity", "onPause");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.d("MainActivity", "onStop");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d("MainActivity", "onDestroy");
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.d("MainActivity", "onRestart");
    }
}
