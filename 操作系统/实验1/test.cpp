#include <conio.h>
#include <windows.h>

#include <cstdlib>
#include <ctime>
#include <fstream>
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

void Create_ProcInfo(void) {
    srand(time(0));               // 设置随机种子
    ProcNumber = rand() % 6 + 5;  // 随机产生数量5~10

    for (int i = 0; i < ProcNumber; i++) {
        proc[i].p_pid = rand() % 1000;  // 初始化随机的进程ID号
        proc[i].p_state = 'B';          // 初始都为后备状态
        proc[i].p_rserial[0] =
            rand() % 5 + 5;  // 生成进程的CPU-I/O时间数据序列的长度

        for (int j = 1; j <= proc[i].p_rserial[0]; j++) {
            proc[i].p_rserial[j] = rand() % 200;  // 生成CPU-I/O时间数据序列
        }

        proc[i].p_pos = 1;
        proc[i].p_starttime = rand() % 10;  // 随机生成进程的开始时间

        proc[i].p_endtime = 0;
        proc[i].p_cputime = proc[i].p_rserial[1];
        proc[i].p_iotime = proc[i].p_rserial[2];
        proc[i].p_next = -1;
    }

    cout << "\n---------------------------\n    建立了 " << ProcNumber
         << " 个进程数据序列\n\n";
    DisData();
    _getch();
}

void DisData() {
    ofstream outFile("1_Process_Info.txt");

    for (int i = 0; i < ProcNumber; i++) {
        outFile << "ID=" << proc[i].p_pid << ", len=" << proc[i].p_rserial[0]
                << ", start=" << proc[i].p_starttime << ": ";

        for (int j = 1; j <= proc[i].p_rserial[0]; j++) {
            outFile << proc[i].p_rserial[j] << " ";
        }

        outFile << endl;
        cout << "ID=" << proc[i].p_pid << ", len=" << proc[i].p_rserial[0]
             << ", start=" << proc[i].p_starttime << ": ";

        for (int j = 1; j <= proc[i].p_rserial[0]; j++) {
            cout << proc[i].p_rserial[j] << " ";
        }

        cout << endl;
    }

    outFile.close();
}

void Scheduler_FF(void);

void main() {
    char ch;
    RunPoint = -1;
    WaitPoint = -1;
    ReadyPoint = -1;
    ClockNumber = 0;
    ProcNumber = 0;

    system("cls");
    while (true) {
        printf("***********************************\n");
        printf("     1: 建立进程调度数据序列 \n");
        printf("     2: 读进程信息，执行调度算法\n");
        printf("***********************************\n");
        printf("Enter your choice (1 ~ 2): ");

        do {
            ch = (char)_getch();
        } while (ch != '1' && ch != '2');

        if (ch == '2')
            Scheduler_FF();
        else if (ch == '1')
            Create_ProcInfo();
        _getch();
        system("cls");
    }
    getch();
}

void NewReadyProc(void) {
    for (int i = 0; i < ProcNumber; i++) {
        if (proc[i].p_starttime == ClockNumber) {
            proc[i].p_state = 'R';
            proc[i].p_next = -1;

            if (ReadyPoint == -1)
                ReadyPoint = i;
            else {
                int n = ReadyPoint;

                while (proc[n].p_next != -1) n = proc[n].p_next;

                proc[n].p_next = i;
            }
        }
    }
}

void Cpu_Sched(void) {
    if (RunPoint == -1) {
        NextRunProcess();
        return;
    }

    proc[RunPoint].p_cputime--;

    if (proc[RunPoint].p_cputime > 0) return;

    if (proc[RunPoint].p_rserial[0] == proc[RunPoint].p_pos) {
        FinishedProc++;
        proc[RunPoint].p_state = 'F';
        proc[RunPoint].p_endtime = ClockNumber;
        RunPoint = -1;
        NextRunProcess();
    } else {
        proc[RunPoint].p_pos++;
        proc[RunPoint].p_state = 'W';
        proc[RunPoint].p_iotime =
            proc[RunPoint].p_rserial[proc[RunPoint].p_pos];

        int n = WaitPoint;

        if (n == -1)
            WaitPoint = RunPoint;
        else {
            while (proc[n].p_next != -1) n = proc[n].p_next;

            proc[n].p_next = RunPoint;
        }

        RunPoint = -1;
        NextRunProcess();
    }
}

