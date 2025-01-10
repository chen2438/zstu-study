<template>
  <div class="mapcontainer">
    <!--    <div class="search-box">-->
    <!--      <input v-model="searchKey" type="search" id="search" />-->
    <!--      <button @click="searchByHand">搜索</button>-->
    <!--      <div class="tip-box" id="searchTip"></div>-->
    <!--    </div>-->
    <!--
        amap-manager： 地图管理对象
        vid：地图容器节点的ID
        zooms： 地图显示的缩放级别范围，在PC上，默认范围[3,18]，取值范围[3-18]；在移动设备上，默认范围[3-19]，取值范围[3-19]
        center： 地图中心点坐标值
        plugin：地图使用的插件
        events： 事件
    -->
    <el-amap
      class="amap-box"
      :amap-manager="amapManager"
      :vid="'amap-vue'"
      :zoom="zoom"
      :plugin="plugin"
      :events="events"
      :center="center"
    >
      <!-- 标记 -->
      <el-amap-marker v-for="(marker, index) in markers" :position="marker" :key="index"></el-amap-marker>
    </el-amap>
  </div>
</template>

<script>
import { AMapManager, lazyAMapApiLoaderInstance } from 'vue-amap'
const amapManager = new AMapManager()
export default {
  name: 'Map',
  props: {
    lnglat: {
      default: () => {
        return {
          lng: '', lat: ''
        }
      },
      type: Object
    }
  },
  data () {
    const self = this
    return {
      address: null,
      searchKey: '',
      amapManager,
      CarPoint: [], // 所有车子定位以及发动状态
      markers: [],
      searchOption: {
        city: '宁波',
        citylimit: true
      },
      saveData: {
        pos: [],
        adname: '',
        name: ''
      },
      center: [120.154686, 30.326259],
      zoom: 11,
      lng: 0,
      lat: 0,
      loaded: false,
      events: {
        init () {
          lazyAMapApiLoaderInstance.load().then(() => {
            self.initSearch()
          })
        },
        // 点击获取地址的数据
        click (e) {
          // console.log(e)
          self.markers = []
          const { lng, lat } = e.lnglat
          self.lng = lng
          self.lat = lat
          self.center = [lng, lat]
          self.markers.push([lng, lat])
          // 这里通过高德 SDK 完成。
          const geocoder = new window.AMap.Geocoder({
            radius: 1000,
            extensions: 'all'
          })
          geocoder.getAddress([lng, lat], function (status, result) {
            if (status === 'complete' && result.info === 'OK') {
              if (result && result.regeocode) {
                // console.log(result);
                self.address = result.regeocode.formattedAddress
                self.searchKey = result.regeocode.formattedAddress
                self.$nextTick()
                const poi = result.regeocode.addressComponent
                const d = {
                  pos: [lng, lat],
                  adname: poi.district,
                  // name: poi.name,
                  address: self.address
                }

                self.$emit('poi', d)
              }
            }
          })
        }
      },
      // 一些工具插件
      plugin: [
        // {
        //   pName: 'Geocoder',
        //   events: {
        //     init (o) {
        //       console.log(o.getAddress())
        //     }
        //   }
        // },
        {
          // 定位
          pName: 'Geolocation',
          events: {
            init (o) {
              // o是高德地图定位插件实例
              o.getCurrentPosition((status, result) => {
                if (result && result.position) {
                  // 设置经度
                  self.lng = self.lnglat.lng || result.position.lng
                  // 设置维度
                  self.lat = self.lnglat.lat || result.position.lat
                  // 设置坐标
                  self.center = [self.lng, self.lat]
                  self.markers.push([self.lng, self.lat])
                  // load
                  self.loaded = true
                  // 页面渲染好后
                  self.$nextTick()
                }
              })
            }
          }
        },
        {
          // 工具栏
          pName: 'ToolBar',
          events: {
            init (instance) {
              // console.log(instance);
            }
          }
        },
        {
          // 鹰眼
          pName: 'OverView',
          events: {
            init (instance) {
              // console.log(instance);
            }
          }
        },
        {
          // 地图类型
          pName: 'MapType',
          defaultType: 0,
          events: {
            init (instance) {
              // console.log(instance);
            }
          }
        },
        {
          // 搜索
          pName: 'PlaceSearch',
          events: {
            init (instance) {
              // console.log(instance)
            }
          }
        }
      ]
    }
  },
  created () {
    this.searchKey = this.lnglat.address
  },
  methods: {
    initSearch () {
      const vm = this
      const map = this.amapManager.getMap()
      window.AMapUI.loadUI(['misc/PoiPicker'], function (PoiPicker) {
        var poiPicker = new PoiPicker({
          input: 'search',
          placeSearchOptions: {
            map: map,
            pageSize: 10
          },
          suggestContainer: 'searchTip',
          searchResultsContainer: 'searchTip'
        })
        vm.poiPicker = poiPicker
        // 监听poi选中信息
        poiPicker.on('poiPicked', function (poiResult) {
          const source = poiResult.source
          const poi = poiResult.item
          if (source !== 'search') {
            poiPicker.searchByKeyword(poi.name)
          } else {
            poiPicker.clearSearchResults()
            vm.markers = []
            const lng = poi.location.lng
            const lat = poi.location.lat
            const address = poi.cityname + poi.adname + poi.name
            vm.center = [lng, lat]
            vm.markers.push([lng, lat])
            vm.lng = lng
            vm.lat = lat
            vm.address = address
            vm.searchKey = address
            const d = {
              pos: [lng, lat],
              adname: poi.adname,
              name: poi.name,
              address:
                poi.pname +
                ' ' +
                poi.cityname +
                ' ' +
                poi.adname +
                ' ' +
                poi.address +
                ' ' +
                poi.name
            }
            // console.log(JSON.stringify(poi, null, 3));
            // vm.$parent.getPos([lng, lat], poi.adname, poi.name);

            vm.$emit('poi', d)
          }
        })
      })
    },
    searchByHand () {
      if (this.searchKey !== '') {
        this.poiPicker.searchByKeyword(this.searchKey)
      }
    }
  }
}
</script>

<style lang="less">
.mapcontainer {
  width: 100%;
  height: 550px;
  /* position: absolute;
  left: 50%;
  top: 50%;
  transform: translate3d(-50%, -50%, 0); */
  border: 1px solid #999;
  margin-top: 40px;
  position: relative;
  .search-box {
    width: 100%;
    border: 1px solid #999;
    margin: 0 auto;
    height: 42px;
    position: absolute;
    top: -50px;
    left: 0;
    z-index: 888;
    display: flex;
    justify-content: space-between;
  }
  .search-box input {
    width: 80%;
    height: 100%;
    border: none;
    outline: none;
    padding: 0 8px;
    box-sizing: border-box;

  }
  .search-box button {
    width: 20%;
    height: 100%;
    border: none;
    background: #1890FF;
    color: #fff;
    outline: none;
  }
  .tip-box {
    width: 100%;
    max-height: 260px;
    position: absolute;
    top: 40px;
    overflow-y: auto;
    background-color: #fff;
  }
}

</style>
