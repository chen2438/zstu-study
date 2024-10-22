<template>
  <div>
    <h1 class="big" style="float: left">当前路况：用户数量:{{ this.userNum }} 车辆总数:{{ this.carNum }} 未启动车数量:{{ this.stoppedCarNum
    }}
      启动车数量:{{ this.startedCarNum }} </h1>
    <div style="float:left ; clear: both;">
      <el-card style=" background-color:rgba(64, 160, 255, 0.653);">
        <span style="font-size: larger; font-weight: 900; color: black;">最近服务区距您: {{ this.dist }} </span>
      </el-card>
    </div>
    <Amap ref="map" @callbackComponent="callbackComponent"></Amap>
  </div>
</template>

<script>
import Amap from '@/views/map/Amap'
import { findStartedCars, findStoppedCars } from '@/api/car'
import { findCarsAndUser, } from '@/api/driver'
import { updateDiatance } from '../../api/data'
export default {
  name: 'UserHost',
  components: { Amap },
  data() {
    return {
      timer: '',
      carNum: '',
      userNum: '',
      stoppedCarNum: '',
      startedCarNum: '',
      dist: '车辆未启动',
      curlocat: []
    }
  },
  created() {
    this.getCarsAndUser()
  },
  methods: {
    callbackComponent(params) {
      params.function && this[params.function](params.data)
    },
    async getCarsAndUser() {
      const { data } = await findCarsAndUser()
      this.startedCarNum = data.data.startedCarNum
      this.stoppedCarNum = data.data.stoppedCarNum
      this.carNum = this.startedCarNum + this.stoppedCarNum
      this.userNum = data.data.userNum
    },
    // 地图初始化完成之后的回调
    loadMap() {
      this.getStoppedCar()
      this.getStartedCar()
      // 定时器要执行的任务和间隔时间（毫秒）
      this.timer = setInterval(this.getStoppedCar, 5000)
      this.timer = setInterval(this.getStartedCar, 5000)
      this.timer = setInterval(this.getDistance, 5000)

    },
    async getStoppedCar() {
      // eslint-disable-next-line no-unused-vars
      const { data } = await findStoppedCars()
      data.data.stoppedCarList.forEach(item => {
        // eslint-disable-next-line eqeqeq
        item.position = item.carTude.split(',')

        item.content = '<img src="' + require('@/assets/img/blue_car.png') + '" height="22" width="35"/>'
        // item.label = { content: item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|尚未启动', offset: [40, 0] }
        if (item.userName == this.$cookies.get("userName")) item.text = `<div style="width:400px;color: white;background: black">${"本人" + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|尚未启动'}</div>`
        if (item.userName != this.$cookies.get("userName")) item.text = `<div style="width:400px;color: white;background: black">${item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|尚未启动'}</div>`
        item.offset = [10, -50]
      })
      // 调用地图中的方法 获取未使用车辆 (父组件调子组件中的方法)
      this.$refs.map.findstopCarsData(data)
    },
    async getStartedCar() {
      // eslint-disable-next-line no-unused-vars
      const { data } = await findStartedCars()
      data.data.startedCarList.forEach(item => {
        // eslint-disable-next-line eqeqeq
        if (item.userNow == 0 && item.userName == this.$cookies.get("userName")) {
          item.text = `<div style="width:400px;color: black;background: red">${"本人" + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|疲劳驾驶'}</div>`
          // item.text = item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|疲劳驾驶'
          // item.label = { content: item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|疲劳驾驶', offset: [40, 0] }
        } else if (item.userNow == 0 && item.userName != this.$cookies.get("userName")) {
          item.text = `<div style="width:400px;color: black;background: red">${item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|疲劳驾驶'}</div>`
          // item.text = item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|疲劳驾驶'
          // item.label = { content: item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|疲劳驾驶', offset: [40, 0] }
        } else if (item.userNow != 0 && item.userName == this.$cookies.get("userName")) {
          item.text = `<div style="width:400px;color: white;background: #42b983">${"本人" + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|状态正常'}</div>`
          // item.text = item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|状态正常'
          // item.label = { content: item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|状态正常', offset: [40, 0] }
        } else {
          item.text = `<div style="width:400px;color: white;background: #42b983">${item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|状态正常'}</div>`
          // item.text = item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|状态正常'
          // item.label = { content: item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|状态正常', offset: [40, 0] }
        }
        item.offset = [10, -40]
        item.position = item.carTude.split(',')
        // eslint-disable-next-line eqeqeq
        // 获取当前帐户司机的位置
        if (item.userName == this.$cookies.get("userName")) { this.curlocat = item.position }
        item.content = '<img src="' + require('@/assets/img/black_car.png') + '" height="50" width="45"/>'
      })
      // 调用地图中的方法 获取正在使用车辆 (父组件调子组件中的方法)
      this.$refs.map.findstartCarsData(data)
    },
    async getDistance() {
      console.log(this.curlocat)
      const response = await updateDiatance(this.curlocat[0], this.curlocat[1])
      this.dist = response.data.curdist.toFixed(3) + 'km'
      console.log(response)
      console.log(this.dist)
    }
  },
  beforeDestroy: function () {
    // 关闭窗口后清除定时器
    clearInterval(this.timer)
  }
}
</script>

<style></style>
