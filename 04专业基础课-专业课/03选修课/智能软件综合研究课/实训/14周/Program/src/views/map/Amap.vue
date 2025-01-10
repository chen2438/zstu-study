<template>
  <div class="amap-wrapper">
    <el-amap vid="amapContainer" :amap-manager="amapManager" :zoom="zoom" :center="center" :events="events" :class="amap-demo">
      <!--覆盖物 圆-->
<!--      <el-amap-circle :center="[120.154686, 30.326259]" :radius="3" fill-color="#393e43" stroke-color="#393e43" stroke-opacity="0.2" stroke-weight="30"></el-amap-circle>-->
      <!--覆盖物 未启动车辆-->
      <el-amap-marker v-for="(item,index) in stoppedCar" :key="item.id" :content="item.content" :title="item.title" :position="item.position" :vid="index"></el-amap-marker>
      <!--覆盖物 已启动车辆-->
      <el-amap-marker v-for="(item,index) in startCar" :key="item.id"  :content="item.content" :title="item.title" :position="item.position" :vid="index"></el-amap-marker>
      <!--覆盖物 未启动车辆 文字标签-->
      <el-amap-marker v-for="(item,index) in stoppedCar" :key="item.id" :content="item.text" :offset="item.offset" :position="item.position" :vid="index"></el-amap-marker>
      <!--覆盖物 已启动车辆 文字标签-->
      <el-amap-marker v-for="(item,index) in startCar" :key="item.id" :content="item.text" :offset="item.offset" :position="item.position" :vid="index"></el-amap-marker>
    </el-amap>
  </div>
</template>

<script>
import { AMapManager, lazyAMapApiLoaderInstance } from 'vue-amap'
// import { centerLocation } from './centerLocation'
const amapManager = new AMapManager()
export default {
  name: 'Amap',
  data () {
    const _this = this
    return {
      map: null,
      amapManager,
      zoom: 12,
      center: [120.154686, 30.326259],
      events: {
        init (o) {
          // // eslint-disable-next-line no-undef
          // const marker = new AMap.Marker({
          //   positon: [120.154686, 30.326259]
          // })
          // marker.setMap(o)
          lazyAMapApiLoaderInstance.load().then(() => {
            _this.initMap()
          })
        }
      },
      startCar: [],
      stoppedCar: [],
      stoppedCarsMessage: [],
      startCarsMessage: []
    }
  },
  methods: {
    initMap () {
      this.map = amapManager.getMap()
      // 地图初始化完成回调
      this.$emit('callbackComponent', {
        function: 'loadMap'
      })
      // 监控中心定位
      // centerLocation({
      //   map: this.map,
      //   complete: (val) => this.onComplete(val),
      //   error: (val) => this.onError(val)
      // })
    },
    onComplete (data) {
      const lng = data.position.lng
      const lat = data.position.lat
      this.center = [lng, lat]
    },
    onError (data) {

    },
    async findstartCarsData (data) {
      console.log(data)
      this.startCar = data.data.startedCarList
      this.startCarsMessage = data.data.startedCarList
    },
    async findstopCarsData (data) {
      console.log(data)
      this.stoppedCar = data.data.stoppedCarList
      this.stoppedCarsMessage = data.data.stoppedCarList
    }
  },
  mounted () {
    // lazyAMapApiLoaderInstance.load().then(() => {
    //   // your code ...
    //   // eslint-disable-next-line no-undef
    //   this.map = new AMap.Map('amapContainer', {
    //     // eslint-disable-next-line no-undef
    //     center: new AMap.LngLat(120.154686, 30.326259),
    //     zoom: this.zoom
    //   })
    // })
  }
}
</script>

<style>
.amap-wrapper {
  width: 100%;
  height: 580px;
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
