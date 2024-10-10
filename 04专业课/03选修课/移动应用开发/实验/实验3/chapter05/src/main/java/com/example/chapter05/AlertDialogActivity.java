package com.example.chapter05;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class AlertDialogActivity extends AppCompatActivity implements View.OnClickListener {
    private TextView tv_alert; // 声明一个文本视图对象

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_alert_dialog);
        // 给btn_alert设置点击监听器，一旦用户点击按钮，就触发监听器的onClick方法
        findViewById(R.id.btn_alert).setOnClickListener(this);
        // 从布局文件中获取名叫tv_alert的文本视图
        tv_alert = findViewById(R.id.tv_alert);
    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.btn_alert) {
            // 创建提醒对话框的建造器
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("尊敬的用户"); // 设置对话框的标题文本
            builder.setMessage("你真的要卸载我吗？"); // 设置对话框的内容文本
            // 设置对话框的肯定按钮文本及其点击监听器
            builder.setPositiveButton("残忍卸载", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    tv_alert.setText("虽然依依不舍，但是只能离开了");
                }
            });
            // 设置对话框的否定按钮文本及其点击监听器
            builder.setNegativeButton("我再想想", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    tv_alert.setText("让我再陪你三百六十五个日夜");
                }
            });
            AlertDialog alert = builder.create(); // 根据建造器构建提醒对话框对象
            alert.show(); // 显示提醒对话框
        }
    }

}
