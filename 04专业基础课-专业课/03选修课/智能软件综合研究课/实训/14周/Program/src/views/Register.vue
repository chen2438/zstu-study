<!-- 新增注册界面 -->

<template>
  <!--注册表单的容器-->
  <div class="login_container">
    <!-- <div class="title">
      <span>疲劳驾驶监控中心</span>
    </div> -->
    <!--注册区域-->
    <div class="login_box" style="margin-top: 50px">
      <!--头像-->
      <div class="avatar_box">
        <img src="../assets/img/img_1.png">
      </div>
      <!--表单-->
      <el-form :model="registerForm" :rules="registerRules" ref="registerForm" label- width="0px" class="login_form">
        <el-form-item prop="admin">
          <el-input v-model="registerForm.admin" placeholder="请输入你的用户名" prefix-icon="el-icon-user-solid"></el-input>
        </el-form-item>

        <el-form-item prop="password">
          <el-input type="password" v-model="registerForm.password" placeholder="请输入登录密码"
            prefix-icon="el-icon-lock"></el-input>
        </el-form-item>
        <el-form-item prop="passwordConfirm">
          <el-input type="password" v-model="registerForm.passwordConfirm" placeholder="请确认登录密码"
            prefix-icon="el-icon-lock"></el-input>
        </el-form-item>

        <el-form-item prop="verifyCode">
          <div class="verifyCode_box">
            <el-input v-model="registerForm.verifyCode" placeholder="请输入计算结果" prefix-icon="el-icon-mobile"
              class="verifyCode"></el-input>
            <img src="../assets/img/mskKPg.png" alt="" class="verifyCode_img">
          </div>
        </el-form-item>
        <el-form-item class="login_btn" style="white-space: pre;">
          <router-link to="/login" class="tip-color">已有账号？去登录</router-link>
          {{ ' '.repeat(2) }}
          <el-button type="primary" @click="submitForm('registerForm')">注册</el-button>
          <el-button @click="resetForm('registerForm')">重置</el-button>
        </el-form-item>
      </el-form>
    </div>
  </div>
</template>
  
<script>
import { register } from '@/api/admin'

export default {
  name: 'Register',
  data() {
    return {
      registerForm: {
        admin: '',
        password: '',
        passwordConfirm: '',
        verifyCode: ''
      },
      registerRules: {
        admin: [
          { required: true, message: '请输入管理用户名', trigger: 'blur' },
          { min: 1, max: 12, message: '请输入1-12位', trigger: 'blur' }
        ],
        password: [
          { required: true, message: '请输入登录密码', trigger: 'blur' },
          { min: 6, max: 16, message: '长度在 6 到 16 个字符', trigger: 'blur' }
        ],
        passwordConfirm: [
          { required: true, message: '请再次输入密码', trigger: 'blur' },
          { validator: this.validatePasswordConfirm, trigger: 'blur' }
        ],
        verifyCode: [
          { required: true, message: '请输入计算结果', trigger: 'blur' }
        ]
      },
      flag: 1
    }
  },
  methods: {
    validatePasswordConfirm(rule, value) {
      // console.log('password',this.registerForm.password);
      // console.log('passwordConfirm',this.registerForm.passwordConfirm);
      if (this.registerForm.password === this.registerForm.passwordConfirm) {
        return Promise.resolve();
      } else {
        return Promise.reject('两次输入密码不一致');
      }
    },

    submitForm(registerForm) {
      // eslint-disable-next-line no-unused-expressions
      this.$refs[registerForm].validate(valid => {
        if (!valid) {
          this.$message({
            message: '请完整输入',
            type: 'warning',
            duration: 1200
          })
          this.flag = 0
          return false
        }
      })
      this.getadminRegister()
      // 获取admin的信息
    },
    resetForm(formName) {
      this.$refs[formName].resetFields()
    },

    async getadminRegister() {
      const { data } = await register(this.registerForm.admin, this.registerForm.password, this.registerForm.passwordConfirm)
      // console.log('data', data)
      this.$store.commit('getToken', data.data.token)
      this.$store.commit('getData', data.data.shop)
      if (data.code === 4001) {
        this.$message({
          message: '注册失败，请重新注册',
          type: 'warning',
          duration: 4000
        })
      } else if (data.code === 20000 && this.flag === 1) {
        this.$message({
          message: '注册成功，去登录！',
          type: 'success',
          duration: 4000,
          onClose: () => {
            this.$router.push('/login')
          }
        })
      }
    }
  }
}
</script>
  
<style lang="less" scoped>
.title {
  color: dimgray;
  -webkit-text-stroke: 1px black;
  letter-spacing: 0.04em;
  background-color: #FFFFFF;
  font-size: 50px;
  font-weight: bold;
  text-shadow: 1px -1px black, 2px -2px white;
  text-align: center;
  opacity: 0.45;
}

.login_container {
  height: 100%;
  background-color: #708090;
}

.login_box {
  width: 450px;
  height: 400px;
  background-color: #FFFFFF;
  border-radius: 3px;
  position: absolute;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);

  .avatar_box {
    width: 130px;
    height: 130px;
    border: 1px solid #EEEEEE;
    border-radius: 50%;
    padding: 10px;
    box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);
    margin: -65px auto;
    background-color: #FFFFFF;

    img {
      width: 100%;
      height: 100%;
      border-radius: 50%;
      background-color: #EEEEEE;
    }
  }

  .login_form {
    position: absolute;
    bottom: 0px;
    width: 100%;
    padding: 0px 20px;
    box-sizing: border-box;

    .login_btn {
      display: flex;
      justify-content: flex-end;
    }

    .tip-color {
      color: #708090;
    }

    .tip-color:hover {
      color: red;
    }

    .tip-color:active {
      color: green;
    }

    .verifyCode_box {
      display: flex;

      .verifyCode {
        width: 70%;
        justify-content: left;
      }

      .verifyCode_img {
        width: 30%;
        height: 45px;
        justify-content: flex-end;
      }
    }
  }
}

.login_container {
  margin: 0;
  padding: 0;
  height: 100%;
  background-image: url(../assets/img/img_3.png);
  background-size: cover;
  background-position: center;
}
</style>
  