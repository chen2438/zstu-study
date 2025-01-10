#!/usr/bin/python3
# -*- coding: utf-8 -*-
# @Time    : 18-11-4 下午2:16
# @Author  : KainHuck
# @Email   : kainhoo2333@gmail.com
# @File    : orm.py

from .kainMysql import KainMysql

class ORM():
    def save(self):
        tableName = self.__class__.__name__.lower()
        fieldStr = valueStr = "("
        for field in self.__dict__:
            fieldStr += (field + ',')
            if isinstance(self.__dict__[field], str):
                valueStr += ("'" + self.__dict__[field] + "',")
            else:
                valueStr += (str(self.__dict__[field]) + ",")
        fieldStr = fieldStr[:len(fieldStr)-1] + ")"
        valueStr = valueStr[:len(valueStr)-1] + ")"
        sql = "insert into " + tableName + " " + fieldStr + " values " + valueStr
        tempMysql = KainMysql()
        tempMysql.insert(sql)

    def delete(self):
        # delete from users where user='hello' and pass='sad'
        #               $          $        $
        tableName = self.__class__.__name__.lower()
        fieldStr = ''
        for field in self.__dict__:
            fieldStr += (field + '=')
            if isinstance(self.__dict__[field], str):
                fieldStr += "'"+self.__dict__[field]+"'"
            else:
                fieldStr += str(self.__dict__[field])
            fieldStr += ' and '

        sql = 'delete from ' + tableName + ' where ' + fieldStr[:len(fieldStr)-4]
        print(sql)
        tempMysql = KainMysql()
        tempMysql.delete(sql)

    def update(self):
        pass

    @classmethod
    def all(cls):
        # "select * from users"
        tableName = cls.__name__.lower()
        sql = "select * from " + tableName
        tempMysql = KainMysql()
        # print(sql)
        return tempMysql.get_all_obj(sql,tableName)

    def filter(self):
        pass