void Display_ProcInfo() {
    system("cls");
    printf("当前系统模拟 %d 个进程的运行 %ld 个时钟：\n", ProcNumber,
           ClockNumber);
    printf("就绪指针=%d, 运行指针=%d, 阻塞指针=%d\n", ReadyPoint, RunPoint,
           WaitPoint);

    if (RunPoint != -1) {
        printf("\n当前运行的进程的信息：\n");
        printf("进程ID：%d\n", proc[RunPoint].p_pid);
        printf("剩余CPU时间：%d\n", proc[RunPoint].p_cputime);
        printf("剩余I/O时间：%d\n", proc[RunPoint].p_iotime);
    } else {
        printf("No Process Running !\n");
    }

    int n = ReadyPoint;
    printf("\n就绪进程：\n");
    while (n != -1) {
        printf("进程ID：%d\n", proc[n].p_pid);
        n = proc[n].p_next;
    }

    n = WaitPoint;
    printf("\n阻塞进程：\n");
    while (n != -1) {
        printf("进程ID：%d\n", proc[n].p_pid);
        n = proc[n].p_next;
    }

    printf("\n=================== 后备进程 ====================\n");
    for (int i = 0; i < ProcNumber; i++) {
        if (proc[i].p_state == 'B') {
            printf("进程ID：%d\n", proc[i].p_pid);
        }
    }

    printf("\n================ 已经完成的进程 =================\n");
    for (int i = 0; i < ProcNumber; i++) {
        if (proc[i].p_state == 'F') {
            printf("进程ID：%d\n", proc[i].p_pid);
        }
    }
}

void Read_Process_Info() {
    ifstream inFile("Process_Info.txt");
    char ch;
    int i, j, k, tmp;

    i = 0;
    while (inFile) {
        inFile.get(ch);
        for (j = 0; j < 3; j++) inFile.get(ch);

        inFile >> proc[i].p_pid;

        for (j = 0; j < 5; j++) inFile.get(ch);

        inFile >> proc[i].p_rserial[0];

        for (j = 0; j < 7; j++) inFile.get(ch);

        inFile >> proc[i].p_starttime;

        for (j = 0; j < 2; j++) inFile.get(ch);

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

        i++;
    }

    ProcNumber = i - 1;

    inFile.close();
}

void NextRunProcess(void) {
    int n = ReadyPoint;

    if (n == -1) return;

    while (n != -1) {
        if (proc[n].p_state == 'R') {
            RunPoint = n;
            proc[RunPoint].p_state = 'C';
            break;
        }

        n = proc[n].p_next;
    }
}

void IO_Sched(void) {
    int n = WaitPoint;

    if (n == -1) return;

    while (n != -1) {
        proc[n].p_iotime--;

        if (proc[n].p_iotime == 0) {
            proc[n].p_state = 'R';
            int m = ReadyPoint;

            if (m == -1)
                ReadyPoint = n;
            else {
                while (proc[m].p_next != -1) m = proc[m].p_next;

                proc[m].p_next = n;
            }

            if (n == WaitPoint)
                WaitPoint = proc[n].p_next;
            else {
                int prev = WaitPoint;

                while (proc[prev].p_next != n) prev = proc[prev].p_next;

                proc[prev].p_next = proc[n].p_next;
            }
        }

        n = proc[n].p_next;
    }
}

void Scheduler_FF(void) {
    if (ProcNumber == 0) {
        Read_Process_Info();
    }

    ClockNumber = 0;

    while (FinishedProc < ProcNumber) {
        ClockNumber++;
        NewReadyProc();
        Cpu_Sched();
        IO_Sched();
        Display_ProcInfo();
        Sleep(700);
    }

    getch();
}
