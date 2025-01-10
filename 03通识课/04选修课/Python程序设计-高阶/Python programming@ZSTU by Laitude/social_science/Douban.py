#-*-coding:utf-8-*-
import urllib.request
from bs4 import BeautifulSoup
import re
import json
import pymysql
import pandas as pd


# 从数据库获取电影/电视名，演员表两列，写入男主演：male_lead,女主演：female_lead
def getActorsFromDataBase():
    database_name = 'huashu'        #数据库名
    config = dict(host='localhost', user='root', password='123456',db=database_name,
                  cursorclass=pymysql.cursors.DictCursor
                  )
    conn = pymysql.Connect(**config)
    conn.autocommit(1)
    cursor = conn.cursor()
    sql_query = 'select FILM_NAME,ACTOR from films limit 1;'
    df = pd.read_sql(sql_query,con=conn)    #获取FILM_NAME,ACTOR两列内容
    print(df)
    return df



# kd为关键字,关键字为“豆瓣 ”+电影名称，如“豆瓣 康熙王朝”
def getFullUrl(kd):
    # 将关键字进行url编码，传递到urlencode（）中的字符类型为字典
    wd = {"wd": kd}
    wd = urllib.parse.urlencode(wd)
    # 构造完整的url
    fullurl = url + "?" + wd
    return fullurl

#向服务器发送请求，获取返回内容content
def getContent(fullurl,headers):
    # 构造服务器请求信息
    request = urllib.request.Request(fullurl, headers=headers)
    # 向服务器发送请求
    response = urllib.request.urlopen(request)
    # 获取百度搜索内容中的豆瓣电影
    content = response.read()       #网页源代码
    return content

# 解析百度搜索页
def parseBaidu(content):
    soup=BeautifulSoup(content,"html.parser")
    div = soup.find("div",attrs={'data-tools':re.compile('.*豆瓣电影.*')})
    data = div['data-tools']        #该data是str,{"title":"康熙王朝 (豆瓣) _豆瓣电影","url":"http://www.baidu.com/link?url=d8lhfLoCqn4IXrZc47Hfum6n0LuloNb96dPKZ4bMrLueqTjh72y5zQgj26HtH1TRdxT4EBVsytN1zWQ8kfDdqK"}
    data = json.loads(data)     #将data转换成字典
    return data

#从演员详情页获取演员的性别，返回：男，女，null
# actor_url是parseBaidi()中返回的data的url，需要和base_url拼接
def getSexFromActor(base_url,actor_url,headers):
    content = getContent(base_url+actor_url,headers)
    soup = BeautifulSoup(content, "html.parser")
    sex = soup.find("div", id='headline').find('li')
    if str(sex).find("女") != -1:
        return '女';
    elif  str(sex).find("男") != -1:
        return '男';
    else:
        return 'null'




#进入豆瓣电影，获取演员信息，演员下面格式中
# film_actors:是数据库中的演员表 ， list-actors：是豆瓣电影上的演员表
'''
<span class="actors">
    <span class="attrs">
        <a href="/celebrity/1274429/" rel="v:starring">斯琴高娃</a>
        <a href="/celebrity/1045565/" rel="v:starring">陈道明</a>
        ....
    </span>
</span>
'''
def parseDouban(data,headers,film_actors,row):
    print(data['title'])
    content = getContent(data['url'],headers)
    soup=BeautifulSoup(content,"html.parser")
    span_actor = soup.find("span", attrs={'class':'actor'})
    span_attrs = span_actor.find("span",attrs={'class':'attrs'})
    resultSet_actors = span_attrs.find_all('a')         # resultSet_actors :[<a href="/celebrity/1059980/" rel="v:starring">安在旭</a>, <a href="/celebrity/1001074/" rel="v:starring">董洁</a>]

    for actor in resultSet_actors:  # actor : <a href="/celebrity/1059980/" rel="v:starring">安在旭</a>
        if actor.string in film_actors:
            sex = getSexFromActor(base_url,actor['href'],headers)
            if sex == '男':
                if row['MALE_LEAD']:
                    row['MALE_LEAD'] = [row['MALE_LEAD'],actor.string]
                else:
                    row['MALE_LEAD'] = actor.string
            elif sex == '女':
                if  row['FEMALE_LEAD']:
                    row['FEMALE_LEAD'] =[row['FEMALE_LEAD'],actor.string]
                else:
                    row['FEMALE_LEAD'] = actor.string
    return row


#针对一行进行男女演员分类
def classfyActors(row):
    film_name = row['FILM_NAME']
    film_actors = row['ACTOR'].split(',')      # row['ACTOR']返回类型为str,转换成列表返回

    if film_actors:
        kd = '豆瓣 ' + film_name  # 搜索关键字
        full_url = getFullUrl(kd)  # 返回进行请求的百度搜索kd关键字的url
        content = getContent(full_url, headers)  # 返回返回请求返回的百度搜索页内容
        data = parseBaidu(content)  # 解析百度搜索页，返 回字典data,
        # row = parseDouban(data, headers, film_actors,row)  # 解析豆瓣电影页
        # print('--------row------\n',row)
        return parseDouban(data, headers, film_actors,row)

if __name__ == '__main__':
    # 定义User-Agent，要爬取的url，以及要查询的关键字
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.181 Safari/537.36"}
    url = "http://www.baidu.com/s"
    base_url = 'https://movie.douban.com'

    df = getActorsFromDataBase()
    df['MALE_LEAD'] = None
    df['FEMALE_LEAD'] = None
    df= df.apply(classfyActors,axis=1)

    df.to_csv('F:\Data\out\out.csv')

    #
    # kd = '豆瓣 康熙王朝'
    #full_url = getFullUrl(kd)       #返回进行请求的百度搜索kd关键字的url
    # content = getContent(full_url,headers)  #返回返回请求返回的百度搜索页内容
    # data = parseBaidu(content)             #解析百度搜索页，返 回字典data,
    # parseDouban(data,headers)                       #解析豆瓣电影页