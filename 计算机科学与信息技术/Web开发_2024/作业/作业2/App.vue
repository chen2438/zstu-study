<template>
  <div class="add-good">
    <span class="name">
      <span>商品名称：</span><input class="name-input" v-model="add_name" placeholder="请输入商品名称">
      <span style="margin-left: 5px">商品价格：</span><input class="price-input" v-model="add_price" placeholder="请输入商品价格">
    </span>
    <button class="add-btn" @click="addGood" style="margin-left: 5px">添加商品</button>
  </div>
  <div class="goods_list">
    <!-- 无序列表 -->
    <ul>
      <li v-for="good in goods_list" :key="good.name">
        <span>商品名称：{{ good.name }}---</span>
        <span>商品单价：{{ good.price }}</span>
        <button @click="addCart(good)" style="margin-left: 5px">添加到购物车</button>
      </li>
    </ul>
  </div>
  <div class="cart_list">
    <!-- 表格 -->
    <table class="cart_table">
      <thead>
      <tr>
        <th><span>选择</span><input type="checkbox" v-model="selectAll" @change="selectAll_func(selectAll)"></th>
        <th>商品名称</th>
        <th>商品单价</th>
        <th>商品数量</th>
        <th>价格</th>
      </tr>
      </thead>
      <tbody>
      <tr v-for="good in cart_list" :key="good.name">
        <td><input type="checkbox" v-model="good.isSelected" @change="isSelect_func(good.isSelected)"></td>
        <td>{{ good.name }}</td>
        <td>{{ good.price }}</td>
        <td>
          <button @click="subCart(good)">-</button>
          {{ good.count }}
          <button @click="addCart(good)">+</button>
        </td>
        <td>{{ good.total_price }}</td>
      </tr>
      <tr>
        <td colspan="2">选中的商品：{{ selected_count }}/{{ total_count }}</td>
        <td colspan="3">需付总价格：{{ total_value }}</td>
      </tr>
      </tbody>
    </table>
  </div>
</template>

<script setup>
import {ref} from "vue";

const add_name = ref('');
const add_price = ref('');

const goods_list = ref([
  {name: '小酥肉', price: 10},
  {name: '炸鸡柳', price: 15},
  {name: '酱烧鸡', price: 50},
  {name: '电脑', price: 7000},
]);

const selectAll = ref(true);
const selected_count = ref(0);
const total_count = ref(0);
const total_value = ref(0);
const selectAll_func = (selectAll) => {
  cart_list.value.forEach(item => {
    item.isSelected = selectAll;
  });
  count_total();
}

const isSelect_func = () => {
  selectAll.value = cart_list.value.every(item => item.isSelected);
  count_total();
}


const cart_list = ref([
  {name: '酸辣粉', price: 8, count: 5, isSelected: true, total_price: 40},
  {name: '麻辣烫', price: 15, count: 13, isSelected: true, total_price: 195},
]);

const addGood = () => {
  if (!add_name.value || !add_price.value) {
    alert('请输入商品名称和价格');
    return;
  }
  goods_list.value.push({
    name: add_name.value,
    price: add_price.value
  });
  add_name.value = '';
  add_price.value = '';
}

const addCart = (good) => {
  if (cart_list.value.some(item => item.name === good.name)) {
    cart_list.value.forEach(item => {
      if (item.name === good.name) {
        item.count++;
        item.total_price = item.count * item.price;
      }
    });
  } else {
    cart_list.value.push({
      isSelected: true,
      name: good.name,
      price: good.price,
      count: 1,
      total_price: good.price * 1
    });
  }
  count_total();
}
const subCart = (good) => {
  if (cart_list.value.some(item => item.name === good.name)) {
    cart_list.value.forEach(item => {
      if (item.name === good.name) {
        item.count--;
        item.total_price = item.count * item.price;
        if (item.count === 0) {
          cart_list.value.splice(cart_list.value.indexOf(item), 1);
        }
      }
    });
  } else {
    alert('错误：购物车中没有该商品');
  }
  count_total();
}

const count_total = () => {
  total_value.value = 0;
  total_count.value = 0;
  selected_count.value = 0;
  cart_list.value.forEach(item => {
    if (item.isSelected) {
      total_value.value += item.total_price;
      selected_count.value += 1;
    }
    total_count.value++;
  })
}

count_total();
</script>

<style>
    .cart_table{
      border-top: #787878 solid 2px;
      border-left: #787878 solid 2px;
      border-bottom: black solid 2px;
      border-right: black solid 2px;
    }
    .cart_table th{
      border-top: black solid 2px;
      border-left: black solid 2px;
      border-right: #787878 solid 2px;
      border-bottom: #787878 solid 2px;
    }
    .cart_table td{
      border-top: black solid 2px;
      border-left: black solid 2px;
      border-right: #787878 solid 2px;
      border-bottom: #787878 solid 2px;
    }
</style>
