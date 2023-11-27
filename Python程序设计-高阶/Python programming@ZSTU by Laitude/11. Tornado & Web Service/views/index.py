from tornado.web import RequestHandler, authenticated
from tornado.httpclient import AsyncHTTPClient
import tornado.web
import config
import os
import json

# 操作数据库
from models import Users

# class MainPageHandler(RequestHandler):
#     def get(self, *args, **kwargs):
#         # 反向解析
#         # url = self.reverse_url('huck')
#         # self.write('<a href="%s">点击切换页面</a>' % url)
#         self.render('mainpage.html')

class KainHandler(RequestHandler):
    # 该方法会在http方法之前调用
    def initialize(self, item1, item2):
        self.item1 = item1
        self.itme2 = item2

    def get(self, *args, **kwargs):
        # print(self.item1, self.itme2)
        self.write('Hello Kain')

class HuckHandler(RequestHandler):
    def initialize(self, item3, item4):
        self.item3 = item3
        self.item4 = item4

    def get(self, *args, **kwargs):
        self.write('Hello huck')

# 匹配URL中的特定部分
class KainHuckHandler(RequestHandler):
    def get(self, h1, h2, h3, *args, **kwargs):
        print(h1,h2,h3)
        self.write('hello kainhuck')

# 获取get方法传递的参数
class GetArgHandler(RequestHandler):
    def get(self, *args, **kwargs):
        # strip过滤左右空格
        a = self.get_query_argument('a',default='not_a',strip=True)
        b = self.get_argument('b')
        self.write('get args')
        print(a, b)

# request
class ZhuyinHandler(RequestHandler):
    def get(self, *args, **kwargs):
        # print(self.request.method)
        # print(self.request.host)
        # print(self.request.uri) # 注意是uri不是url
        # print(self.request.path)
        # print(self.request.query)
        # print(self.request.version)
        # print(self.request.headers)
        # print(self.request.body)
        # print(self.request.remote_ip)
        # print(self.request.files)
        self.write('zhuyin<br><br>')
        self.write(str(self.request.method) + '<br><br>')
        self.write(str(self.request.host) + '<br><br>')
        self.write(str(self.request.uri) + '<br><br>')  # 注意是uri不是url
        self.write(str(self.request.path) + '<br><br>')
        self.write(str(self.request.query) + '<br><br>')
        self.write(str(self.request.version) + '<br><br>')
        self.write(str(self.request.headers) + '<br><br>')
        self.write(str(self.request.body) + '<br><br>')
        self.write(str(self.request.remote_ip) + '<br><br>')
        self.write(str(self.request.files))

# post
class PostFileHandler(RequestHandler):
    def get(self, *args, **kwargs):
        self.render('register.html')

    def post(self, *args, **kwargs):
        username = self.get_argument('username')
        password = self.get_argument('password')
        print(username, password)
        self.write('<script>\
                    window.alert("注册成功");\
                    </script>')

    def options(self, *args, **kwargs):
        username = self.get_argument('username')
        password = self.get_argument('password')
        print(username,password)


# json
class Json1Handler(RequestHandler):
    def get(self, *args, **kwargs):
        per = {
            "name": "kain huck",
            "age": 18,
            "height": 170
        }
        # 将字典转换成json字符串
        jsonStr = json.dumps(per)
        self.write(jsonStr)

# 推荐
class Json2Handler(RequestHandler):
    def get(self, *args, **kwargs):
        per = {
            "name": "kain huck",
            "age": 18,
            "height": 170
        }
        self.write(per)

# 上传文件
class UpFileHandler(RequestHandler):
    def get(self, *args, **kwargs):
        self.render('upfile.html')

    def post(self):
        fileDict = self.request.files
        for inputname in fileDict:
            fileArr = fileDict[inputname]
            for fileObj in fileArr:
                #储存路径
                filepath = os.path.join(config.BASE_DIRS, 'upfile/'+fileObj.filename)
                with open(filepath, 'wb') as f:
                    f.write(fileObj.body)

        self.write('ok')

# 设置响应头
class HeaderHandler(RequestHandler):
    def set_default_headers(self):
        self.set_header('name','kain')

    def get(self, *args, **kwargs):
        self.write('set header page')

# 定制返回状态码
class StatusCodeHandlers(RequestHandler):
    def get(self, *args, **kwargs):
        # self.set_status(404)
        self.write('status_code page')
        self.write('666 ha ha ha')
        self.set_status(666, 'hahaha')


class FilesHandles(RequestHandler):
    def post(self):
        f=file.open('aaa.epq','r')
        #输出所有的地震文件


# 重定向
class RedirectHandler(RequestHandler):
    def get(self, *args, **kwargs):
        self.redirect('/')


# 错误处理
class ErrorHandler(RequestHandler):
    # 接受send_error发送的错误
    def write_error(self, status_code, **kwargs):
        if status_code == 404:
            self.write("页面未找到")
        elif status_code == 500:
            self.write("服务器内部错误")

    def get(self, *args, **kwargs):
        flag = self.get_query_argument('flag')
        if flag == '0':
            self.send_error(404)
        elif flag == '1':
            self.send_error(500)
        else:
            self.write('一切正常,没有错误')

# 接口测试
class IndexHandler(RequestHandler):
    def initialize(self):
        print('initialize')

    def prepare(self):
        print('prepare')

    def get(self, *args, **kwargs):
        print('HTTP方法')
        self.write('hello kainhuck')

    def set_default_headers(self):
        print('set_default_headers')

    def write_error(self, status_code, **kwargs):
        print('write_error')

    def on_finish(self):
        print('on_finish')

