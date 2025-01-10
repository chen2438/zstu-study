import selenium
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
import time
# import pymysql
import re
import demo_data

chrome_path = r'C:\Users\latitude\AppData\Local\Google\Chrome\Application\chrome.exe'
# key_text = '%E4%B8%AD%E7%BE%8E%E8%B4%B8%E6%98%93%E6%91%A9%E6%93%A6'
key_text = '旧金山'


def get_yicai_news_list(key_text):
	url = 'https://www.yicai.com/search?keys=' + key_text
	print(url)
	browser.get(url)
	# web_element = browser.find_element_by_id('searchlist')
	old_elements = []
	news_list = []
	# web_elements = browser.find_elements_by_class_name('f-db')
	web_elements = browser.find_elements(By.CLASS_NAME, 'f-db')
	# button = browser.find_element_by_class_name('u-btn')	    # 点击加载更多的按钮
	button = browser.find_element(By.CLASS_NAME, 'u-btn')	    # 点击加载更多的按钮
	while len(old_elements) < len(web_elements):        # 运行直到没有新的新闻加载
		for element in web_elements:
			if element not in old_elements:
				link = element.get_attribute('href')
				print(link)
				news_list.append(link)
			# WebDriverWait(browser, 3).until(EC.element_to_be_clickable((By.XPATH, "//*[@id='u1']/a[8]"))).click()
		old_elements = web_elements
		js = 'window.scrollTo(0,document.body.scrollHeight)'
		browser.execute_script(js)
		time.sleep(2)
		button.click()
		time.sleep(3)
		# web_elements = browser.find_elements_by_class_name('f-db')
		web_elements = browser.find_elements(By.CLASS_NAME, 'f-db')

	return news_list


def get_page_text(url):
	browser.get(url)
	try:
		# text = browser.find_element_by_class_name('m-txt')
		text = browser.find_element(By.CLASS_NAME, 'm-txt')
	except selenium.common.exceptions.NoSuchElementException:
		return

	if text:
		# date = browser.find_element_by_tag_name('em').text
		date = browser.find_element(By.TAG_NAME, 'em').text
		text = text.text
		for i in range(len(reg_rows)):
			r = re.search(reg_rows[i][2], text)
			if r:
				if len(text) > 20000:
					start, end = int(r.span()[0]), int(r.span()[1])
					text = text[start:end+1]
				save_to_db(reg_rows[i][0], url, text, date)


def save_to_db(key_id, url, text, date):
	sql = "insert page_text(key_id,url,page_text,date) values(" + str(key_id) + ",'" + url + "','" \
		+ text + "','" + date + "')"
	cur.execute(sql)
	db.commit()


# db = pymysql.connect(host='47.101.198.252', user='root', password='root', db='spidertest', port=3306)
# cur = db.cursor()
sql = "select * from website1 where name like '%" + key_text + "%'"
# cur.execute(sql)     # 执行sql语句
# reg_rows = cur.fetchall()
print(sql)     # 执行sql语句


news_list = demo_data.demo_data
browser = webdriver.Chrome()
if not news_list:
	news_list = get_yicai_news_list(key_text)	# 获取所有的新闻列表页面
for url in news_list:
	if 'html' in url:
		print(url)
		# get_page_text(url)
browser.quit()
