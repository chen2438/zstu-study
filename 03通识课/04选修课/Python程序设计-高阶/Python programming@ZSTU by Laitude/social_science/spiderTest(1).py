#import requests
import random
from urllib import request
from lxml import etree
import re
import json
import datetime
import pymysql


# 初始化数据库
db = pymysql.connect(host="47.101.198.252", user="root",\
     password="root", db="spidertest", port=3306)

cur = db.cursor()
sql = 'select zzbds from website1'
cur.execute(sql)     # 执行sql语句
zzResults = cur.fetchall()

my_headers = [
    "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.95 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.153 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:30.0) Gecko/20100101 Firefox/30.0",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.75.14 (KHTML, like Gecko) Version/7.0.3 Safari/537.75.14",
    "Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; Win64; x64; Trident/6.0)",
    'Mozilla/5.0 (Windows; U; Windows NT 5.1; it; rv:1.8.1.11) Gecko/20071127 Firefox/2.0.0.11',
    'Opera/9.25 (Windows NT 5.1; U; en)',
    'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.1.4322; .NET CLR 2.0.50727)',
    'Mozilla/5.0 (compatible; Konqueror/3.5; Linux) KHTML/3.5.5 (like Gecko) (Kubuntu)',
    'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.8.0.12) Gecko/20070731 Ubuntu/dapper-security Firefox/1.5.0.12',
    'Lynx/2.8.5rel.1 libwww-FM/2.14 SSL-MM/1.4.1 GNUTLS/1.2.9',
    "Mozilla/5.0 (X11; Linux i686) AppleWebKit/535.7 (KHTML, like Gecko) Ubuntu/11.04 Chromium/16.0.912.77 Chrome/16.0.912.77 Safari/535.7",
    "Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:10.0) Gecko/20100101 Firefox/10.0 "]

# 设置开始时间和结尾时间，超出则结束
beginTime = datetime.datetime.strptime('2018-03-23 00:00', '%Y-%m-%d %H:%M')
endTime = datetime.datetime.strptime('2019-09-05 00:00', '%Y-%m-%d %H:%M')


# 获取列表
def get_yicai_news_list(key_text):
    # url = 'https://www.yicai.com/api/ajax/getjuhelist?action=news&page=' + str(news_index) + '&pagesize=1'
    url = 'https://www.yicai.com/search?keys=' + key_text
    page = 0
    headers = {'User-Agent': random.choice(my_headers), \
               'content-type': 'application/json; charset=utf-8'}
    data_string = request.urlopen(url).read().decode('utf-8')

    while True:
        print('current url=', url)
        # 模拟发送请求，并返回响应

        url = 'https://www.yicai.com/api/ajax/getSearchResult?page=' + str(page) + '&pagesize=20&keys=' + \
              key_text + '&action=10'
        data_string = request.urlopen(url).read().decode('utf-8')

        # 将这样格式的字符串转化为JSON
        data_json = json.loads(data_string)
        if not data_json:
            return False    # 如果没有数据了,退出
        # 获取每一条新闻的一些数据
        for data in data_json:
            # 获取该新闻的发布时间，超出则跳出
            news_time = datetime.datetime.strptime(data['pubDate'], '%Y-%m-%d %H:%M')
            if news_time > endTime or news_time < beginTime:
                continue    # 如果时间不在范围以内了,不爬取

            # get_page_data('https://www.yicai.com' + data['url'])   # 根据其中的URL，再次发送请求
            print('https://www.yicai.com' + data['url'])
        page += 1


def get_page_data(url):
    html=request.urlopen(url).read().decode('utf-8')
    html=etree.HTML(html)
    # 获取正文数据
    dataArray = html.xpath("//div[@class='m-txt']/p/text()")
    # 获取标题数据并打印
    title = ""
    if html.xpath("//div[@class='intro']/text()"):
        title = str(html.xpath("//div[@class='intro']/text()")[0])
    print(title)
    # 拼接成一个长字符串
    s = arrayToString(title,dataArray)
    # 遍历数据库的分类
    for id in range(0,351):
        # 获取该分类可匹配的正则表达式
        mat = get_reg(id)
        # 去匹配，若满足，计数值加一并保存
        ret = re.search(r"" + mat, s)
        if ret:
            set_count(i+1, 1)


def arrayToString(title, dataArray):
    s = title
    for data in dataArray :
        s = s + data
    return s


def get_reg(id):
    return zzResults[id][0]


def set_count(id, n):
    sql = 'update website1 set count = count +' + str(n) + 'where id=' + str(id)
    cur.execute(sql)     # 执行sql语句
    db.commit()


if __name__ == '__main__':
    get_yicai_news_list('%E4%B8%AD%E7%BE%8E%E8%B4%B8%E6%98%93%E6%91%A9%E6%93%A6')
