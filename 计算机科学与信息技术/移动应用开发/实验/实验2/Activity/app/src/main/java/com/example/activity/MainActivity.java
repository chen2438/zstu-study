package com.example.activity;

import android.content.Intent;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    private TextView countdownTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        countdownTextView = findViewById(R.id.countdownTextView);

        // 设置倒计时为5秒，间隔为1秒
        new CountDownTimer(5000, 1000) {
            public void onTick(long millisUntilFinished) {
                long seconds = millisUntilFinished / 1000;
                countdownTextView.setText(String.valueOf(seconds));
            }

            public void onFinish() {
                // 倒计时结束后跳转到 Activity2
                Intent intent = new Intent(MainActivity.this, Activity2.class);

                // 将诗词发送到 Activity2
                String poem = "长风破浪会有时，直挂云帆济沧海";
                intent.putExtra("poem", poem);

                startActivity(intent);
                finish();
            }
        }.start();
    }
}
