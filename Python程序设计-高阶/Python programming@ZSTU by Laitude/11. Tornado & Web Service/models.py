#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @Time    : 18-11-4 下午2:14
# @Author  : KainHuck
# @Email   : kainhoo2333@gmail.com
# @File    : models.py

from ORM.orm import ORM

class Users(ORM):
    def __init__(self, username, password):
        self.username = username
        self.password = password






