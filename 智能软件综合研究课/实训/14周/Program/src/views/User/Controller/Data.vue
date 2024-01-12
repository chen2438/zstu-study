<template>
  <div>
    <div>
      <!--面包屑-->
      <el-breadcrumb separator-class="el-icon-arrow-right"
        style="padding-left: 10px;padding-bottom: 10px;font-size: 12px">
        <el-breadcrumb-item :to="{ path: '/usermain' }">首页</el-breadcrumb-item>
        <el-breadcrumb-item>监控中心</el-breadcrumb-item>
        <el-breadcrumb-item>实时数据</el-breadcrumb-item>
      </el-breadcrumb>
    </div>

    <!--司机基础信息卡片-->
    <el-card class="box-card">
      <!--用户司机信息表格-->
      <el-table max-height="369px" :data="userList" border :header-cell-style="{ 'text-align': 'center' }"
        :cell-style="{ 'text-align': 'center' }" style="width: 100% ;">
        <el-table-column prop="userId" label="用户编号">
        </el-table-column>
        <el-table-column prop="userName" label="姓名">
        </el-table-column>
        <el-table-column prop="carPlates" label="当前驾驶车牌">
        </el-table-column>
        <el-table-column prop="tiredSituation" label="十分钟内疲劳情况">
        </el-table-column>
        <el-table-column prop="times" label="总疲劳次数(次/1min)">
        </el-table-column>
        <el-table-column prop="reminded" label="被提醒次数">
        </el-table-column>
        <el-table-column prop="curtimes" label="行车时间">
        </el-table-column>
      </el-table>
      <!--分页功能-->
      <div class="block">
        <span class="demonstration"></span>
        <el-pagination style="padding-top: 20px" @size-change="handleSizeChange" @current-change="handleCurrentChange"
          :current-page="current" :page-sizes="[2, 6, 10, 20]" :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper" :total="total">
        </el-pagination>
      </div>
    </el-card>
  </div>
</template>

<script>
import { findUserTired } from '@/api/data'
import io from 'socket.io-client';


export default {
  name: 'UserData',
  data() {
    return {
      // 用户集合
      userList: [],
      // 每页显示的条数
      pageSize: 6,
      // 总条数
      total: 200,
      // 当前页
      current: 1,
      socket: io(process.env.VUE_APP_SOCKET_URL)
    }
  },
  created() {
    // 创建组件的时候调用查询所有车辆的方法
    this.getUserTired()
  },
  mounted() {
    this.socket.on('response', (data) => {
      this.userList = data.tired
      this.userList = this.userList.filter(user => user["userId"] == this.$cookies.get('usersessionid'));
    });
  },
  methods: {
    async getUserTired() {
      const response = await findUserTired(this.current, this.pageSize)
      const { code, data } = response.data
      console.log(data.UserAll)
      this.total = data.total
      this.userList = data.UserAll
      this.userList = this.userList.filter(user => user["userId"] == this.$cookies.get('usersessionid'));
      console.log(this.userList)
      console.log('total:' + data.total)
    },
    handleSizeChange(val) {
      console.log(`每页 ${val} 条`)
      // 将val赋值给size
      this.pageSize = val
      // 重新从后台查询数据
      this.getUserTired()
    },
    handleCurrentChange(val) {
      console.log(`当前页: ${val}`)
      this.current = val
      this.getUserTired()
    },
  }
}
</script>

<style lang="scss" scoped>
.data-show-container {
  .chartComponent {
    margin: 20px;
    background: #1d344d;

    .el-header {
      text-align: left;
    }
  }

  .left-container {
    float: left;
    width: 500px;

    .categoryChart {
      color: #ffffff;
    }
  }

  .middle-container {
    float: left;
    width: calc(100vw - 1020px);

    .radialChart {
      color: #ffffff;
    }

    .chinaSdkMap {
      color: #ffffff;
    }
  }

  .right-container {
    float: left;
    width: 500px;

    .circleLineChart {
      color: #ffffff;
    }
  }
}
</style>
