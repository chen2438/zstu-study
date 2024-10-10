package com.example.chapter07.adapter;

import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;

import com.example.chapter07.bean.GoodsInfo;
import com.example.chapter07.fragment.DynamicFragment;

import java.util.ArrayList;
import java.util.List;
//官方推荐使用：ViewPager2，1.Activity 布局文件中引入 ViewPager2 控件
// 2. 编写Fragment用于填充到ViewPager2中
// 3. 编写Adapter实现FragmentStateAdapter
public class MobilePagerAdapter extends FragmentPagerAdapter {
    private List<GoodsInfo> mGoodsList = new ArrayList<GoodsInfo>(); // 声明一个商品列表

    // 碎片页适配器的构造方法，传入碎片管理器与商品信息列表
    public MobilePagerAdapter(FragmentManager fm, List<GoodsInfo> goodsList) {
        super(fm, BEHAVIOR_RESUME_ONLY_CURRENT_FRAGMENT);
        mGoodsList = goodsList;
    }

    // 获取碎片Fragment的个数
    public int getCount() {
        return mGoodsList.size();
    }

    // 获取指定位置的碎片Fragment,使用newInstance方法给碎片对象传递参数信息
    public Fragment getItem(int position) {
        return DynamicFragment.newInstance(position,
                mGoodsList.get(position).pic, mGoodsList.get(position).desc);
    }

    // 获得指定碎片页的标题文本
    public CharSequence getPageTitle(int position) {
        return mGoodsList.get(position).name;
    }
}

