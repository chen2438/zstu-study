<template>
  <div>
    <!--面包屑-->
    <el-breadcrumb separator-class="el-icon-arrow-right" style="padding-left: 10px;padding-bottom: 10px;font-size: 12px">
      <el-breadcrumb-item :to="{ path: '/adminmain' }">首页</el-breadcrumb-item>
      <el-breadcrumb-item>基础信息</el-breadcrumb-item>
      <el-breadcrumb-item>车辆</el-breadcrumb-item>
    </el-breadcrumb>

    <!--车辆列表卡片-->
    <el-card class="box-card">
      <el-form :inline="true" :model="formInline" class="demo-form-inline">
        <el-row type="flex" justify="start">
          <el-form-item label="车辆位置" style="margin-left: 10px">
            <el-select v-model="formInline.city" placeholder="请选择">
              <el-option
                v-for="item in carCityAndCount"
                :key="item.carTude"
                :label="item.carTude"
                :value="item.carTude">
                <span style="float: left">{{ item.carTude }}</span>
                <span style="float: right; color: #8492a6; font-size: 13px">
                  <span class="el-tag el-tag--success el-tag--mini el-tag--plain">{{ item.cityCount }}</span>
                </span>
              </el-option>
            </el-select>
          </el-form-item>
          <el-form-item label="车牌" style="margin-left: 10px">
            <el-input clearable v-model="formInline.plate" placeholder="请输入车牌"></el-input>
          </el-form-item>
          <el-form-item label="车型" style="margin-left: 10px">
            <el-select v-model="formInline.style" clearable placeholder="请选择">
              <el-option
                v-for="item in formCar"
                :key="item.value"
                :label="item.label"
                :value="item.value">
              </el-option>
            </el-select>
          </el-form-item>
          <el-form-item style="margin-left: 10px"  >
            <el-button icon="el-icon-refresh" @click="resetForm">重置</el-button>
            <el-button type="primary" icon="el-icon-search" @click="myqueryCarList">查询</el-button>
          </el-form-item>
        </el-row>
      </el-form>
      <!--表格内容显示区域-->
      <el-table
        :data="carList"
        border
        :header-cell-style="{'text-align':'center'}"
        :cell-style="{'text-align':'center'}"
        max-height="380px"
        style="width: 100%;">
        <el-table-column
          prop="carId"
          label="编号"
          width="100">
        </el-table-column>
        <el-table-column
          prop="carPlates"
          label="车牌"
          width="150">
        </el-table-column>
        <el-table-column
          prop="carStyle"
          label="车型号"
          width="150">
        </el-table-column>
        <el-table-column
          prop="userName"
          label="司机姓名"
          width="150">
        </el-table-column>
        <el-table-column
          prop="userPhone"
          label="手机号码"
          width="150">
        </el-table-column>
        <el-table-column
          prop="carTude"
          label="车辆位置"
          width="140">
        </el-table-column>
        <el-table-column
          prop="userAddress"
          label="用户地址">
        </el-table-column>
      </el-table>
      <!--分页功能-->
      <el-pagination
        style="padding-top: 20px"
        @size-change="handleSizeChange"
        @current-change="handleCurrentChange"
        :current-page="current"
        :page-sizes="[2,6,10,20]"
        :page-size="pageSize"
        layout="total, sizes, prev, pager, next, jumper"
        :total="total">
      </el-pagination>
    </el-card>

  </div>
</template>

<script>
import { findCarCityAndCount, queryCarList } from '@/api/car'

export default {
  name: 'AdminCar',
  data () {
    return {
      formInline: {
        plate: '',
        style: '',
        city: ''
      },
      // 集合
      carList: [],
      // 城市集合
      cityList: [],
      // 每页显示的条数
      pageSize: 6,
      // 总条数
      total: 200,
      // 当前页
      current: 1,
      carCityAndCount: [],
      formCar: [{
        value: '小型车',
        label: '小型车'
      }, {
        value: '中型车',
        label: '中型车'
      }, {
        value: '大型车',
        label: '大型车'
      }]
    }
  },
  created () {
    // 创建组件的时候调用查询所有车辆的方法
    this.myqueryCarList()
    this.getCarCityAndCount()
  },
  methods: {
    onSubmit () {
      console.log('submit!')
    },
    // 当每一页条数改变的时候，
    handleSizeChange (val) {
      // eslint-disable-next-line no-template-curly-in-string
      console.log(`每页 ${val} 条`)
      // 将val赋值给size
      this.pageSize = val
      // 重新去后台查询数据
      this.myqueryCarList()
    },
    // 当页码改变的时候
    handleCurrentChange (val) {
      // eslint-disable-next-line no-template-curly-in-string
      console.log(`当前页: ${val}`)
      this.current = val
      this.myqueryCarList()
    },
    async getCarCityAndCount () {
      const { data } = await findCarCityAndCount()
      console.log(data)
      this.carCityAndCount = data.data.carCityAndCount
    },
    async myqueryCarList () {
      // eslint-disable-next-line no-unused-vars
      const { data } = await queryCarList(this.current, this.pageSize,
        this.formInline.city, this.formInline.plate, this.formInline.style)
      this.carList = data.data.records
      this.total = data.data.total
      console.log(data)
      console.log('current:' + data.data.current)
      console.log('total:' + data.data.total)
    },
    resetForm () {
      this.formInline.plate = ''
      this.formInline.style = ''
      this.formInline.city = ''
      this.myqueryCarList()
    }
  }

}
</script>

<style scoped>

</style>
