<template>
  <div>
    <!--面包屑-->
    <el-breadcrumb separator-class="el-icon-arrow-right" style="padding-left: 10px;padding-bottom: 10px;font-size: 12px">
      <el-breadcrumb-item :to="{ path: '/adminmain' }">首页</el-breadcrumb-item>
      <el-breadcrumb-item>基础信息</el-breadcrumb-item>
      <el-breadcrumb-item>司机</el-breadcrumb-item>
    </el-breadcrumb>

    <!--司机基础信息卡片-->
    <el-card class="box-card" >
      <!--用户司机信息表格-->
      <el-table
        max-height="369px"
        :data="userList"
        border
        :header-cell-style="{'text-align':'center'}"
        :cell-style="{'text-align':'center'}"
        style="width: 100%">
        <el-table-column
          prop="userId"
          label="用户编号"
          width="100">
        </el-table-column>
        <el-table-column
          prop="userName"
          label="姓名"
          width="150">
        </el-table-column>
        <el-table-column
          prop="userPhone"
          label="用户电话"
          width="200">
        </el-table-column>
        <el-table-column
          prop="userTime"
          label="注册时间"
          width="200">
        </el-table-column>
        <el-table-column
          prop="userScore"
          label="司机驾驶分"
          width="150">
        </el-table-column>
        <el-table-column
          prop="userAddress"
          label="家庭地址">
        </el-table-column>
        <el-table-column
          label="操作"
          width="180">
          <template slot-scope="scope">
            <el-button type="primary" size="mini" icon="el-icon-edit" @click="showEditDialog(scope.row.userId)"></el-button>
            <el-button type="danger" size="mini" icon="el-icon-delete" @click="removeUserById(scope.row.userId)"></el-button>
          </template>
        </el-table-column>
      </el-table>
      <!--分页功能-->
      <div class="block">
        <span class="demonstration"></span>
        <el-pagination
          style="padding-top: 20px"
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
          :current-page="current"
          :page-sizes="[2, 6, 10, 20]"
          :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total">
        </el-pagination>
      </div>
    </el-card>

    <!--修改用户司机的对话框-->
    <el-dialog title="修改司机信息" :visible.sync="editDialogVisible" width="40%" @close="editDialogClosed">
      <el-form :model="editForm" :rules="editFormRules" ref="editFormRef" label-width="90px">
        <el-form-item label="用户编号">
          <el-input v-model="editForm.userId" disabled></el-input>
        </el-form-item>
        <el-form-item label="姓名" >
          <el-input v-model="editForm.userName" disabled></el-input>
        </el-form-item>
        <el-form-item label="手机号码">
          <el-input v-model="editForm.userPhone" disabled></el-input>
        </el-form-item>
        <el-form-item label="驾照扣分">
          <el-input v-model="editForm.userScore" ></el-input>
        </el-form-item>
        <el-form-item label="扣分原因">
          <el-input v-model="this.reason"></el-input>
        </el-form-item>
      </el-form>
      <span slot="footer" class="dialog-footer">
        <el-button @click="editDialogVisible = false">取消</el-button>
        <el-button type="primary" @click="editUserInfo">确定</el-button>
      </span>
    </el-dialog>

  </div>
</template>

<script>

// eslint-disable-next-line no-unused-vars
import { deleteUser, editUser, findUserList, getUserById } from '@/api/driver'

export default {
  name: 'AdminDriver',
  data () {
    return {
      // 用户集合
      userList: [],
      // 每页显示的条数
      pageSize: 6,
      // 总条数
      total: 200,
      // 当前页
      current: 1,
      // 控制修改司机对话框的显示和隐藏
      editDialogVisible: false,
      // 查询到的司机信息
      editForm: {},
      reason: "",
      // 修改分类表单的验证规则
      editFormRules: {
        userScore: [
          { required: true, message: '驾照所扣分数不能为空', trigger: 'blur' }
        ],
        reason: [
          { required: true, message: '扣分原因不能为空', trigger: 'blur' }
        ]
      }
    }
  },
  created () {
    this.getUserList()
  },
  methods: {
    onSubmit () {
      console.log('submit!')
    },
    handleSizeChange (val) {
      console.log(`每页 ${val} 条`)
      // 将val赋值给size
      this.pageSize = val
      // 重新从后台查询数据
      this.getUserList()
    },
    handleCurrentChange (val) {
      console.log(`当前页: ${val}`)
      this.current = val
      this.getUserList()
    },
    // 返回对应分页查询的用户司机信息
    async getUserList () {
      // eslint-disable-next-line no-unused-vars
      const { data } = await findUserList(this.current, this.pageSize)
      this.userList = data.data.records
      this.userList = this.userList.filter(user => user.type !== 0);
      this.total = data.data.total
      console.log(data.data)
      console.log('current:' + data.data.current)
      console.log('total:' + data.data.total)
    },
    // 展示编辑用户的对话框
    async showEditDialog (userId) {
      // eslint-disable-next-line no-unused-vars
      const { data } = await getUserById(userId)
      console.log(data.data)
      if (data.code !== 20000) {
        return this.$message.error('查询对应数据失败！')
      }
      this.editForm = data.data.user
      this.editDialogVisible = true
    },
    // 监听修改司机对话框的关闭事件
    editDialogClosed () {
      // eslint-disable-next-line no-unused-expressions
      this.$refs.editFormRef.resetFields()
    },
    // 修改司机信息并提交
    editUserInfo () {
      // eslint-disable-next-line no-unused-expressions
      this.$refs.editFormRef.validate(async valid => {
        // eslint-disable-next-line no-useless-return
        if (!valid) return
        // 发起修改信息的数据申请
        // eslint-disable-next-line no-unused-vars
        const { data } = await editUser(this.editForm.userId, this.editForm.userScore, this.reason)
        console.log(data.data)
        if (data.code !== 20000) {
          return this.$message.error('更新司机信息失败')
        }
        this.getUserList()
        this.editDialogVisible = false
        this.$message.success('更新司机信息成功')
      })
    },
    // 根据Id删除对应的司机信息
    async removeUserById (userId) {
      // 弹框提示
      // eslint-disable-next-line no-unused-vars
      const confirmResult = await this.$confirm('此操作将永久删除该用户信息, 是否继续?', '警示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).catch(err => {
        return err
      })
      // 如果点击确定返回字符串 confirm
      // 如果点击取消返回字符串 cancel
      if (confirmResult !== 'confirm') {
        return this.$message.info('已经取消删除')
      }
      // eslint-disable-next-line no-unused-vars
      const { data } = await deleteUser(userId)
      console.log(data)
      if (data.code !== 20000) {
        return this.$message.error('删除本司机信息失败')
      }
      this.$message.success('删除本司机信息成功')
      this.getUserList()
    }
  }
}
</script>

<style scoped>

</style>
