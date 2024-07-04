package com.bigdata.mapreduce.flowsum;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Partitioner;

public class ProvincePartitioner extends Partitioner<Text, FlowBean> {

    @Override
    public int getPartition(Text key, FlowBean value, int numPartitions) {
        // 1 获取电话号码的前三位
        String preNum = key.toString().substring(0, 3);

        int partition = 4;

        // 2 判断是哪个省
        if ("135".equals(preNum)) {
            partition = 0;
        }else if ("136".equals(preNum)) {
            partition = 1;
        }else if ("137".equals(preNum)) {
            partition = 2;
        }else if ("138".equals(preNum)) {
            partition = 3;
        }

        return partition;
    }
}