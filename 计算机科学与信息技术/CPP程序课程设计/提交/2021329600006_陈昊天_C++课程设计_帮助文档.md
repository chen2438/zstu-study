# expressManager-帮助文档

[Releases](https://github.com/chen2438/expressManager/releases)

## 安装与环境配置

以 Debian 10 为例, root 权限执行.

### 安装 PHP

```bash
apt update
apt install php php-fpm
```

### 安装 Nginx

```bash
apt install nginx
systemctl status nginx #查看nginx是否正常启动(Active: active (running))
```

```bash
root@vm:/var/www/html# systemctl status nginx
● nginx.service - A high performance web server and a reverse proxy server
   Loaded: loaded (/lib/systemd/system/nginx.service; enabled; vendor preset: enabled)
   Active: active (running) since Wed 2023-02-08 12:08:38 UTC; 57min ago
     Docs: man:nginx(8)
 Main PID: 31132 (nginx)
    Tasks: 2 (limit: 1163)
   Memory: 4.4M
   CGroup: /system.slice/nginx.service
           ├─31132 nginx: master process /usr/sbin/nginx -g daemon on; master_process on;
           └─31133 nginx: worker process
```

### 配置 Nginx

```bash
rm /etc/nginx/sites-enabled/default
vim /etc/nginx/sites-enabled/default
```

将`/etc/nginx/sites-enabled/default`修改为以下内容

```bash
server {
        listen 80 default_server;
        listen [::]:80 default_server;
        root /var/www/html;
        index index.php  index.html index.htm index.nginx-debian.html;
        add_header Access-Control-Allow-Origin *;
        add_header Access-Control-Allow-Methods 'GET, POST, OPTIONS';
        add_header Access-Control-Allow-Headers 'DNT,X-Mx-ReqToken,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Authorization';
        if ($request_method = 'OPTIONS') {
            return 204;
        }
        server_name localhost;
        location / {
                try_files $uri $uri/ =404;
        }
        location ~ \.php$ {
                include snippets/fastcgi-php.conf;
                # With php-fpm (or other unix sockets):
                fastcgi_pass unix:/run/php/php7.3-fpm.sock;
                # With php-cgi (or other tcp sockets):
                #fastcgi_pass 127.0.0.1:9000;
        }
}
```

### 安装 MySQL

参考:https://github.com/chen2438/docs/blob/main/debian/d-mysql.md

### 配置MySQL登陆信息

```bash
cd /var/www/html
vim connectDB.in
```

填入你的 MySQL 登陆信息

```bash
localhost
root
root密码
```

### 配置 C++ 连接 MySQL

```bash
#apt install libmysqld-dev libmysqlclient-dev
apt install libmariadbd-dev libmariadb-dev-compat libmariadb-dev
```

### 设置 MySQL 数据库

如图所示

<img src="https://media.opennet.top/i/2023/02/08/63e3a0ff70821.png" style="zoom:50%;" />

设置express表属性

![image-20230208212005171](https://media.opennet.top/i/2023/02/08/63e3a18feb93c.png)

设置user表属性

![image-20230208212059554](https://media.opennet.top/i/2023/02/08/63e3a1becb971.png)

### 编译

```bash
cd /var/www/html && rm -rf expressManager/
git clone https://github.com/chen2438/expressManager.git
```

```bash
g++ expressManager/cpp/main.cpp  -std=c++17 -o expressManager/cpp/main `mysql_config --cflags --libs` && chmod 777 -R expressManager/ 
```

### 访问

`http://IP地址/expressManager`
