<template>
  <div>
    <div>
      <!--面包屑-->
      <el-breadcrumb separator-class="el-icon-arrow-right"
        style="padding-left: 10px;padding-bottom: 10px;font-size: 12px">
        <el-breadcrumb-item :to="{ path: '/adminmain' }">首页</el-breadcrumb-item>
        <el-breadcrumb-item>监控中心</el-breadcrumb-item>
        <el-breadcrumb-item>实时数据</el-breadcrumb-item>
      </el-breadcrumb>
    </div>

    <!--司机基础信息卡片-->
    <el-card class="box-card">
      <!--用户司机信息表格-->
      <el-table max-height="369px" :data="userList" border :header-cell-style="{ 'text-align': 'center' }"
        :cell-style="{ 'text-align': 'center' }" style="width: 100%">
        <el-table-column prop="userId" label="用户编号">
        </el-table-column>
        <el-table-column prop="userName" label="姓名">
        </el-table-column>
        <el-table-column prop="carPlates" label="当前驾驶车牌">
        </el-table-column>
        <el-table-column prop="tiredSituation" label="十分钟内疲劳情况">
        </el-table-column>
        <el-table-column prop="reminded" label="被提醒次数">
        </el-table-column>
        <el-table-column prop="curtimes" label="行车时间">
        </el-table-column>
        <el-table-column label="警示">
          <template slot-scope="scope">
            <el-button type="warning" @click="warningClick(scope.row.userId)">警示</el-button>
          </template>
        </el-table-column>
        <el-table-column label="扣分">
          <template slot-scope="scope">
            <el-button type="danger" @click="showEditDialog(scope.row.userId)">扣分</el-button>
          </template>
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
    <el-dialog title="扣分" :visible.sync="editDialogVisible" width="40%" @close="editDialogClosed">
      <el-form :model="editForm" :rules="editFormRules" ref="editFormRef" label-width="90px">
        <el-form-item label="用户编号">
          <el-input v-model="editForm.userId" disabled></el-input>
        </el-form-item>
        <el-form-item label="姓名">
          <el-input v-model="editForm.userName" disabled></el-input>
        </el-form-item>
        <el-form-item label="手机号码">
          <el-input v-model="editForm.userPhone" disabled></el-input>
        </el-form-item>
        <el-form-item label="驾照分数">
          <el-input v-model="editForm.userScore" disabled></el-input>
        </el-form-item>
        <el-form-item label="本次扣分">
          <el-input v-model="editForm.changePoints"></el-input>
        </el-form-item>
        <el-form-item label="扣分原因">
          <el-input v-model="editForm.reason"></el-input>
        </el-form-item>
      </el-form>
      <span slot="footer" class="dialog-footer">
        <el-button @click="editDialogVisible = false">取消</el-button>
        <el-button type="primary" @click="editUserInfo()">确定</el-button>
      </span>
    </el-dialog>
  </div>
</template>

<script>
import { findUserTired } from '@/api/data'
import { warningtiredUserById, getUserById, editUser } from '@/api/driver'
import io from 'socket.io-client';
export default {
  name: 'AdminData',
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
      editDialogVisible: false,
      editForm: {},
      socket: io(process.env.VUE_APP_SOCKET_URL),
      reason: "",
      editFormRules: {
        changePoints: [
          { required: true, message: '驾照所扣分数不能为空', trigger: 'blur' }
        ],
        reason: [
          { required: true, message: '扣分原因不能为空', trigger: 'blur' }
        ],
      }
    }
  },
  created() {
    // 创建组件的时候调用查询所有车辆的方法
    this.getUserTired()
    this.userList = this.userList.filter(user => user.type !== 0);
  },
  mounted() {
    this.socket.on('response', (data) => {
      this.userList = data.tired
    });
  },
  methods: {
    async getUserTired() {
      const { data } = await findUserTired(this.current, this.pageSize)
      console.log(data.data.UserAll)
      this.total = data.data.total
      this.userList = data.data.UserAll
      console.log('current:' + data.data.current)
      console.log('total:' + data.data.total)
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
    async warningClick(userId) {
      // 弹框提示
      // eslint-disable-next-line no-unused-vars
      const confirmResult = await this.$confirm('是否提醒该用户疲劳驾驶?', '警示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).catch(err => {
        return err
      })
      // 如果点击确定返回字符串 confirm
      // 如果点击取消返回字符串 cancel
      if (confirmResult !== 'confirm') {
        return this.$message.info('已经取消提醒')
      }
      // eslint-disable-next-line no-unused-vars
      const { data } = await warningtiredUserById(userId)
      console.log(data)
      if (data.code === 3014) {
        return this.$message.error('本用户未驾驶车辆')
      }
      this.$message.success('警示成功')
      this.getUserTired()
    },
    // 展示扣分的对话框
    async showEditDialog(userId) {
      // eslint-disable-next-line no-unused-vars
      const { data } = await getUserById(userId)
      console.log(data.data)
      if (data.code !== 20000) {
        return this.$message.error('查询对应数据失败！')
      }
      this.editForm = data.data.user
      this.editDialogVisible = true
    },
    // 监听扣分对话框的关闭事件
    editDialogClosed() {
      // eslint-disable-next-line no-unused-expressions
      this.$refs.editFormRef.resetFields()
    },
    // 扣分并提交
    editUserInfo() {
      this.$refs.editFormRef.validate(async valid => {
        console.log(123456, this.editForm.changePoints, this.editForm.reason)
        if (!valid) return
        const { data } = await editUser(this.editForm.userId, this.editForm.changePoints, this.editForm.reason)
        if (data.code !== 20000 || !this.editForm.changePoints || !this.editForm.reason) {
          return this.$message.error('扣分失败')
        }
        this.getUserTired()
        this.editDialogVisible = false
        this.$message.success('扣分成功')
      })
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
