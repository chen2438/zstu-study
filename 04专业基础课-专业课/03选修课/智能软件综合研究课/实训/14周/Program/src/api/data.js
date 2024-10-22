// eslint-disable-next-line no-unused-vars
import request from '../utils/request'

/**
 * 查找实施疲劳记录
 * @returns {AxiosPromise}
 */
export const findUserTired = (current, size) => {
  return request({
    url: '/Head/findUserTired',
    method: 'get',
    params: {
      current,
      size
    }
  })
}
export const updateDiatance = (curlocat_x,curlocat_y) => {
  return request({
    url: '/Userhost/updatedist',
    method: 'get',
    params:{
      curlocat_x,
      curlocat_y
    }
  })
}
export const updateVideo = (status) => {
  return request({
    url: '/User/updatevideo',
    method: 'get',
    params:{
      status
    }
  })
}
export const videoGetUserList = () => {
  return request({
    url: 'url',
    method: 'post',
  })
}
