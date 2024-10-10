<template>
  <div>
    <template>
      <el-submenu index="/systemManage">
        <template slot="title">
          <i class="el-icon-setting"></i>
          <span>系统管理</span>
        </template>
        <!--        <el-menu-item index="/welcome" >-->
        <!--          <i class="el-icon-star-off"></i>-->
        <!--          <span slot="title">控制面板</span>-->
        <!--        </el-menu-item>-->
        <el-menu-item index="/userhost">
          <i class="el-icon-s-home"></i>
          <span slot="title">主界面</span>
        </el-menu-item>
      </el-submenu>

      <el-submenu index="/userbusinessManage">
        <template slot="title">
          <i class="el-icon-tickets"></i>
          <span>个人中心</span>
        </template>
        <el-menu-item index="/userinfo" >
          <i class="el-icon-user"></i>
          <span slot="title">基础信息</span>
        </el-menu-item>
        <el-menu-item index="/userintro" >
          <i class="el-icon-info"></i>
          <span slot="title">交规必知</span>
        </el-menu-item>
      </el-submenu>

      <el-submenu index="/usermonitor">
        <template slot="title">
          <i class="el-icon-camera-solid"></i>
          <span>监控中心</span>
        </template>
        <el-menu-item index="/userdata">
          <i class="el-icon-date"></i>
          <span slot="title">实时数据</span>
        </el-menu-item>
        <el-menu-item index="/user-video-surveillance">
          <i class="el-icon-video-camera"></i>
          <span slot="title">视频监控</span>
        </el-menu-item>

      </el-submenu>
    </template>
  </div>
</template>

<script>
export default {
  name: 'UserMenuTree'
}
</script>

<style scoped>
/*实现了溢出处理*/
.el-menu--collapse span,
.el-menu--collapse i.el-submenu__icon-arrow {
  height: 0;
  width: 0;
  overflow: hidden;
  visibility: hidden;
  display: inline-block;
}
</style>
