<template>
  <el-container class="main_container">
    <!--头部布局-->
    <el-header>
      <div class="left_box">
        <img src="../../assets/img/img_1.png">
        <span>司机——疲劳驾驶监控中心</span>
      </div>
      <div class="right_box">
        <el-dropdown>
          <img src="../../assets/img/img_1.png">
          <!--下拉菜单-->
          <el-dropdown-menu slot="dropdown">
            <el-dropdown-item icon="el-icon-s-home" @click.native="change">首页信息</el-dropdown-item>
            <el-dropdown-item icon="el-icon-switch-button" @click.native="quit">退出登录</el-dropdown-item>
          </el-dropdown-menu>
        </el-dropdown>
      </div>
    </el-header>
    <el-container>
      <!--侧边栏-->
      <el-aside :width="isCollapse?'64px':'200px'">
        <!--展开收起-->
        <div class="toggle_box" @click="toggleCollapse">|||</div>
        <el-menu
          default-active="2"
          class="el-menu-vertical-demo"
          @open="handleOpen"
          @close="handleClose"
          background-color="#001529"
          text-color="#fff"
          active-text-color="#ffd04b"
          :collapse="isCollapse"
          :collapse-transition="false"
          :unique-opened="true"
          :router="true">
          <UserMenuTree></UserMenuTree>
        </el-menu>
      </el-aside>
      <el-main>
        <!--路由视图-->
        <router-view></router-view>
      </el-main>
    </el-container>
  </el-container>
</template>

<script>
// eslint-disable-next-line no-unused-vars
import UserMenuTree from '@/components/UserMenuTree'
export default {
  name: 'UserMain',
  components: { UserMenuTree },
  data () {
    return {
      isCollapse: false
    }
  },
  methods: {
    toggleCollapse () {
      this.isCollapse = !this.isCollapse
    },
    quit () {
      window.sessionStorage.clear()
      this.$router.push('/login')
    },
    change () {
      this.$router.push('/userhost')
    }
  }
}
</script>

<style lang="less" scoped>
.el-container{
  height: 100%;
}
/*头部布局*/
.el-header {
  background-color: #001529;
  display: flex;
  justify-content: space-between;
  padding-left: 0;
  color: #FFFFFF;
  align-items: center;
  font-size: 20px;
/*左边的logo和标题*/
.left_box{
  display: flex;
  align-items: center;
  font-size: 30px;
  color: #F0F8FF;
/*logo*/
img{
  width: 55px;
  height: 55px;
  border-radius: 30%;
  margin: 0px 0px 5px 5px;
}
/*标题*/
span{
  margin-left: 15px;
}
}
/*右边的登录头像*/
.right_box{
.el-dropdown>img{
  height: 55px;
  width: 55px;
  border-radius: 50%;
  background-color: #FFFFFF;
  margin: 0px 15px 0px 0px;
  background-size: contain;
}
}

}
/*侧边栏*/
.el-aside {
  background-color: #001529;
  text-align: left;
.el-menu{
  border-right: none;
}
/*展开/收起*/
.toggle_box{
  background-color: white;
  font-size: 15px;
  font-weight: bold;
  line-height: 25px;
  color: black;
  letter-spacing: 0.2em;
  text-align: center;
  cursor: pointer;
}
}
/*内容主体*/
.el-main {
  background-color: #E9EEF3;
}
/*菜单下拉样式*/
.el-dropdown-link {
  cursor: pointer;
  color: #409EFF;
}
</style>
