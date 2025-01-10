#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @Time    : 18-11-2 下午7:13
# @Author  : KainHuck
# @Email   : kainhoo2333@gmail.com
# @File    : server.py

import config
from application import Application
from tornado import ioloop, httpserver
if __name__ == '__main__':

    app = Application()
    http_server = httpserver.HTTPServer(app)
    http_server.bind(config.options['port'])
    # asyncio.set_event_loop_policy(asyncio.WindowsSelectorEventLoopPolicy())
    http_server.start(1)


    ioloop.IOLoop.current().start()