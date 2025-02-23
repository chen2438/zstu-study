package com.example.activity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class Activity2 extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_2);

        TextView poemTextView = findViewById(R.id.poemTextView);

        // 获取 MainActivity 传递的诗词
        Intent intent = getIntent();
        String poem = intent.getStringExtra("poem");

        // 在 Activity2 中显示诗词
        poemTextView.setText(poem);
    }
}
