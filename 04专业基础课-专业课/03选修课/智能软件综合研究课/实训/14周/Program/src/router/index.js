import Vue from 'vue'
import VueRouter from 'vue-router'

Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    redirect: '/home'
  },
  {
    path: '/home',
    name: 'home',
    component: () => import('../views/home.vue')
  },
  {
    path: '/register',
    name: 'Register',
    component: () => import('../views/Register.vue')
  },
  {
    path: '/login',
    name: 'Login',
    component: () => import('../views/Login.vue')
  },
  {
    path: '/Adminmain',
    name: 'AdminMain',
    component: () => import('../views/Admin/Main.vue'),
    children: [
      {
        path: '/admindriver',
        name: 'AdminDriver',
        component: () => import(/* webpackChunkName: "about" */ '../views/Admin/Information/Driver.vue')
      }, {
        path: '/admincar',
        name: 'AdminCar',
        component: () => import(/* webpackChunkName: "about" */ '../views/Admin/Information/Car.vue')
      }, {
        path: '/adminplace',
        name: 'AdminPlace',
        component: () => import(/* webpackChunkName: "about" */ '../views/Admin/Information/Place.vue')
      }, {
        path: '/admindata',
        name: 'AdminData',
        component: () => import(/* webpackChunkName: "about" */ '../views/Admin/Controller/Data.vue')
      }, {
        path: '/adminrecord',
        name: 'AdminRecord',
        component: () => import(/* webpackChunkName: "about" */ '../views/Admin/Controller/Record.vue')
      }, {
        path: '/adminhost',
        name: 'AdminHost',
        component: () => import(/* webpackChunkName: "about" */ '../views/Admin/Host.vue')
      },
      // {
      //   path: '/admin-video-surveillance',
      //   name: 'AdminVideoSurveillance',
      //   component: () => import(/* webpackChunkName: "about" */ '../views/Admin/Controller/VideoSurveillance.vue')
      // }
    ]
  },
  {
    path: '/Usermain',
    name: 'UserMain',
    component: () => import('../views/User/Main.vue'),
    children: [
      {
        path: '/userintro',
        name: 'UserIntro',
        component: () => import(/* webpackChunkName: "about" */ '../views/User/Information/Introduce.vue')
      }, {
        path: '/userinfo',
        name: 'UserInfo',
        component: () => import(/* webpackChunkName: "about" */ '../views/User/Information/UserInfo.vue')
      }, {
        path: '/userplace',
        name: 'UserPlace',
        component: () => import(/* webpackChunkName: "about" */ '../views/User/Information/Place.vue')
      }, {
        path: '/userdata',
        name: 'UserData',
        component: () => import(/* webpackChunkName: "about" */ '../views/User/Controller/Data.vue')
      }, {
        path: '/userhost',
        name: 'UserHost',
        component: () => import(/* webpackChunkName: "about" */ '../views/User/Host.vue')
      }, {
        path: '/user-video-surveillance',
        name: 'UserVideoSurveillance',
        component: () => import(/* webpackChunkName: "about" */ '../views/User/Controller/VideoSurveillance.vue')
      }
    ]
  }
]

const router = new VueRouter({
  routes
})

export default router
