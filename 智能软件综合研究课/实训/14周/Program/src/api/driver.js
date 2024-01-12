// eslint-disable-next-line no-unused-vars
import request from '../utils/request'

/**
 * 分页显示所有用户司机信息
 * @param current
 * @param size
 * @returns {AxiosPromise}
 */
export const findUserList = (current, size) => {
  return request({
    url: '/User/common/findUserList',
    method: 'get',
    params: {
      current,//第几页
      size//每页大小
    }
  })
}

/**
 * 获取对应UserId的用户司机信息
 * @param sortId
 * @returns {AxiosPromise}
 */
export const getUserById = (userId) => {
  return request({
    url: '/User/common/getUserById',
    method: 'get',
    params: {
      userId
    }
  })
}

/**
 * 管理员修改司机信息
 * @param userId
 * @param userCity
 * @param userAddress
 * @returns {AxiosPromise}
 */
export const editUser = (userId, userScore, reason) => {
  return request({
    url: '/User/common/editUser',
    method: 'get',
    params: {
      userId,
      userScore,
      reason
    }
  })
}

/**
 * 删除用户信息
 * @param userId
 * @returns {AxiosPromise}
 */
export const deleteUser = (userId) => {
  return request({
    url: '/User/common/deleteUser',
    method: 'get',
    params: {
      userId
    }
  })
}

/**
 * 查找用户 车辆 正在驾驶 尚未使用 各种信息
 * @returns {AxiosPromise}
 */
export const findCarsAndUser = () => {
  return request({
    url: '/User/common/findCarsAndUser',
    method: 'get'
  })
}

/**
 * 点击按钮对当前疲劳的用户进行警告
 * @returns {AxiosPromise}
 */
export const warningAllTiredUser = () => {
  return request({
    url: '/User/common/warningAllTiredUser',
    method: 'POST'
  })
}

/**
 * 点击按钮对指定疲劳的用户进行警告
 * @returns {AxiosPromise}
 */
export const warningtiredUserById = (userId) => {
  return request({
    url: '/User/common/warningtiredUserById',
    method: 'POST',
    params: {
      userId
    }
  })
}
/*
* 个人中心信息展示
* */
export const userInfo = (userId) => {
  return request({
    url: '/User/userInfo',
    method: 'GET',
    params:{
      userId
    }
  })
}

/*
* 司机修改个人信息
* */
export const updateUser = (userId,userAddress,userPassword,userTime,userPhone) => {
  return request({
    url: '/User/updateuser',
    method: 'GET',
    params:{
      userId,
      userAddress,
      userPassword,
      userTime,
      userPhone
    }
  })
}
