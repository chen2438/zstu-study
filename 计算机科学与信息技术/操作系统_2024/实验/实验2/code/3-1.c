#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#define SHMKEY 75
#define K 1024

int shmid;

void cleanup(int signum) {
    shmctl(shmid, IPC_RMID, 0);
    exit(0);
}

int main() {
    int i, *pint;
    char *addr;
    for (i = 0; i < 20; i++) signal(i, cleanup);
    shmid = shmget(SHMKEY, 16 * K, 0777 | IPC_CREAT); /* 建立16K共享区SHMKEY */
    addr = shmat(shmid, 0, 0); /* 挂接，并得到共享区首地址 */
    printf("addr %p\n", (void *)addr);
    pint = (int *)addr;
    for (i = 0; i < 256; i++) *pint++ = i;
    pause(); /* 等待接收进程读 */
    return 0;
}
