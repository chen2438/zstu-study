import request from '../utils/request'

/**
 * 账号登录
 * @param Name
 * @param Pwd
 * @returns {AxiosPromise}
 */
export const accountLogin = (Name, Pwd) => {
  return request({
    url: '/Account/AccountLogin',
    method: 'post',
    headers: {
      'Content-Type': 'application/json', // 明确设置 Content-Type
    },
    data: { // 使用 data 而不是 param 发送请求体
      Name,
      Pwd
    }
  })
}

export const register = (admin, password) => {
  return request({
    url: '/Account/AccountRegister',
    method: 'post',
    headers: {
      'Content-Type': 'application/json', // 明确设置 Content-Type
    },
    data: {
      admin,
      password
    }
  })
}
