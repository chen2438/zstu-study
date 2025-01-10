import selenium
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
import time
import pymysql
import re
import demo_data

chrome_path = r'C:\Users\latitude\AppData\Local\Google\Chrome\Application\chrome.exe'
# key_text = '%E4%B8%AD%E7%BE%8E%E8%B4%B8%E6%98%93%E6%91%A9%E6%93%A6'
key_text = '中美贸易战'


url = 'http://3g.baidu.com/sf/vsearch?pd=realtime_ugc&word=%E6%9C%80%E5%A4%9A%E8%B7%91%E4%B8%80%E6%AC%A1&tn=vsearch&sa=vs_tab&lid=8320208636551962084&ms=1&atn=list'
browser = webdriver.Chrome()
browser.get(url)
web_element = browser.find_element_by_class_name('item-nickname')
print(web_element.text)
browser.quit()
