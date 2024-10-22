<template>
  <div class="home">
    <img src="../assets/img/scai.png" alt="" style="position: fixed; left:25%; top: 10%;" />
    <el-row :gutter="0">
      <el-col :span="3" :offset="22" class="top" style="margin-top: 11px">
        <el-button :span="3" type="primary" @click="gotologin">登录</el-button>

      </el-col>
    </el-row>
    <el-row style="margin-top: 300px;margin-left: 300px">
      <el-col :span="8" class="t1">
        <div class="text text1">{{ startedCarNum }}</div>
        <div class="textt tt1">正在使用</div>
      </el-col>
      <el-col :span="8" class="t2">
        <div class="text text2">{{ carNum }}</div>
        <div class="textt tt2">车辆数目</div>
      </el-col>
      <el-col :span="8" class="t3">
        <div class="text text3">{{ userNum }}</div>
        <div class="textt tt3">注册用户
        </div>
      </el-col>
    </el-row>
  </div>
</template>

<script>
import { findCarsAndUser } from '@/api/driver'

export default {
  name: 'home',
  components: {},
  data() {
    return {
      startedCarNum: 111,
      carNum: 2222,
      userNum: 33333
    }
  },
  created() {
    // Vue.axios.get('http://localhost:5000/home/').then((response) => {
    //   response = JSON.parse(response.request.responseText)
    //   if (response.code === 200) {
    //     (this.project_num = response.data.project_num),
    //     (this.task_num = response.data.task_num),
    //     (this.user_num = response.data.user_num)
    //   }
    // })
    this.getCarsAndUser()
  },
  methods: {
    async getCarsAndUser() {
      const { data } = await findCarsAndUser()
      this.startedCarNum = data.data.startedCarNum
      this.stoppedCarNum = data.data.stoppedCarNum
      this.carNum = this.startedCarNum + this.stoppedCarNum
      this.userNum = data.data.userNum
    },
    gotologin() {
      this.$router.push('/login')
    },
    guestEnter() {
      this.$router.push('/host')
    }
  }
}
</script>
<style>
.home {
  /* background: url(../assets/img/img_3.png) no-repeat;
  background-size: 100% 770px;
  overflow: hidden;
  height: 100%; */
  margin: 0;
  padding: 0;
  height: 100%;
  background-image: url(../assets/img/img_3.png);
  background-size: cover;
  background-position: center;
}

.text,
.textt {
  font-size: 1.5rem;
  color: #fff;
}
</style>
