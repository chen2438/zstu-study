---
description: 发布于 2024-06-22
categories:
- study
date: 2024-06-22
slug: bigdata-hdfs-java
title: 大数据应用项目实践：HDFS的Java客户端操作
updated: 
tags:
- study
- hadoop
- hdfs
copyright: false
---

# 大数据应用项目实践：HDFS的Java客户端操作

> 浙江理工大学 2024 大数据应用项目实践 实操 HDFS的Java客户端操作
>
> [实操文档和项目代码](https://github.com/chen2438/zstu-study/tree/main/%E5%A4%A7%E6%95%B0%E6%8D%AE%E6%8A%80%E6%9C%AF/%E8%AF%BE%E7%A8%8B%E8%AE%BE%E8%AE%A1)

## 3.1 HDFS客户端环境准备

创建一个Maven工程，在pom.xml的`<project>`中添加以下依赖：

```xml
<dependencies>
		<dependency>
			<groupId>junit</groupId>
			<artifactId>junit</artifactId>
			<version>4.12</version>
		</dependency>
		<dependency>
			<groupId>org.apache.logging.log4j</groupId>
			<artifactId>log4j-core</artifactId>
			<version>2.8.2</version>
		</dependency>
		<dependency>
			<groupId>org.apache.hadoop</groupId>
			<artifactId>hadoop-common</artifactId>
			<version>2.7.2</version>
		</dependency>
		<dependency>
			<groupId>org.apache.hadoop</groupId>
			<artifactId>hadoop-client</artifactId>
			<version>2.7.2</version>
		</dependency>
		<dependency>
			<groupId>org.apache.hadoop</groupId>
			<artifactId>hadoop-hdfs</artifactId>
			<version>2.7.2</version>
		</dependency>
</dependencies>
```

在项目的src/main/resources目录下，新建一个文件，命名为“log4j.properties”，在文件中填入

```
log4j.rootLogger=info, stdout
log4j.appender.stdout=org.apache.log4j.ConsoleAppender
log4j.appender.stdout.layout=org.apache.log4j.PatternLayout
log4j.appender.stdout.layout.ConversionPattern=%d %p [%c] - %m%n
log4j.appender.logfile=org.apache.log4j.FileAppender
log4j.appender.logfile.File=target/spring.log
log4j.appender.logfile.layout=org.apache.log4j.PatternLayout
log4j.appender.logfile.layout.ConversionPattern=%d %p [%c] - %m%n
```

创建HdfsClient类

```java
public class HdfsClient{	
@Test
	public void testMkdirs() throws IOException, InterruptedException, URISyntaxException{
		
		// 1 获取文件系统
		Configuration configuration = new Configuration();
		// 配置在集群上运行
		// configuration.set("fs.defaultFS", "hdfs://hadoop101:9000");
		// FileSystem fs = FileSystem.get(configuration);

		FileSystem fs = FileSystem.get(new URI("hdfs://hadoop101:9000"), configuration, "root");
		
		// 2 创建目录
		fs.mkdirs(new Path("/0723"));
		
		// 3 关闭资源
		fs.close();
	}
}
```

## 3.2 HDFS的API操作

### 3.2.1 HDFS文件上传

```java
	@Test
	public void testCopyFromLocalFile() throws IOException, InterruptedException, URISyntaxException {
		// 1 获取文件系统
		Configuration configuration = new Configuration();
		configuration.set("dfs.replication", "2");
		FileSystem fs = FileSystem.get(new URI("hdfs://hadoop101:9000"), configuration, "root");

		// 2 上传文件
		fs.copyFromLocalFile(new Path("e:/hello.txt"), new Path("/hello.txt"));

		// 3 关闭资源
		fs.close();
		System.out.println("over");
}
```

![image-20240622152439434](https://media.opennet.top/i/2024/06/22/o17l2r-0.png)

### 3.2.2 HDFS文件下载

```java
	@Test
	public void testCopyToLocalFile() throws IOException, InterruptedException, URISyntaxException{
		// 1 获取文件系统
		Configuration configuration = new Configuration();
		FileSystem fs = FileSystem.get(new URI("hdfs://hadoop101:9000"), configuration, "root");
		
		// 2 执行下载操作
		// boolean delSrc 指是否将原文件删除
		// Path src 指要下载的文件路径
		// Path dst 指将文件下载到的路径
		// boolean useRawLocalFileSystem 是否开启文件校验
		fs.copyToLocalFile(false, new Path("/hello1.txt"), new Path("e:/hello1.txt"), true);
		
		// 3 关闭资源
		fs.close();
}
```

### 3.2.3 HDFS文件夹删除

```java
	@Test
	public void testDelete() throws IOException, InterruptedException, URISyntaxException{
		// 1 获取文件系统
		Configuration configuration = new Configuration();
		FileSystem fs = FileSystem.get(new URI("hdfs://hadoop101:9000"), configuration, "root");
		
		// 2 执行删除
		fs.delete(new Path("/1108/"), true);
		
		// 3 关闭资源
		fs.close();
}
```

### 3.2.4 HDFS文件名更改

```java
	@Test
	public void testRename() throws IOException, InterruptedException, URISyntaxException{
		// 1 获取文件系统
		Configuration configuration = new Configuration();
		FileSystem fs = FileSystem.get(new URI("hdfs://hadoop101:9000"), configuration, "root"); 
		
		// 2 修改文件名称
		fs.rename(new Path("/hello.txt"), new Path("/hello6.txt"));
		
		// 3 关闭资源
		fs.close();
}
```

### 3.2.5 HDFS文件和文件夹判断

```java
	@Test
	public void testListStatus() throws IOException, InterruptedException, URISyntaxException{
		
		// 1 获取文件配置信息
		Configuration configuration = new Configuration();
		FileSystem fs = FileSystem.get(new URI("hdfs://hadoop101:9000"), configuration, "root");
		
		// 2 判断是文件还是文件夹
		FileStatus[] listStatus = fs.listStatus(new Path("/"));
		
		for (FileStatus fileStatus : listStatus) {
			
			// 如果是文件
			if (fileStatus.isFile()) {
				System.out.println("f:"+fileStatus.getPath().getName());
			}else {
				System.out.println("d:"+fileStatus.getPath().getName());
			}
		}
		
		// 3 关闭资源
		fs.close();
}
```

![image-20240622161009700](https://media.opennet.top/i/2024/06/22/pg06il-0.png)

### 3.2.6 通过IO流操作HDFS

HDFS文件上传

```java
    @Test
    public void putFileToHDFS() throws Exception {
        // 1. 获取对象
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://hadoop101:9000"), conf, "root");
        // 2. 输入流
        FileInputStream fis = new FileInputStream(new File("testio.txt"));
        // 3. 输出流
        FSDataOutputStream fos = fs.create(new Path("/testio.txt"));
        // 4. 输入输出流相互拷贝
        IOUtils.copyBytes(fis, fos, conf);
        // 5. 关闭流
        IOUtils.closeStream(fos);
        IOUtils.closeStream(fis);
        fs.close();
    }
```

HDFS文件下载到本地

```java
    @Test
    public void getFileFromHDFS() throws IOException, InterruptedException, URISyntaxException {
        // 1. 创建配置对象
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://hadoop101:9000"), conf, "root");
        // 2. 输入流
        FSDataInputStream fis = fs.open(new Path("/testio.txt"));
        // 3. 输出流
        FileOutputStream fos = new FileOutputStream(new File("testio1.txt"));
        // 4. 流互拷贝
        IOUtils.copyBytes(fis, fos, conf);
        // 5. 关闭流对象
        IOUtils.closeStream(fos);
        IOUtils.closeStream(fis);
        fs.close();
    }
```

定位文件读取 - 下载第一块

```java
    @Test
    /**
     * 下载第1块内容
     */
    public void readFileSeek1() throws IOException, InterruptedException, URISyntaxException {
        // 1. 获取对象
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://hadoop101:9000"), conf, "root");
        // 2.获取输入流
        FSDataInputStream fis = fs.open(new Path("/hadoop-3.3.6.tar.gz"));
        // 3. 获取输出流
        FileOutputStream fos = new FileOutputStream(new File("hadoop-3.3.6.tar.gz.part1"));
        // 4. 流的互拷贝（这里只拷贝指定大小的数据流128M）
        byte[] buffer = new byte[1024];
        for (int i = 0; i < 1024 * 128; i++) {
            fis.read(buffer);
            fos.write(buffer);
        }
        // 5. 关闭资源
        IOUtils.closeStream(fos);
        IOUtils.closeStream(fis);
        fs.close();
    }
```

定位文件读取 - 下载第二块

```java
    @Test
    /**
     * 下载第2块资源
     * @throws URISyntaxException
     * @throws InterruptedException
     * @throws IOException
     */
    public void readFileSeek2() throws IOException, InterruptedException, URISyntaxException {
        // 1. 获取对象
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://hadoop101:9000"), conf, "root");
        // 2. 获取输入流
        FSDataInputStream fis = fs.open(new Path("/hadoop-3.3.6.tar.gz"));
        // 3. 指定输入流读取位置
        fis.seek(1024*1024*128);
        // 4. 获取输出流
        FileOutputStream fos = new FileOutputStream(new File("hadoop-3.3.6.tar.gz.part2"));
        // 5. 流的互拷贝
        IOUtils.copyBytes(fis, fos, conf);
        // 6. 关闭资源
        IOUtils.closeStream(fos);
        IOUtils.closeStream(fis);
        fs.close();
    }
```

合并文件

```bash
cat hadoop-3.3.6.tar.gz.part1 hadoop-3.3.6.tar.gz.part2 > merged.tar.gz
```

![image-20240622163553253](https://media.opennet.top/i/2024/06/22/qj76e6-0.png)
