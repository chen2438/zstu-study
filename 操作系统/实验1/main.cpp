根据提示信息，把函数写完整，使成为一个可运行程序。

说明：进程生命周期数据。即CPU -
    I /
        O时间序列，它是进程运行过程中进行调度、进入不同队列的依据。
            如序列：10秒（CPU），500秒（I /
        O），20秒（CPU），100秒（I / O），30秒（CPU），90秒（I /
        O），110秒（CPU），60秒（I /
        O）……，此序列在进程创建时要求自动生成。

#include <iostream>
        using namespace std;

struct ProcStruct {
    int p_pid;  // 进程的标识号
    char p_state;  // 进程的状态，C--运行  R--就绪  W--组塞  B--后备  F--完成
    int p_rserial
        [10];  // 模拟的进程执行的CPU和I/O时间数据序列，间隔存储，第0项存储随后序列的长度（项数），以便知晓啥时该进程执行结束
    int p_pos;  // 当前进程运行到的位置，用来记忆执行到序列中的哪项
    int p_starttime;  // 进程建立时间
    int p_endtime;    // 进程运行结束时间
    int p_cputime;    // 当前运行时间段进程剩余的需要运行时间
    int p_iotime;     // 当前I/O时间段进程剩余的I/O时间
    int p_next;       // 进程控制块的链接指针
} proc[10];

int RunPoint;      // 运行进程指针，-1时为没有运行进程
int WaitPoint;     // 阻塞队列指针，-1时为没有阻塞进程
int ReadyPoint;    // 就绪队列指针，-1时为没有就绪进程
long ClockNumber;  // 系统时钟
int ProcNumber;    // 系统中模拟产生的进程总数
int FinishedProc;  // 系统中目前已执行完毕的进程总数

void Create_ProcInfo(void) {  // 随机创建进程
    （1）创建数目随机的进程，用rand()
        函数，（来自stdlib.h） 但要先种随机种子，用srand(
            GetTickCount());  // 初始化随机数队列的"种子"
    Eg.ProcNumber = ((float)rand() / 32767) * 5 + 5;  // 随机产生数量5~10
    for (i = 0; i < ProcNumber; i++)  // 生成进程的CPU--I/O时间数据序列
    {
        proc[i].p_pid = ((float)rand() / 32767) * 1000;  // 初始化随机的进程ID号
        proc[i].p_state = 'B';  // 初始都为后备状态，可用其他表示符
        ……
……
……
    }
    printf("\n---------------------------\n    建立了%2d 个进程数据序列\n\n",
           ProcNumber);

    DisData();  // 该函数为在屏幕上打印所创建的进程的具体信息，Dis是Display的缩写.
    _getch();
}

展示所创建的进程序列
DisData() {
    ofstream outFile;  // 同时将该信息写入磁盘的某txt文件中 ，该函数要#include
                       // <fstream.h>

    outFile.open(
        "1_Process_Info.txt");  // 该txt 文件名可自己命名，第1次open时磁盘
                                // 中没有该文件，系统会创建一个空白的。
    for (i = 0; i < ProcNumber; i++) {
        写到txt文件中 打印到屏幕上
    }

    outFile.close();  // 写入txt文件的流被冲刷，保存到磁盘上
}

void main() {
    char ch;
    RunPoint = -1;    // 运行进程指针，-1时为没有运行进程
    WaitPoint = -1;   // 阻塞队列指针，-1时为没有阻塞进程
    ReadyPoint = -1;  // 就绪队列指针，-1时为没有就绪进程
    ClockNumber = 0;  // 系统时钟
    ProcNumber = 0;   // 当前系统中的进程总数

    system("cls");
    while (true) {
        printf("***********************************\n");
        printf("     1: 建立进程调度数据序列 \n");
        printf("     2: 读进程信息，执行调度算法\n");
        printf("***********************************\n");
        printf("Enter your choice (1 ~ 2): ");

        do ch = (char)_getch();  // 如果输入信息不正确，继续输入
        while (ch != '1' && ch != '2');

        if (ch == '2')
            Scheduler_FF();  // 选择2
        else if (ch == '1')
            Create_ProcInfo();  // 选择1
        _getch();
        system("cls");
    }
    getch();
}

void Scheduler_FF(void)  // 调度模拟算法
{
    if (ProcNumber == 0)  // 该值居然是0？ 只能说用户没创建进程
    {
        Read_Process_Info();  // 那么，从磁盘读取上次创建的进程信息，赋值给相应变量
    }
    ClockNumber = 0;  // 时钟开始计时, 开始调度模拟

    while (FinishedProc < ProcNumber)  // 执行算法
    {
        ClockNumber++;       // 时钟前进1个单位
        NewReadyProc();      // 判别新进程是否到达
        Cpu_Sched();         // CPU调度
        IO_Sched();          // IO调度
        Display_ProcInfo();  // 显示当前状态
        Sleep(700);
    }
    DisResult();
    getch();
}

判断当前是否有新进程到达
// 有则放入就绪队列

