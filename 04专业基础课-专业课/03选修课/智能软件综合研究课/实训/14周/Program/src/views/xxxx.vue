<template>
  <div id="host" >
    <el-row type="flex" justify="start">
      <div class="amap-wrapper" >
        <el-amap
          class="amap-box"
          vid="amap-vue"
          :zoom="zoom"
          :center="center"
        ></el-amap>
      </div>
    </el-row>
    <router-view />
  </div>
</template>

<script>
export default {
  name: 'xxxx',
  data () {
    return {
      zoom: 11,
      center: [120.154686, 30.326259]
    }
  }
}
</script>

<style>
.amap-wrapper {
  width: 100%;
  height: 610px;
  float: right;
}
#host {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

#nav {
  padding: 30px;
}

#nav a {
  font-weight: bold;
  color: #2c3e50;
}

#nav a.router-link-exact-active {
  color: #42b983;
}
</style>
