package com.hadoop.hdfs;


import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.IOUtils;
import org.junit.Test;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class HdfsClient{
    @Test
    public void testMkdirs() throws IOException, InterruptedException, URISyntaxException {

        // 1 获取文件系统
        Configuration configuration = new Configuration();
        // 配置在集群上运行
        // configuration.set("fs.defaultFS", "hdfs://hadoop101:9000");
        // FileSystem fs = FileSystem.get(configuration);

        FileSystem fs = FileSystem.get(new URI("hdfs://node1:8020"), configuration, "root");

        // 2 创建目录
        fs.mkdirs(new Path("/0723"));

        // 3 关闭资源
        fs.close();
    }

    @Test
    public void testCopyFromLocalFile() throws IOException, InterruptedException, URISyntaxException {
        // 1 获取文件系统
        Configuration configuration = new Configuration();
        configuration.set("dfs.replication", "2");
        FileSystem fs = FileSystem.get(new URI("hdfs://node1:8020"), configuration, "root");

        // 2 上传文件
        fs.copyFromLocalFile(new Path("src/main/java/com/hadoop/hdfs/hello.txt"), new Path("/hello3.txt"));

        // 3 关闭资源
        fs.close();
        System.out.println("over");
    }

    @Test
    public void testCopyToLocalFile() throws IOException, InterruptedException, URISyntaxException{
        // 1 获取文件系统
        Configuration configuration = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://node1:8020"), configuration, "root");

        // 2 执行下载操作
        // boolean delSrc 指是否将原文件删除
        // Path src 指要下载的文件路径
        // Path dst 指将文件下载到的路径
        // boolean useRawLocalFileSystem 是否开启文件校验
        fs.copyToLocalFile(false, new Path("/hello.txt"), new Path("src/main/java/com/hadoop/hdfs/hello1.txt"), true);

        // 3 关闭资源
        fs.close();
    }

    @Test
    public void testDelete() throws IOException, InterruptedException, URISyntaxException{
        // 1 获取文件系统
        Configuration configuration = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://node1:8020"), configuration, "root");

        // 2 执行删除
        fs.delete(new Path("/0723/"), true);

        // 3 关闭资源
        fs.close();
    }

    @Test
    public void testRename() throws IOException, InterruptedException, URISyntaxException{
        // 1 获取文件系统
        Configuration configuration = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://node1:8020"), configuration, "root");

        // 2 修改文件名称
        fs.rename(new Path("/hello.txt"), new Path("/hello6.txt"));

        // 3 关闭资源
        fs.close();
    }

    @Test
    public void testListStatus() throws IOException, InterruptedException, URISyntaxException{

        // 1 获取文件配置信息
        Configuration configuration = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://node1:8020"), configuration, "root");

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

    @Test
    public void putFileToHDFS() throws Exception {
        // 1. 获取对象
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://node1:8020"), conf, "root");
        // 2. 输入流
        FileInputStream fis = new FileInputStream(new File("/Users/nanmener/Downloads/hadoop-3.3.6.tar.gz"));
        // 3. 输出流
        FSDataOutputStream fos = fs.create(new Path("/hadoop-3.3.6.tar.gz"));
        // 4. 输入输出流相互拷贝
        IOUtils.copyBytes(fis, fos, conf);
        // 5. 关闭流
        IOUtils.closeStream(fos);
        IOUtils.closeStream(fis);
        fs.close();
    }

    @Test
    public void getFileFromHDFS() throws IOException, InterruptedException, URISyntaxException {
        // 1. 创建配置对象
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://node1:8020"), conf, "root");
        // 2. 输入流
        FSDataInputStream fis = fs.open(new Path("/hadoop-3.3.6.tar.gz"));
        // 3. 输出流
        FileOutputStream fos = new FileOutputStream(new File("/Users/nanmener/Downloads/hadoop-3.3.6.tar.gz.2"));
        // 4. 流互拷贝
        IOUtils.copyBytes(fis, fos, conf);
        // 5. 关闭流对象
        IOUtils.closeStream(fos);
        IOUtils.closeStream(fis);
        fs.close();
    }

    @Test
    /**
     * 下载第1块内容
     */
    public void readFileSeek1() throws IOException, InterruptedException, URISyntaxException {
        // 1. 获取对象
        Configuration conf = new Configuration();
        FileSystem fs = FileSystem.get(new URI("hdfs://node1:8020"), conf, "root");
        // 2.获取输入流
        FSDataInputStream fis = fs.open(new Path("/hadoop-3.3.6.tar.gz"));
        // 3. 获取输出流
        FileOutputStream fos = new FileOutputStream(new File("/Users/nanmener/Downloads/hadoop-3.3.6.tar.gz.part1"));
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
        FileSystem fs = FileSystem.get(new URI("hdfs://node1:8020"), conf, "root");
        // 2. 获取输入流
        FSDataInputStream fis = fs.open(new Path("/hadoop-3.3.6.tar.gz"));
        // 3. 指定输入流读取位置
        fis.seek(1024*1024*128);
        // 4. 获取输出流
        FileOutputStream fos = new FileOutputStream(new File("/Users/nanmener/Downloads/hadoop-3.3.6.tar.gz.part2"));
        // 5. 流的互拷贝
        IOUtils.copyBytes(fis, fos, conf);
        // 6. 关闭资源
        IOUtils.closeStream(fos);
        IOUtils.closeStream(fis);
        fs.close();
    }
}