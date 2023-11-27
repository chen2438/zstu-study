from selenium import webdriver
import pymysql
import datetime
from dateutil.parser import parse
import re

def str2date(string):
    # str->date
    return parse(string)

def date_compare(x, y):
    # x>=y:true; x<y:false
    return x.__ge__(y)

def get_keywords():
    sql = "select id, keywords, regexps, count from keywords"
    cur.execute(sql)     # 执行sql语句
    return cur.fetchall()

def get_keywords2():
    sql = "select id, keyword, regexps, count from keyword where priority = 4"
    cur.execute(sql)     # 执行sql语句
    return cur.fetchall()

def save(Id1, Id2, url, text, newsTime):
    """
    :param Id1: 第一轮关键词
    :param Id2: 第二轮关键词
    :param url: 新闻链接
    :param text: 新闻内容
    :param newsTime: 新闻时间
    :return:
    """
    try:
        count_sql = 'update keywords set count = count + 1 where id=' + str(Id1)
        cur.execute(count_sql)     # 执行sql语句
        if Id2 != -1:
            count_sql = 'update keyword set count = count + 1 where id=' + str(Id2)
            cur.execute(count_sql)  # 执行sql语句
        save_sql = "insert into page_text(keywords_id1, keywords_id2, url, page_text, date) values(%s,%s,%s,%s,%s)"
        cur.executemany(save_sql,[[Id1, Id2, url, text, newsTime]])# 执行sql语句
        con.commit()
    except Exception as e:
        # 错误回滚
        print(e)
        con.rollback()

def search_keywords_in_text(url, newtime, text):
    keywords = get_keywords()
    # 第一轮爬取
    for i in range(len(keywords)):
        Id1 = keywords[i][0]
        regexp = keywords[i][2]
        ret = re.search(r"" + regexp, text)
        if ret:
            save(Id1, -1, url, text, newtime)
            # 第二轮爬取
            keywords2 = get_keywords2()
            for i in range(len(keywords2)):
                Id2 = keywords2[i][0]
                regexp = keywords2[i][2]
                res = re.search(r"" + regexp, text)
                if res:
                    save(Id1, Id2, url, text, newtime)

url_list = [
    "https://www.19lou.com/r/1/zzd.html",
    "https://taizhou.19lou.com/r/37/tzxwzzd.html",
    "https://quzhou.19lou.com/r/71/rd.html",
    "https://jiaxing.19lou.com/r/58/jrrd.html"
]
beginTime = datetime.datetime.strptime('2016-12-01 00:00', '%Y-%m-%d %H:%M')
endTime = datetime.datetime.strptime('2019-8-31 00:00', '%Y-%m-%d %H:%M')

con = pymysql.connect(host='10.11.35.168', user='root', passwd='Abcd$9876', db='sjk_spider_19lou')
cur = con.cursor()

browser = webdriver.Chrome() # 创建实例

for item_url in url_list:
    count = 0
    flag = 1
    link_list = []
    search_url = item_url

    browser.get(search_url)
    while flag != 0:
        # print(browser.current_url)
        div_list = []
        try:
            # .find_element_by_xpath('//section[@id="main"]//div[@id="J_itemWrap"]')
            # div_list = browser.find_elements_by_css_selector(".J_item.J_toUrl.item")
            div_list = browser.find_elements_by_css_selector(".cont.link2")
            count += len(div_list)
        except:
            print("error 1001: failed to get content_left!")

        next_page_url = ""
        try:
            # '//section[@id="main"]//div[@id="J_pageWrap"]//a[@class="page-next"]'
            next_page_url = browser.find_element_by_xpath('//a[@class="page-next"]').get_attribute("href")
        except:
            print("final!", browser.current_url)

        # 将信息插入到数据库
        if len(div_list) > 0:
            for item in div_list:
                link = ""
                try:
                    link = item.find_element_by_tag_name("a").get_attribute("href")
                except:
                    print("error 1002: failed to get link")

                if link != "":
                    link_list.append(link)
                else:
                    count -= 1

        if next_page_url == "":
            flag = 0
        else:
            browser.get(next_page_url)

    for item in link_list:
        new_link = item
        new_time = ""
        text = ""

        browser.get(new_link)
        try:
            new_time = browser.find_element_by_xpath(
                '//div[@class="clearall floor first"]//div[@class="cont-hd clearall"]//li[@title]').get_attribute(
                "title")[3:]
            new_time = str2date(new_time)
        except:
            print("error 2001: failed to get time")

        try:
            text_list = browser.find_elements_by_xpath('//div[@class="clearall floor first"]//div[@align="left"]')
            for item in text_list:
                text += item.get_attribute('textContent').strip().replace("\r\n", "").replace(" ", "")
        except:
            print("error 2002: failed to get text")

        if new_time != "" and text != "":
            if date_compare(new_time, beginTime) and date_compare(endTime, new_time):
                # print(new_time, new_link, text)
                print(new_time, new_link)
                search_keywords_in_text(new_link, new_time, text)
        else:
            count -= 1
            print("error 2003: some special code", new_link)
    print(count)

browser.quit()  # 退出浏览器