#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @Time    : 18-11-2 下午7:32
# @Author  : KainHuck
# @Email   : kainhoo2333@gmail.com
# @File    : application.py

import os
import tornado.web
import config
from views import index


class Application(tornado.web.Application):
    def __init__(self):
        handlers = [
            # (r'/', index.MainPageHandler),



            # 服务器传参数
            (r'/kain', index.KainHandler, {'item1': 'kain', 'item2': 'huck'}),
            # 反向解析
            tornado.web.url(r'/huck', index.HuckHandler, {'item3': 'kain', 'item4': 'huck'}, name='huck'),

            # 匹配URL中的特定部分
            (r'/kainhuck/(\w+)/(\w+)/(\w+)', index.KainHuckHandler),
            # 第二种写法,取名字,使用较少
            # (r'/kainhuck/(?P<h1>\w+)/(?P<h3>\w+)/(?P<h2>\w+)', index.KainHuckHandler),

            # 获取get方法传递的参数
            (r'/getarg', index.GetArgHandler),

            # post
            (r'/postfile', index.PostFileHandler),

            # request
            (r'/zhuyin', index.ZhuyinHandler),

            # json
            (r'/json1', index.Json1Handler),
            (r'/json2', index.Json2Handler),

            # 上传文件
            (r'/upfile', index.UpFileHandler),

            # header
            (r'/header', index.HeaderHandler),

            # 状态码
            (r'/status', index.StatusCodeHandlers),

            # 重定向
            (r'/index', index.RedirectHandler),

            # 错误处理
            (r'/error', index.ErrorHandler),

            # 借口测试
            (r'/jktest', index.IndexHandler),

            # 参数,函数传递,转义测试
            (r'/funtran', index.FunTranHandler),

            # static
            (r'/static', index.StaticHandler),

            # 继承
            (r'/inherit', index.InheritHandler),

            # 数据库
            (r'/users', index.UsersHandler),

            # 展示图片
            (r'/img', index.ImgHandler),

            # cookie
            (r'/cookie', index.CookieHandler),

            # cookie计数,记录浏览器访问次数
            (r'/cookienum', index.CookieNumHandler),
            (r'/postcookie', index.PostCookieHandler),

            # 用户验证
            (r'/login', index.LoginHandler),
            (r'/home', index.HomeHandler),

            # 回调函数异步
            (r'/student', index.StudentHandler),

            # 协程异步
            (r'/teacher', index.TeacherHandler),
            (r'/teacherplus', index.TeacherPlusHandler),

            # StaticFileHandler,注意要放在所有路由的最下面
            (r'/(.*)$', index.StaticFileHandler, {"path": os.path.join(config.BASE_DIRS,'static/html'), \
            "default_filename": "index.html"}),

            # # 404界面
            # (r'/.*', index.NotFoundHandler),

        ]
        super(Application,self).__init__(handlers,**config.settings)
        # self.db = KainMysql(config.mysql['host'], config.mysql['user'], config.mysql['passwd'], config.mysql['dbName'])
        
        print('Tornado backend server starting....')
        print('listening on port ', config.options['port'])