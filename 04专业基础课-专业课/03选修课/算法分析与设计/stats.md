## iperf直连

入口 
iperf3 -c 34.88.146.245 -i 10 -t 30 -p 80 -P 1

出口 
iperf3 -s -i 10 -p 80

1

```bash
[ ID] Interval           Transfer     Bitrate         Retr
[  5]   0.00-30.00  sec   522 MBytes   146 Mbits/sec    0             sender
[  5]   0.00-30.16  sec   522 MBytes   145 Mbits/sec                  receiver
```

4

```bash
[SUM]   0.00-30.00  sec  2.01 GBytes   575 Mbits/sec    0             sender
[SUM]   0.00-30.16  sec  2.01 GBytes   571 Mbits/sec                  receiver
```

16

```bash
[SUM]   0.00-30.00  sec  6.50 GBytes  1.86 Gbits/sec    0             sender
[SUM]   0.00-30.17  sec  6.49 GBytes  1.85 Gbits/sec                  receiver
```

128

```bash
[SUM]   0.00-30.00  sec  6.74 GBytes  1.93 Gbits/sec   44             sender
[SUM]   0.00-30.17  sec  6.62 GBytes  1.88 Gbits/sec                  receiver
```

## GOST ws

Target 

```bash
./gost -L relay+ws://:443/127.0.0.1:80
iperf3 -s -i 10 -p 80
```

Client

```bash
./gost -L udp://:443 -L tcp://:443 -F relay+ws://34.88.146.245:443
iperf3 -c 127.0.0.1 -i 10 -t 30 -p 443 -P 32
```



```bash
[ ID] Interval           Transfer     Bitrate         Retr
单线程
[  5]   0.00-30.00  sec   529 MBytes   148 Mbits/sec   63             sender
[  5]   0.00-30.16  sec   519 MBytes   144 Mbits/sec                  receiver
4线程
[SUM]   0.00-30.00  sec  1.96 GBytes   561 Mbits/sec  210             sender
[SUM]   0.00-30.16  sec  1.92 GBytes   548 Mbits/sec                  receiver
16线程
[SUM]   0.00-30.00  sec  5.15 GBytes  1.47 Gbits/sec  807             sender
[SUM]   0.00-30.16  sec  5.01 GBytes  1.43 Gbits/sec                  receiver
128线程
[SUM]   0.00-30.00  sec  1.84 GBytes   526 Mbits/sec  22894             sender
[SUM]   0.00-30.16  sec  1.65 GBytes   470 Mbits/sec                  receiver
```



## GOST wss

入口
./gost -L udp://:443 -L tcp://:443 -F relay+wss://34.88.146.245:443

iperf3 -c 127.0.0.1 -i 10 -t 30 -p 443 -P 128

出口
./gost -L relay+wss://:443/127.0.0.1:80

iperf3 -s -i 10 -p 80



```bash
[ ID] Interval           Transfer     Bitrate         Retr
单线程
[  5]   0.00-30.00  sec   521 MBytes   146 Mbits/sec   47             sender
[  5]   0.00-30.16  sec   512 MBytes   142 Mbits/sec                  receiver
4线程
[SUM]   0.00-30.00  sec  2.04 GBytes   584 Mbits/sec  221             sender
[SUM]   0.00-30.16  sec  2.00 GBytes   570 Mbits/sec                  receiver
16线程
[SUM]   0.00-30.00  sec  5.38 GBytes  1.54 Gbits/sec  761             sender
[SUM]   0.00-30.16  sec  5.24 GBytes  1.49 Gbits/sec                  receiver
128线程
[SUM]   0.00-30.00  sec  1.86 GBytes   534 Mbits/sec  23343             sender
[SUM]   0.00-30.16  sec  1.68 GBytes   478 Mbits/sec                  receiver
```

