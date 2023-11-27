#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @Time    : 18-11-4 下午12:25
# @Author  : KainHuck
# @Email   : kainhoo2333@gmail.com
# @File    : kainMysql.py
# @Software: PyCharm

import pymysql
import config

class KainMysql():
    def __init__(self):
        self.host = config.mysql['host']
        self.user = config.mysql['user']
        self.passwd = config.mysql['passwd']
        self.dbName = config.mysql['dbName']

    def connect(self):
        self.db = pymysql.connect(self.host,self.user,self.passwd,self.dbName)
        self.cursor = self.db.cursor()

    def close(self):
        self.cursor.close()
        self.db.close()

    def get_one(self, sql):
        res = None
        try:
            self.connect()
            self.cursor.execute(sql)
            res = self.cursor.fetchone()
            self.close()
        except:
            print('查询失败')
        return res

    def get_all(self, sql):
        res = ()
        try:
            self.connect()
            self.cursor.execute(sql)
            res = self.cursor.fetchall()
            self.close()
        except:
            print('查询失败')
        return res

    def get_all_obj(self, sql, tableName, *args):
        resList = []
        fieldsList = []
        if len(args) > 0:
            for item in args:
                fieldsList.append(item)
        else:
            fieldsSql = "SELECT COLUMN_NAME FROM \
                        information_schema.COLUMNS \
                        WHERE TABLE_NAME = '%s' AND table_schema = '%s'" % (
                tableName, self.dbName
            )
            fields = self.get_all(fieldsSql)
            for item in fields:
                fieldsList.append(item[0])

        # 执行查询数据sql
        res = self.get_all(sql)
        for item in res:
            obj = {}
            count = 0
            for x in item:
                obj[fieldsList[count]] = x
                count += 1
            resList.append(obj)
        return resList



    def insert(self, sql):
        return self.__edit(sql)
    def update(self, sql):
        return self.__edit(sql)
    def delete(self, sql):
        return self.__edit(sql)

    def __edit(self, sql):
        count = 0
        try:
            self.connect()
            count = self.cursor.execute(sql)
            self.db.commit()
            self.close()
        except:
            print("语句提交失败")
            self.db.rollback()
        return count




