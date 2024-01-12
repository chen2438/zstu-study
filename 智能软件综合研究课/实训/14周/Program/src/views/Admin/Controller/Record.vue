<template>
  <div>
    <!--面包屑-->
    <el-breadcrumb separator-class="el-icon-arrow-right" style="padding-left: 10px;padding-bottom: 10px;font-size: 12px">
      <el-breadcrumb-item :to="{ path: '/adminmain' }">首页</el-breadcrumb-item>
      <el-breadcrumb-item>监控中心</el-breadcrumb-item>
      <el-breadcrumb-item>疲劳记录</el-breadcrumb-item>
    </el-breadcrumb>
  </div>
</template>

<script>
export default {
  name: 'AdminRecord'
}
</script>

<style scoped>

</style>
