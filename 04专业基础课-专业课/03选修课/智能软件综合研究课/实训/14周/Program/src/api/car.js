// eslint-disable-next-line no-unused-vars
import request from '../utils/request'

/**
 * 查询车子对应的城市和数量
 * @returns {AxiosPromise}
 */
export const findCarCityAndCount = () => {
  return request({
    url: '/Car/findCarCityAndCount',
    method: 'get'
  })
}

/**
 * 查询车辆
 * @param current
 * @param size
 * @param city
 * @param plate
 * @param style
 * @returns {AxiosPromise}
 */
export const queryCarList = (current, size, city, plate, style) => {
  return request({
    url: '/Car/queryCarList',
    method: 'get',
    params: {
      current,
      size,
      carTude: city,//城市
      carPlates: plate,//车牌
      carStyle: style//车型
    }
  })
}

/**
 * 查询所有未启动车辆的信息
 * @returns {AxiosPromise}
 */
export const findStoppedCars = () => {
  return request({
    url: '/Car/findStoppedCars',
    method: 'get',
    params: {
    }
  })
}

/**
 * 查询所有正在使用车辆的信息
 * @returns {AxiosPromise}
 */
export const findStartedCars = () => {
  return request({
    url: '/Car/findStartedCars',
    method: 'get',
    params: {
    }
  })
}
