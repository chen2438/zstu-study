package com.example.chapter05;

import android.annotation.SuppressLint;
import android.app.DatePickerDialog;
import android.os.Bundle;
import android.view.View;
import android.widget.DatePicker;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.util.Calendar;

@SuppressLint("DefaultLocale")
// 该页面类实现了接口OnDateSetListener，意味着要重写日期监听器的onDateSet方法
public class DatePickerActivity extends AppCompatActivity implements
        View.OnClickListener, DatePickerDialog.OnDateSetListener {
    private TextView tv_date; // 声明一个文本视图对象
    private DatePicker dp_date; // 声明一个日期选择器对象

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_date_picker);
        tv_date = findViewById(R.id.tv_date);
        // 从布局文件中获取名叫dp_date的日期选择器
        dp_date = findViewById(R.id.dp_date);
        findViewById(R.id.btn_date).setOnClickListener(this);
        findViewById(R.id.btn_ok).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.btn_date) {
            // 获取日历的一个实例，里面包含了当前的年月日
            Calendar calendar = Calendar.getInstance();
            // 构建一个日期对话框，该对话框已经集成了日期选择器。
            // DatePickerDialog的第二个构造参数指定了日期监听器
            DatePickerDialog dialog = new DatePickerDialog(this, this,
                    calendar.get(Calendar.YEAR), // 年份
                    calendar.get(Calendar.MONTH), // 月份
                    calendar.get(Calendar.DAY_OF_MONTH)); // 日子
            dialog.show(); // 显示日期对话框
        } else if (v.getId() == R.id.btn_ok) {
            // 获取日期选择器dp_date设定的年月份
            String desc = String.format("使用DatePicker选的日期是%d年%d月%d日",
                    dp_date.getYear(), dp_date.getMonth() + 1, dp_date.getDayOfMonth());
            tv_date.setText(desc);
        }
    }

    // 一旦点击日期对话框上的确定按钮，就会触发监听器的onDateSet方法
    @Override
    public void onDateSet(DatePicker view, int year, int monthOfYear, int dayOfMonth) {
        // 获取日期对话框设定的年月份
        String desc = String.format("通过DatePickerDialog选的日期是%d年%d月%d日",
                year, monthOfYear + 1, dayOfMonth);
        tv_date.setText(desc);
    }
}
