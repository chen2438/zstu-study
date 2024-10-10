<template>
    <div>
      <h1 class="big" style="float: left">用户数量:{{this.userNum}} 车辆总数:{{this.carNum}}  未启动车数量:{{this.stoppedCarNum}} 启动车数量:{{this.startedCarNum}}      </h1>
      <el-button style="margin-left: 40px" type="danger" size="mini" @click="handledangerClick">警告疲劳</el-button>
      <Amap ref="map" @callbackComponent="callbackComponent"></Amap>
    </div>
</template>

<script>
import Amap from '@/views/map/Amap'
import { findStartedCars, findStoppedCars } from '@/api/car'
import { findCarsAndUser, warningAllTiredUser } from '@/api/driver'
export default {
  name: 'AdminHost',
  components: { Amap },
  data () {
    return {
      timer: '',
      carNum: '',
      userNum: '',
      stoppedCarNum: '',
      startedCarNum: ''
    }
  },
  created () {
    this.getCarsAndUser()
  },
  methods: {
    callbackComponent (params) {
      params.function && this[params.function](params.data)
    },
    async handledangerClick () {
      const { data } = await warningAllTiredUser()
      console.log(data)
      if (data.code === 20000) {
        this.$message({
          message: '成功向所有疲劳用户发起警报',
          type: 'success',
          duration: 2000
        })
      }
    },
    async getCarsAndUser () {
      const { data } = await findCarsAndUser()
      this.startedCarNum = data.data.startedCarNum
      this.stoppedCarNum = data.data.stoppedCarNum
      this.carNum = this.startedCarNum + this.stoppedCarNum
      this.userNum = data.data.userNum
    },
    // 地图初始化完成之后的回调
    loadMap () {
      this.getStoppedCar()
      this.getStartedCar()
      // 定时器要执行的任务和间隔时间（毫秒）
      this.timer = setInterval(this.getStoppedCar, 5000)
      this.timer = setInterval(this.getStartedCar, 5000)
    },
    async getStoppedCar () {
      // eslint-disable-next-line no-unused-vars
      const { data } = await findStoppedCars()
      data.data.stoppedCarList.forEach(item => {
        // eslint-disable-next-line eqeqeq
        item.position = item.carTude.split(',')
        item.content = '<img src="' + require('@/assets/img/blue_car.png') + '" height="22" width="35"/>'
        // item.label = { content: item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|尚未启动', offset: [40, 0] }
        item.text = `<div style="width:400px;color: white;background: black">${item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|尚未启动'}</div>`
        item.offset = [10, -50]
      })
      // 调用地图中的方法 获取未使用车辆 (父组件调子组件中的方法)
      this.$refs.map.findstopCarsData(data)
    },
    async getStartedCar () {
      // eslint-disable-next-line no-unused-vars
      const { data } = await findStartedCars()
      data.data.startedCarList.forEach(item => {
        // eslint-disable-next-line eqeqeq
        if (item.userNow == 0) {
          item.text = `<div style="width:400px;color: black;background: red">${item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|疲劳驾驶'}</div>`
          // item.text = item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|疲劳驾驶'
          // item.label = { content: item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|疲劳驾驶', offset: [40, 0] }
        } else {
          item.text = `<div style="width:400px;color: white;background: #42b983">${item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|状态正常'}</div>`
          // item.text = item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|状态正常'
          // item.label = { content: item.userName + '|' + item.userPhone + '|' + item.carStyle + '|' + item.carPlates + '|状态正常', offset: [40, 0] }
        }
        item.offset = [10, -40]
        item.position = item.carTude.split(',')
        item.content = '<img src="' + require('@/assets/img/black_car.png') + '" height="50" width="45"/>'
      })
      // 调用地图中的方法 获取正在使用车辆 (父组件调子组件中的方法)
      this.$refs.map.findstartCarsData(data)
    }
  },
  beforeDestroy: function () {
    // 关闭窗口后清除定时器
    clearInterval(this.timer)
  }
}
</script>

<style>

</style>
