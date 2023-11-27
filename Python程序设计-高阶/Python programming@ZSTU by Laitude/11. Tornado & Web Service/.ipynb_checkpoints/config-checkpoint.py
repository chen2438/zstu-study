import os
BASE_DIRS = os.path.dirname(__file__)

# 参数
options = {
    'port': 8080,
}

# 数据库配置
mysql = {
    "host": "localhost",
    "user": "root",
    "passwd": "kain1123",
    "dbName": "web_test"
}

# 配置
settings = {
    "static_path": os.path.join(BASE_DIRS, 'static'),
    "template_path": os.path.join(BASE_DIRS, 'templates'),
    "cookie_secret": '2LBKQd6iTOWKBlPiyvXG+1aTW0PdDEHsmkb4s+Nzfcs=', # 安全cookie的秘钥,uuid base64加密获得  base64.b64encode(uuid.uuid4().bytes + uuid.uuid4.bytes)
    "xsrf_cookies": False,   # True为开启同源保护
    "login_url": '/login',  # authenticated指定的重定向页面
    "debug": True,
    # "autoescape": None 该设置为关闭整个项目的自动转义,不推荐使用
}
