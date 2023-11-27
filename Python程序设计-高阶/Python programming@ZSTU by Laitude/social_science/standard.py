import requests  # 关键库，用于发送Http请求    # pip install requests
from lxml import etree # xml解析包，ElementTree  # pip install lxml
import time
import random
import re
import csv

class Spider:
    def __init__(self, name):
        self.name = name
        self.url = 'https://openstd.samr.gov.cn/bzgk/gb/std_list?r=0.40987171406906286&page=1&pageSize=10&p.p1=0&p.p2=' + name + '&p.p90=circulation_date&p.p91=desc'
        print(self.url)
        self.headers = [
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
            "Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:10.0) Gecko/20100101 Firefox/10.0 "
        ]

    def get_each_link(self):
        '''获得首页链接，返回列表'''
        index = 1 #翻页
        link_list = []  #储存每一个链接的列表
        while True:
            try:
                headers = {
                    "User-Agent" : random.choice(self.headers)    # 随机选择请求头，模拟不同的浏览器
                }
                r = requests.get(self.url, headers=headers)    # 请求数据,返回给Response对象
                r.encoding = r.apparent_encoding    # 设置编码
                #print(r.status_code)
                html = r.text
                selector = etree.HTML(html)    #将网页源码转换为 XPath 可以解析的格式
                Ids = selector.xpath('//tr/td[@style="text-align: left;"]/a/@onclick')  #选择结点
                print(Ids)

                #判断是否获取结束
                if len(Ids) == 0:
                    break

                for each_id in Ids:
                    each_id = each_id.replace('showInfo(\'', '').replace('\');', '')
                    # link = 'http://www.gb688.cn/bzgk/gb/newGbInfo?hcno=' + each_id
                    link = 'https://openstd.samr.gov.cn/bzgk/gb/newGbInfo?hcno=' + each_id
                    
                    print(link)
                    link_list.append(link)
                index += 1
                if index > 1:  # 只请求1页
                    break
                # self.url = 'http://www.gb688.cn/bzgk/gb/std_list?r=0.40987171406906286&page=' + str(index) + '&pageSize=10&p.p1=0&p.p2=' + self.name + '&p.p90=circulation_date&p.p91=desc'
                self.url = 'https://openstd.samr.gov.cn/bzgk/gb/std_list?p.p1=0&p.p2=' + self.name + '&p.p90=circulation_date&p.p91=desc'
                print(self.url)
                time.sleep(random.random()+random.randint(0,1))
            except:
                break
        return link_list

    def get_detial_from_linkList(self, link_list):
        '''从列表的链接下载文件内容'''
        path = self.name + '.csv'
        i = 0 #序号
        #写入表头
        info = ['序号','标准编号','标准名称','英文名称','状态','中国标准分类号（CCS）','国际标准分类号（ICS）','发布日期','实施日期','主管部门','归口单位','发布单位','备注']
        with open(path, 'a') as f:
            csv_writer = csv.writer(f)
            csv_writer.writerow(info)
        for link in link_list:
            try:
                headers = {
                    "User-Agent" : random.choice(self.headers)
                }
                r = requests.get(link, headers=headers)
                r.encoding = r.apparent_encoding
                html = r.text
                selector = etree.HTML(html)
                print(selector.xpath('//td/h1/text()'))
                number = selector.xpath('//td/h1/text()')[0].strip().replace('标准号：','')
                name = selector.xpath('//td/b/text()')[0].strip()
                E_name = re.findall('<td>英文标准名称：(.+)</td>', html)[0] #这里使用正则表达式，因为xpath莫名其妙使用不了
                status = selector.xpath('//td[@align="left"]/span[@class]/text()')[0].strip()
                ccs = selector.xpath('//div[@class="col-xs-12 col-md-4 content"]/text()')[0].strip() #中国标准分类号（CCS）
                ics = selector.xpath('//div[@class="col-xs-12 col-md-4 content"]/text()')[1].strip() #国际标准分类号（ICS）
                release_date = selector.xpath('//div[@class="col-xs-12 col-md-4 content"]/text()')[2].strip() #发布日期
                implement_date = selector.xpath('//div[@class="col-xs-12 col-md-4 content"]/text()')[3].strip() #实施日期
                department = selector.xpath('//div[@class="col-xs-12 col-md-4 content"]/text()')[4].strip() #主管部门
                unit = selector.xpath('//div[@class="col-xs-12 col-md-4 content"]/text()')[5].strip() #归口单位
                f_unit = selector.xpath('//div[@class="col-xs-12 col-md-10 content"]/text()')[0].strip() #发布单位
                other = selector.xpath('//div[@class="col-xs-12 col-md-10 content"]/text()')[1].strip() #备注

                i += 1
                info = []
                info.append(i)
                info.append(number)
                info.append(name)
                info.append(E_name)
                info.append(status)
                info.append(ccs)
                info.append(ics)
                info.append(release_date)
                info.append(implement_date)
                info.append(department)
                info.append(unit)
                info.append(f_unit)
                info.append(other)

                #用None替换不存在的项目
                for j in range(len(info)):
                    if len(info) == 0:
                        info = 'None'

                with open(path, 'a') as f:
                    csv_writer = csv.writer(f)
                    csv_writer.writerow(info)

            except Exception as e:
                print('Downloa Error:', link, e)

def main():

    print('开始下载有关‘安全’的国家标准')
    scrapy = Spider('安全')

    print('正在获取链接...')
    link_list = scrapy.get_each_link()
    print('获取完毕共%d个' % len(link_list))
    print('正在下载...')

    #link_list = ['http://www.gb688.cn/bzgk/gb/newGbInfo?hcno=E6CD13ACF8E3B3BEFAA16852499676D0']
    scrapy.get_detial_from_linkList(link_list)

    print('有关‘安全’的国家标准下载完毕')

if __name__ == '__main__':
    main()