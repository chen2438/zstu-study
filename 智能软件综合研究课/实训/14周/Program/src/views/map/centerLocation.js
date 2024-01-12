let geolocation = null
/**
 * 浏览器定位
 */
export function centerLocation (params) {
  // eslint-disable-next-line no-undef
  if (!geolocation) {
    // eslint-disable-next-line no-undef
    geolocation = new AMap.Geolocation({
      enableHighAccuracy: true, // 是否使用高精度定位，默认:true
      timeout: 10000, // 超过10秒后停止定位，默认：5s
      buttonPosition: 'RB', // 定位按钮的停靠位置
      // eslint-disable-next-line no-undef
      buttonOffset: new AMap.Pixel(10, 20), // 定位按钮与设置的停靠位置的偏移量，默认：Pixel(10, 20)
      zoomToAccuracy: false, // 定位成功后是否自动调整地图视野到定位点
      markerOptions: {
        title: '监控中心所在位置',
        animation: 'AMAP_ANIMATION_DROP'
      }
    })
  }

  // eslint-disable-next-line no-undef
  params.map.addControl(geolocation)
  geolocation.getCurrentPosition()
  if (params.complete && typeof params.complete === 'function') {
    // eslint-disable-next-line no-undef
    AMap.event.addListener(geolocation, 'complete', params.complete)// 定位成功
  }
  if (params.error && typeof params.error === 'function') {
    // eslint-disable-next-line no-undef
    AMap.event.addListener(geolocation, 'error', params.error)// 定位失败
  }
}

// /**
//  * 浏览器定位
//  */
//   // eslint-disable-next-line no-undef
// var geolocation = new AMap.Geolocation({
//     enableHighAccuracy: true, // 是否使用高精度定位，默认:true
//     timeout: 10000, // 超过10秒后停止定位，默认：5s
//     buttonPosition: 'RB', // 定位按钮的停靠位置
//     // eslint-disable-next-line no-undef
//     buttonOffset: new AMap.Pixel(0, 0), // 定位按钮与设置的停靠位置的偏移量，默认：Pixel(10, 20)
//     zoomToAccuracy: false, // 定位成功后是否自动调整地图视野到定位点
//     markerOptions: {
//       title: '监控中心所在位置',
//       animation: 'AMAP_ANIMATION_DROP'
//     }
//   })
// // eslint-disable-next-line no-undef
// this.map.addControl(geolocation)
// geolocation.getCurrentPosition(function (status, result) {
//   // eslint-disable-next-line eqeqeq
//   if (status == 'complete') {
//     // eslint-disable-next-line no-undef
//
//   } else {
//     // eslint-disable-next-line no-undef
//
//   }
// })
