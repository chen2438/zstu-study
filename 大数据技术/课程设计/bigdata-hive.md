---
description: 发布于 2024-06-23
categories:
- study
date: 2024-06-23
slug: bigdata-hive
title: Hive 搭建和实操
updated: 
tags:
- study
- hadoop
- hive
copyright: false
---

# Hive 搭建和实操

> 浙江理工大学 2024 大数据应用项目实践 实操 Hive
>
> [实操文档和项目代码](https://github.com/chen2438/zstu-study/tree/main/%E5%A4%A7%E6%95%B0%E6%8D%AE%E6%8A%80%E6%9C%AF/%E8%AF%BE%E7%A8%8B%E8%AE%BE%E8%AE%A1)

从 [这篇博客](https://chenhaotian.top/linux/hadoop-hdfs-build/) 搭建Hadoop后，在node1上安装MySQL和Hive

## 安装 MySQL

1. **安装MySQL 服务器**

   在node1上执行以下命令来安装MySQL：

   ```bash
   sudo apt update
   sudo apt-get install mysql-server
   ```

2. **配置MySQL**

   启动MySQL服务并进行安全设置：

   ```bash
   sudo systemctl start mysql
   sudo mysql_secure_installation
   ```

   按照提示完成安全设置，创建root用户密码等。

3. **创建Hive数据库**

   使用MySQL登录并创建Hive所需的数据库和用户：

   ```bash
   sudo mysql -u root -p
   ```

   在MySQL shell中执行以下命令：

   ```sql
   CREATE DATABASE metastore;
   CREATE USER 'hiveuser'@'localhost' IDENTIFIED BY 'hivepassword';
   GRANT ALL PRIVILEGES ON metastore.* TO 'hiveuser'@'localhost';
   FLUSH PRIVILEGES;
   EXIT;
   ```

## 安装 Hive

1. **下载并解压Hive**

   在node1上执行以下命令来下载并解压Hive：

   ```bash
   cd /usr/local
   wget https://downloads.apache.org/hive/hive-3.1.3/apache-hive-3.1.3-bin.tar.gz
   sudo tar -zxvf apache-hive-3.1.3-bin.tar.gz
   sudo mv apache-hive-3.1.3-bin hive
   rm apache-hive-3.1.3-bin.tar.gz
   ```

2. **配置环境变量**

   在~/.bashrc文件中添加以下内容：

   ```bash
   export HIVE_HOME=/usr/local/hive
   export PATH=$PATH:$HIVE_HOME/bin
   ```

   使更改生效：

   ```bash
   source ~/.bashrc
   ```

3. **配置Hive**
   
   创建Hive配置目录并编辑配置文件：
   
   ```bash
   sudo mkdir -p $HIVE_HOME/conf
   cd $HIVE_HOME/conf
   # sudo cp $HIVE_HOME/conf/hive-default.xml.template $HIVE_HOME/conf/hive-site.xml
   sudo vim $HIVE_HOME/conf/hive-site.xml
   ```
   
   `hive-site.xml`：
   
   ```xml
   <configuration>
    <property>
        <name>javax.jdo.option.ConnectionURL</name>
        <value>jdbc:mysql://localhost/metastore</value>
        <description>JDBC connect string for a JDBC metastore</description>
    </property>
    <property>
        <name>javax.jdo.option.ConnectionDriverName</name>
        <value>com.mysql.cj.jdbc.Driver</value>
        <description>Driver class name for a JDBC metastore</description>
    </property>
    <property>
        <name>javax.jdo.option.ConnectionUserName</name>
        <value>hiveuser</value>
        <description>Username to use against metastore database</description>
    </property>
    <property>
        <name>javax.jdo.option.ConnectionPassword</name>
        <value>hivepassword</value>
        <description>Password to use against metastore database</description>
    </property>
    <property>
        <name>hive.metastore.warehouse.dir</name>
        <value>/user/hive/warehouse</value>
        <description>location of default database for the warehouse</description>
    </property>
    <property>
   	<name>hive.cli.print.header</name>
   	<value>true</value>
    </property>
    <property>
   	<name>hive.cli.print.current.db</name>
   	<value>true</value>
    </property>
   </configuration>
   ```
   
4. **下载MySQL JDBC驱动**

   下载MySQL JDBC驱动并放到Hive的lib目录：

   ```bash
   cd /usr/local
   wget https://dev.mysql.com/get/Downloads/Connector-J/mysql-connector-java-8.0.26.tar.gz
   tar -zxvf mysql-connector-java-8.0.26.tar.gz
   sudo cp mysql-connector-java-8.0.26/mysql-connector-java-8.0.26.jar $HIVE_HOME/lib/
   rm mysql-connector-java-8.0.26.tar.gz
   # rm -r mysql-connector-java-8.0.26
   ```

5. **初始化Hive Metastore**

   运行以下命令初始化Hive Metastore：

   ```bash
   schematool -initSchema -dbType mysql
   ```

6. **验证安装**

   启动Hive CLI并验证安装：

   ```bash
   hive
   ```

7. **修改HDFS权限**

   ```bash
   hdfs dfs -mkdir -p /user/hive/warehouse
   hdfs dfs -chmod -R 777 /user/hive/warehouse
   ```

## 验证 Hive

1. 创建一个目录来存放数据文件

   ```bash
   hdfs dfs -mkdir -p /user/hive/warehouse/user_data
   ```

2. 上传数据文件到新目录

   确保数据文件在本地存在，如果不存在，请创建一个：

   ```bash
   echo -e "1,John\n2,Jane\n3,Bob" > data.csv
   ```

   然后将数据文件上传到 HDFS 的 `/user/hive/warehouse/user_data` 目录：

   ```bash
   hdfs dfs -put data.csv /user/hive/warehouse/user_data/
   ```

3. 在Hive CLI中，运行以下命令创建一个示例表并查询：

    ```sql
    CREATE EXTERNAL TABLE IF NOT EXISTS user_data (
        id INT,
        name STRING
    )
    ROW FORMAT DELIMITED
    FIELDS TERMINATED BY ','
    STORED AS TEXTFILE
    LOCATION 'hdfs://node1:8020/user/hive/warehouse/user_data';
    
    SELECT * FROM user_data;
    ```

   ![image-20240623161331200](https://media.opennet.top/i/2024/06/23/pi3kaf-0.png)

   ![image-20240623161423347](https://media.opennet.top/i/2024/06/23/pieu9e-0.png)

## 外部表 案例实操

分别创建部门和员工外部表，并向表中导入数据。

### 1 原始数据

注意数据以制表符分隔

dept.txt

```
10	ACCOUNTING	1700
20	RESEARCH	1800
30	SALES	1900
40	OPERATIONS	1700
```

emp.txt

```
7369	SMITH	CLERK	7902	1980-12-17	800.00	0.00	20
7499	ALLEN	SALESMAN	7698	1981-2-20	1600.00	300.00	30
7521	WARD	SALESMAN	7698	1981-2-22	1250.00	500.00	30
7566	JONES	MANAGER	7839	1981-4-2	2975.00	0.00	20
7654	MARTIN	SALESMAN	7698	1981-9-28	1250.00	1400.00	30
7698	BLAKE	MANAGER	7839	1981-5-1	2850.00	0.00	30
7782	CLARK	MANAGER	7839	1981-6-9	2450.00	0.00	10
7788	SCOTT	ANALYST	7566	1987-4-19	3000.00	0.00	20
7839	KING	PRESIDENT	NULL	1981-11-17	5000.00	0.00	10
7844	TURNER	SALESMAN	7698	1981-9-8	1500.00	0.00	30
7876	ADAMS	CLERK	7788	1987-5-23	1100.00	0.00	20
7900	JAMES	CLERK	7698	1981-12-3	950.00	0.00	30
7902	FORD	ANALYST	7566	1981-12-3	3000.00	0.00	20
7934	MILLER	CLERK	7782	1982-1-23	1300.00	0.00	10
```

### 2 建表语句

创建部门表

```sql
create external table if not exists dept(
deptno int,
dname string,
loc int
)
row format delimited fields terminated by '\t';
```

创建员工表

```sql
create external table if not exists emp(
empno int,
ename string,
job string,
mgr int,
hiredate string, 
sal double, 
comm double,
deptno int)
row format delimited fields terminated by '\t';
```

### 3 查看创建的表

```sql
show tables;
```

![image-20240623163031191](https://media.opennet.top/i/2024/06/23/ps7zq6-0.png)

### 4 向外部表中导入数据

导入数据，原始数据文件位于虚拟机上

```sql
load data local inpath '/root/dept.txt' into table default.dept;
load data local inpath '/root/emp.txt' into table default.emp;
```

![image-20240623163245481](https://media.opennet.top/i/2024/06/23/qhb4ey-0.png)

查询结果

```sql
select * from dept;
select * from emp;
```

![image-20240623165133487](https://media.opennet.top/i/2024/06/23/qsjw3t-0.png)

![image-20240623172551561](https://media.opennet.top/i/2024/06/23/rcwdh7-0.png)

### 5 查看表格式化数据

```sql
desc formatted dept;
```

![image-20240623172901710](https://media.opennet.top/i/2024/06/23/reqw5p-0.png)