void NewReadyProc(void) {
    for (i = 0; i < ProcNumber; i++) {
        if (proc[i].p_starttime ==
            ClockNumber)  // 进程进入时间达到系统时间，ClockNumber是当前的系统时间
        {
            proc[i].p_state = 'R';  //	进程状态修改为就绪
            proc[i].p_next =
                -1;  // 该进行即将要挂在队列末尾，它肯定是尾巴，后面没人的，所以先设置next=-1

            if (ReadyPoint == -1)  // 如果当前就绪队列无进程
                ReadyPoint = i;
            else  // 如果就绪队列有进程，放入队列尾
            {
                n = ReadyPoint;
                while (proc[n].p_next != -1)
                    n = proc[n].p_next;  // 找到原来队伍中的尾巴
                proc[n].p_next = i;      // 挂在这个尾巴后面
            }
        }
    }

    CPU调度模拟, 每次只执行一个CPU时间片p = 1

                 void
                 Cpu_Sched(void) {
        int n;

        if (RunPoint == -1)  // 没有进程在CPU上执行
        {
            NextRunProcess();
            return;
        }

        proc[RunPoint].p_cputime--;  // 进程CPU执行时间减少1个时钟单位

        if (proc[RunPoint].p_cputime > 0)
            return;  // 还需要CPU时间，下次继续，这次就返回了

        // 如果不满足以上>0的条件，就意味着=0，就不会自动返回，接着做以下事情。
        // 进程完成本次CPU后的处理
        if (proc[RunPoint].p_rserial[0] ==
            proc[RunPoint].p_pos)  // 进程全部序列执行完成
        {
            FinishedProc++;
            proc[RunPoint].p_state = 'F';
            proc[RunPoint].p_endtime = ClockNumber;
            RunPoint = -1;     // 无进程执行
            NextRunProcess();  // 找分派程序去，接着做下一个
        } else                 // 进行IO操作，进入阻塞队列
        {
            proc[RunPoint].p_pos++;
            proc[RunPoint].p_state = 'W';
            proc[RunPoint].p_iotime =
                proc[RunPoint].p_rserial[proc[RunPoint].p_pos];

            proc[n].p_next ==
                -1;  // 标记下，就自己一个进程，没带尾巴一起来；否则,当p_next不为-1时，后面的那一串都是被阻塞者
            n = WaitPoint;
            if (n == -1)  // 是阻塞队列第一个I/O进程
                WaitPoint = RunPoint;
            else {
                do  // 放入阻塞队列第尾
                {
                    if (proc[n].p_next == -1) {
                        proc[n].p_next = RunPoint;
                        break;
                    }
                    n = proc[n].p_next;
                } while (n != -1);
            }
            RunPoint = -1;
            NextRunProcess();
        }
        return;
    }

    显示系统当前状态

    void Display_ProcInfo() {
        system("cls");
   printf("当前系统模拟% 个进程的运行% 个时钟：);

   printf(" 就绪指针=%d, 运行指针=%d, 阻塞指针);
   
if(RunPoint!= -1)
   {
            Print 当前运行的进程的信息；
   }
   else
       printf("No Process Running !\n");
      
   n=ReadyPoint;
   printf("\n Ready Process ...... \n");
   while(n!=-1) // 显示就绪进程信息
   {    }
  
   n=WaitPoint;
   printf("\n Waiting Process ...... \n");
   while(n!=-1) // 显示阻塞进程信息
   {      }
  
   printf("\n=================== 后备进程 ====================\n");
   for(i=0; i<ProcNumber; i++) 
	     if (proc[i].p_state=='B')
		    printf(。。。。。); 
   
   printf("\n================ 已经完成的进程 =================\n");
   for(i=0; i<ProcNumber; i++) 
	      if (proc[i].p_state=='F')
		     printf(。。。。。);
    }

    从磁盘读取最后一次生成的进程信息的文件，执行调度，以重现调度情况。否则，都是随机生成的，每次都不一样，难以重现当时场景。
    void Read_Process_Info() {
   ifstream inFile;  // 定义打开文件的文件流
   char ch;
   int i, j, k, tmp;

   inFile.open("Process_Info.txt");  // 打开上次写的txt进行信息文件流

   i = 0;
   while (inFile) {
       inFile.get(ch);

       for (j = 0; j < 3; j++) inFile.get(ch);  // 扔掉3个字符，
       原因，是因为以下的格式：
       每一行的前3个字符都是“ID =”， 不要的，接着的是int类型的ID号，不一定几个字符，如下有2个字符的、有3个字符的。再接着是“（len =”,
       5个字符,
       扔掉.读长度。接着是 “，start =”共7个字符不要的，扔掉，读开始时间。。。。。

                                         inFile >>
                                     proc[i].p_pid;

       for (j = 0; j < 5; j++) inFile.get(ch);  // 继续读，扔掉5个字符

       inFile >> proc[i].p_rserial[0];

       for (j = 0; j < 7; j++) inFile.get(ch);  // 继续读，扔掉7个字符

       inFile >> proc[i].p_starttime;

       for (j = 0; j < 2; j++) inFile.get(ch);  // 继续读，扔掉2个字符

       for (k = 1; k <= proc[i].p_rserial[0]; k++) {
           inFile >> tmp;

           proc[i].p_rserial[k] = tmp;
       }

       proc[i].p_state = 'B';
       proc[i].p_pos = 1;
       proc[i].p_endtime = 0;
       proc[i].p_next = -1;
       proc[i].p_cputime = proc[i].p_rserial[1];
       proc[i].p_iotime = proc[i].p_rserial[2];

       i++;  // 本行结束，一个进程信息读完，序号+1, 准备 next process
   }

   ProcNumber = i - 1;  // 给ProcNumber赋值，i最后有++，回位下

   inFile.close();  // 完工后，记得归位，关灯。
    }