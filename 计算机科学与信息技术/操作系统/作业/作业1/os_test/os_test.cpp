// "/std:c++latest"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

struct ProcStruct {
    int p_pid; // 进程的标识号
    char p_state; // 进程的状态，C--运行 R--就绪 W--组塞 B--后备 F--完成
    int p_rserial[10]; // 模拟的进程执行的CPU和I/O时间数据序列，间隔存储，第0项存储随后序列的长度（项数），以便知晓啥时该进程执行结束
    int p_pos; // 当前进程运行到的位置，用来记忆执行到序列中的哪项
    int p_starttime; // 进程建立时间
    int p_endtime; // 进程运行结束时间
    int p_cputime; // 当前运行时间段进程剩余的需要运行时间
    int p_iotime; // 当前I/O时间段进程剩余的I/O时间
    int p_next; // 进程控制块的链接指针，指向该进程所在队列的下一个进程id
} proc[10];

int RunPoint; // 运行进程指针，-1时为没有运行进程
int WaitPoint; // 阻塞队列指针，-1时为没有阻塞进程
int ReadyPoint; // 就绪队列指针，-1时为没有就绪进程
long ClockNumber; // 系统时钟
int ProcNumber; // 系统中模拟产生的进程总数
int FinishedProc; // 系统中目前已执行完毕的进程总数

void Create_ProcInfo(); //创建进程
void DisData(); //显示进程初始值
void Scheduler_FF(); //进程调度函数
void Read_Process_Info(); //从磁盘读取进程初始值
void NewReadyProc(); // 判别新进程是否到达
void Cpu_Sched(); // CPU调度
void IO_Sched(); // IO调度 
void Display_ProcInfo(); //显示当前状态
void NextRunProcess();//寻找下一个运行程序
void Statistic(); //统计

int main() {
    while (true) {
        RunPoint = -1; // 运行进程指针，-1时为没有运行进程
        WaitPoint = -1; // 阻塞队列指针，-1时为没有阻塞进程
        ReadyPoint = -1; // 就绪队列指针，-1时为没有就绪进程
        ClockNumber = 0; // 系统时钟
        ProcNumber = 0; // 当前系统中的进程总数
        printf("***********************************\n");
        printf("1: 建立进程调度数据序列 \n");
        printf("2: 读进程信息，执行调度算法\n");
        printf("***********************************\n");
        printf("Enter your choice (1 ~ 2): ");
        char ch; cin >> ch;
        cout << endl;
        if (ch == '1') Create_ProcInfo();
        else if (ch == '2') Scheduler_FF();
        else cout << "invalid input" << endl;
    }
}

void Create_ProcInfo() {
    srand(GetTickCount()); //初始化种子
    ProcNumber = rand() % 5 + 5; //随机产生进程数量
    for (int i = 0; i < ProcNumber; i++) { // 生成进程的CPU--I/O时间数据序列
        proc[i].p_pid = ((float)rand() / 32767) * 1000; // 初始化随机的进程ID号
        proc[i].p_state = 'B'; // 初始都为后备状态，可用其他表示符
        //生成CPU和I/O时间序列
        int listLength = proc[i].p_rserial[0] = rand() % 7 + 1; //序列长度
        for (int j = 1; j <= listLength; j++)
            proc[i].p_rserial[j] = rand() % 3 + 1;
        proc[i].p_pos = 1;
        proc[i].p_starttime = rand() % 5 + 1;
        proc[i].p_endtime = -1;
        proc[i].p_cputime = proc[i].p_rserial[1];
        proc[i].p_iotime = -1;
        proc[i].p_next = -1;
    }
    printf("建立了%d个进程数据序列\n\n", ProcNumber);
    DisData();
}

void DisData() {
    ofstream outFile;
    outFile.open("./Process_Info.txt", ios::out);
    for (int i = 0; i < ProcNumber; i++) {
        outFile << format("ID={}(len={},startTime={}):", proc[i].p_pid, proc[i].p_rserial[0], proc[i].p_starttime);
        cout << format("ID={}(len={},startTime={}):", proc[i].p_pid, proc[i].p_rserial[0], proc[i].p_starttime);
        for (int j = 1; j <= proc[i].p_rserial[0]; j++) {
            outFile << proc[i].p_rserial[j] << " ";
            cout << proc[i].p_rserial[j] << " ";
        }
        outFile << endl;
        cout << endl;
    }
    cout << endl;
    outFile.close();
}

void Scheduler_FF() {
    if (ProcNumber == 0) Read_Process_Info(); //磁盘读取上次的进程信息
    NewReadyProc();
    Display_ProcInfo();
    while (FinishedProc < ProcNumber) {
        ClockNumber++; // 时钟前进1个单位
        NewReadyProc(); // 判别新进程是否到达
        Cpu_Sched(); // CPU调度
        IO_Sched(); // IO调度
        Display_ProcInfo(); //显示当前状态
        Sleep(0);
    }
    Statistic();
}