# 参数,自定义函数,转义
class FunTranHandler(RequestHandler):
    def get(self, *args, **kwargs):
        title = '参数,自定义函数,转义测试页面'
        lists = [
            {
                'name': 'kain',
                'age': 18,
            },
            {
                'name': 'huck',
                'age': 19,
            }
        ]
        Tstr = '<h1>转义测试字符段</h1>'
        self.render('fun_arg.html', title=title, lists=lists, Tstr=Tstr)

# static
class StaticHandler(RequestHandler):
    def get(self, *args, **kwargs):
        self.render('static_test.html')

# 继承
class InheritHandler(RequestHandler):
    def get(self, *args, **kwargs):
        title = 'inherit'
        self.render('child.html', title=title)

# 数据库
class UsersHandler(RequestHandler):
    def get(self, *args, **kwargs):
        # 从数据库中提取数据
        # users = Users.all()
        # self.render('user.html', users=users)

        # 增加数据
        # user = Users('hello','world')
        # user.save()

        # 删除数据
        user = Users('hello', 'world')
        user.delete()
        self.write('ok')

# 图片展示
class ImgHandler(RequestHandler):
    def get(self, *args, **kwargs):
        self.render('img.html')

# cookie
class CookieHandler(RequestHandler):
    def get(self, *args, **kwargs):
        # 设置普通cookie
        # self.set_cookie('kain','huck')
        # self.set_header('Set-Cookie', 'huck=kain; Path=/')

        # 获取普通cookie
        # cookie1 = self.get_cookie('huck','没有这个cookie')
        # cookie2 = self.get_cookie('kain','没有这个cookie')
        # cookie3 = self.get_cookie('kainhuck', '没有这个cookie')
        # print("cookie =",cookie1+' '+cookie2,cookie3)

        # 清除cookie
        # self.clear_cookie('kain')

        # 设置安全cookie
        # self.set_secure_cookie('kain','huck')

        # 获取安全cookie
        cookie = self.get_secure_cookie('kain')
        print(cookie)

        self.write('cookie ok')

# cookie计数
class CookieNumHandler(RequestHandler):
    def write_error(self, status_code, **kwargs):
        if status_code == 403:
            self.write('你的访问太频繁,')

    def prepare(self):
        count = self.get_cookie('count', None)
        if not count:
            pass
        else:
            if int(count) > 20:
                self.send_error(403)

    def get(self, *args, **kwargs):
        count = self.get_cookie('count')
        self.render('cookienum.html', count=count)

class PostCookieHandler(RequestHandler):
    def get(self, *args, **kwargs):
        self.render('postcookie.html')

    def post(self, *args, **kwargs):
        count = self.get_cookie('count', None)
        if not count:
            count = 1
        else:
            count = int(count)
            count += 1

        self.set_cookie('count', str(count))
        self.redirect('/cookienum')


# 用户验证
class LoginHandler(RequestHandler):
    def get(self, *args, **kwargs):
        next = self.get_argument('next', '/')
        url = 'login?next=' + next
        self.render('login.html', url=url)

    def post(self, *args, **kwargs):
        name = self.get_argument('username')
        passwd = self.get_argument('password')
        if name == 'kain' and passwd == '123456':
            next = self.get_argument('next', '/')
            self.redirect(next+'?flag=logined')
        else:
            next = self.get_argument('next', '/')
            print(next)
            self.redirect('/login?next='+next)

class HomeHandler(RequestHandler):
    # 配合 authenticated 装饰器使用
    def get_current_user(self):
        flag = self.get_argument('flag', None)
        return flag

    @authenticated
    def get(self, *args, **kwargs):
        self.render('home.html')


# 回调函数异步
class StudentHandler(RequestHandler):
    def on_response(self, response):
        if response.error:
            self.send_error(500)
        else:
            data = json.loads(response.body)
            self.write(data)
        self.finish()

    # @tornado.web.asynchronous #不关闭通信的通道
    def get(self, *args, **kwargs):

        url = "http://www.std.gov.cn/gb/search/gbQueryPage?searchText=&ics=&state=&ISSUE_DATE=&sortOrder=asc&pageSize=15&pageNumber=2&_=1541495603600"

        # 创建客户端
        client = AsyncHTTPClient()
        client.fetch(url, self.on_response)

# 协程异步
class TeacherHandler(RequestHandler):
    @tornado.gen.coroutine
    def get(self, *args, **kwargs):
        url = "http://www.std.gov.cn/gb/search/gbQueryPage?searchText=&ics=&state=&ISSUE_DATE=&sortOrder=asc&pageSize=15&pageNumber=2&_=1541495603600"
        client = AsyncHTTPClient()
        res = yield client.fetch(url)
        if res.error:
            self.send_error(500)
        else:
            data = json.loads(res.body)
            self.write(data)

class TeacherPlusHandler(RequestHandler):
    @tornado.gen.coroutine
    def get(self, *args, **kwargs):
        res = yield self.getDate()
        self.write(res)

    @tornado.gen.coroutine
    def getDate(self):
        url = "http://www.std.gov.cn/gb/search/gbQueryPage?searchText=&ics=&state=&ISSUE_DATE=&sortOrder=asc&pageSize=15&pageNumber=2&_=1541495603600"
        client = AsyncHTTPClient()
        res = yield client.fetch(url)

# 定义自己的StaticFileHandler
class StaticFileHandler(tornado.web.StaticFileHandler):
    def __init__(self, *args, **kwargs):
        super(StaticFileHandler, self).__init__(*args, **kwargs)
        self.xsrf_token

# 404页面
# class NotFoundHandler(RequestHandler):
#     def write_error(self, status_code, **kwargs):
#         self.write("404咯,这就说明你要的界面我们没有")

#     def get(self, *args, **kwargs):
#         self.send_error(404)






















