import Vue from 'vue'
import Vuex from 'vuex'

Vue.use(Vuex)
export default new Vuex.Store({
  state: {
    data: {
    },
    token: '',
    sessionid: null
  },
  mutations: {
    getToken: (state, token) => {
      state.token = token
    },
    getData: (state, data) => {
      state.data = data
    },
    getId:(state, sessionid) => {
      state.sessionid = sessionid
    }
  },
  actions: {
  },
  modules: {

  }
})