void NewReadyProc() {
    for (int i = 0; i < ProcNumber; i++) {
        if (proc[i].p_starttime == ClockNumber) {// 进程进入时间达到系统时间，ClockNumber是当前的系统时间
            proc[i].p_state = 'R'; // 进程状态修改为就绪 
            proc[i].p_next = -1; // 该进行即将要挂在队列末尾，它肯定是尾巴，后面没人的，所以先设置next=-1
            if (ReadyPoint == -1) // 如果当前就绪队列无进程
                ReadyPoint = i;
            else { // 如果就绪队列有进程，放入队列尾
                int n = ReadyPoint;
                while (proc[n].p_next != -1)
                    n = proc[n].p_next; //找到原来队伍中的尾巴
                proc[n].p_next = i; //挂在这个尾巴后面
            }
        }
    }
}

void Cpu_Sched() {
    int n;
    if (RunPoint == -1) { // 没有进程在CPU上执行
        NextRunProcess();
        return;
    }
    proc[RunPoint].p_cputime--; // 进程CPU执行时间减少1个时钟单位
    if (proc[RunPoint].p_cputime > 0) return; // 还需要CPU时间，下次继续，这次就返回了
    if (proc[RunPoint].p_rserial[0] == proc[RunPoint].p_pos) {//进程全部序列执行完成
        FinishedProc++;
        proc[RunPoint].p_state = 'F';
        proc[RunPoint].p_endtime = ClockNumber;
        RunPoint = -1; //无进程执行 
        NextRunProcess(); //找分派程序去，接着做下一个
    } else { //进行IO操作，进入阻塞队列
        proc[RunPoint].p_pos++;
        proc[RunPoint].p_state = 'W';
        proc[RunPoint].p_iotime = proc[RunPoint].p_rserial[proc[RunPoint].p_pos];
        proc[RunPoint].p_next = -1; //标记下，就自己一个进程，没带尾巴一起来；否则,当p_next不为-1时，后面的那一串都是被阻塞者
        n = WaitPoint;
        //是阻塞队列第一个I/O进程
        if (n == -1) {
            WaitPoint = RunPoint;
            proc[WaitPoint].p_iotime++; //为了避免一个时钟周期内两次减少，做的处理
        } else {
            do { //放入阻塞队列尾
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


void IO_Sched() {
    if (WaitPoint == -1) return;// 没有等待I/O的进程，直接返回
    proc[WaitPoint].p_iotime--; // 进行1个时钟的I/O时间
    if (proc[WaitPoint].p_iotime > 0) return;// 还没有完成本次I/O
    else {
        //进程全部序列执行完成
        if (proc[WaitPoint].p_rserial[0] == proc[WaitPoint].p_pos) {
            FinishedProc++;
            proc[WaitPoint].p_state = 'F';
            proc[WaitPoint].p_endtime = ClockNumber;
            //阻塞队列更新
            WaitPoint = proc[WaitPoint].p_next;
        } else {
            int i = WaitPoint;
            //进程本身变化
            proc[i].p_state = 'R';
            proc[i].p_pos++;
            proc[i].p_cputime = proc[i].p_rserial[proc[i].p_pos];
            //阻塞队列更新
            WaitPoint = proc[i].p_next;
            proc[i].p_next = -1;
            //插到就绪队列队尾
            if (ReadyPoint == -1) ReadyPoint = i;// 如果当前就绪队列无进程
            else { // 如果就绪队列有进程，放入队列尾
                int n = ReadyPoint;
                while (proc[n].p_next != -1)
                    n = proc[n].p_next; //找到原来队伍中的尾巴
                proc[n].p_next = i; //挂在这个尾巴后面
            }
        }
    }
}

void NextRunProcess() {
    int n = ReadyPoint;
    if (n == -1) return;
    if (proc[n].p_starttime == ClockNumber) return;
    RunPoint = ReadyPoint, ReadyPoint = proc[n].p_next;
    proc[n].p_state = 'C';
}

void Display_ProcInfo() {
    cout << format("当前系统模拟{}个进程的运行   时钟：{}", ProcNumber, ClockNumber);
    cout << format("就绪指针={}, 运行指针={}, 阻塞指针={}\n\n", ReadyPoint, RunPoint, WaitPoint);
    cout << "......Running Process......\n";
    if (RunPoint != -1) {
        cout << format("NO.{} ID:{},总CPU时间={},剩余CPU时间={},serial:", RunPoint, proc[RunPoint].p_pid,
            proc[RunPoint].p_rserial[proc[RunPoint].p_pos], proc[RunPoint].p_cputime);
        for (int j = 1; j <= proc[RunPoint].p_rserial[0]; j++)
            cout << format("{} ", proc[RunPoint].p_rserial[j]);
        cout << endl;
    } else cout << "No Process Running !\n";
    int n = ReadyPoint;
    cout << "\n......Ready Process......\n";
    while (n != -1) { // 显示就绪进程信息
        cout << format("NO.{} ID:{},第{}个/总时间={},serial:",
            n, proc[n].p_pid, proc[n].p_pos, proc[n].p_rserial[proc[n].p_pos]);
        for (int j = 1; j <= proc[n].p_rserial[0]; j++)
            cout << format("{} ", proc[n].p_rserial[j]);
        n = proc[n].p_next;
        cout << endl;
    }
    n = WaitPoint;
    cout << "\nWaiting Process ...... \n";
    while (n != -1) { // 显示阻塞进程信息
        cout << format("NO.{} ID:{},I/O执行到序列中的第{}个，总I/O时间={}，剩余I/O时间={},serial:",
            n, proc[n].p_pid, proc[n].p_pos, proc[n].p_rserial[proc[n].p_pos],
            proc[n].p_iotime);
        for (int j = 1; j <= proc[n].p_rserial[0]; j++)
            cout << format("{} ", proc[n].p_rserial[j]);
        n = proc[n].p_next;
        cout << endl;
    }
    cout << "\n=================== 后备进程 ====================\n";
    for (int i = 0; i < ProcNumber; i++)
        if (proc[i].p_state == 'B') {
            cout << format("NO.{} ID:{},serial:", i, proc[i].p_pid);
            for (int j = 1; j <= proc[i].p_rserial[0]; j++)
                cout << format("{} ", proc[i].p_rserial[j]);
            cout << endl;
        }
    cout << "\n================ 已经完成的进程 =================\n";
    for (int i = 0; i < ProcNumber; i++)
        if (proc[i].p_state == 'F') {
            cout << format("NO.{} ID:{},EndTime={},serial:", i, proc[i].p_pid,
                proc[i].p_endtime);
            for (int j = 1; j <= proc[i].p_rserial[0]; j++)
                cout << format("{} ", proc[i].p_rserial[j]);
            cout << endl;
        }
    cout << endl;
}

void Statistic() {
    cout << "统计\n";
    for (int i = 0; i < ProcNumber; i++)
        if (proc[i].p_state == 'F') {
            int runTime = 0;
            cout << format("ID:{},StartTime={},EndTime={},serial:", proc[i].p_pid, proc[i].p_starttime, proc[i].p_endtime);
            for (int j = 1; j <= proc[i].p_rserial[0]; j++) {
                cout << format("{} ", proc[i].p_rserial[j]);
                runTime += proc[i].p_rserial[j] * (j % 2);
            }
            cout << format("(周转：{},带权周转：{})", proc[i].p_endtime - proc[i].p_starttime,
                (proc[i].p_endtime - proc[i].p_starttime) * 1.0 / runTime);
            cout << format("\n");
        }
    cout << format("\n");
}

void Read_Process_Info() {
    ifstream inFile;
    inFile.open("./Process_Info.txt", ios::in);
    char data[500];
    while (true) {
        inFile.getline(data, 500);
        proc[ProcNumber].p_pid = proc[ProcNumber].p_rserial[0] = proc[ProcNumber].p_starttime = 0;
        int i = 3;
        if (data[0] == '\0') break;
        while (data[i] != '(')
            proc[ProcNumber].p_pid = data[i] - '0' + proc[ProcNumber].p_pid * 10, i++;
        i += 5;
        while (data[i] != ',')
            proc[ProcNumber].p_rserial[0] = data[i] - '0' + proc[ProcNumber].p_rserial[0] * 10, i++;
        i += 11;
        while (data[i] != ')')
            proc[ProcNumber].p_starttime = data[i] - '0' + proc[ProcNumber].p_starttime * 10, i++;
        i += 2;
        for (int j = 1; j <= proc[ProcNumber].p_rserial[0]; j++) {
            int number = 0;
            for (;; i++) {
                if (data[i] == ' ') {
                    i++;
                    break;
                } else number = data[i] - '0' + number * 10;
            }
            proc[ProcNumber].p_rserial[j] = number;
        }
        proc[ProcNumber].p_state = 'B';
        proc[ProcNumber].p_pos = 1;
        proc[ProcNumber].p_endtime = proc[ProcNumber].p_iotime = proc[ProcNumber].p_next = -1;
        proc[ProcNumber].p_cputime = proc[ProcNumber].p_rserial[1];
        ProcNumber++;
    }
    cout << format("从文件读取了{}个进程数据序列\n", ProcNumber);
    for (int i = 0; i < ProcNumber; i++) {
        cout << format("ID={}(len={},startTime={}):", proc[i].p_pid, proc[i].p_rserial[0],
            proc[i].p_starttime);
        for (int j = 1; j <= proc[i].p_rserial[0]; j++)
            cout << format("{} ", proc[i].p_rserial[j]);
        cout << endl;
    }
    cout << endl;
}