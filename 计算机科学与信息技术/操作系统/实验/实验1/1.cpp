#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int i, j, k = -1;
    int status;  // 用于存储子进程的退出状态
    if ((i = fork()) > 0) {
        // 在父进程中
        j = wait(&status);  // 返回结束子进程的PID
        printf("Parent Process! My PID is %d.\n", getpid());  // 打印父进程的PID
        printf("i=%d,j=%d,k=%d\n", i, j, k);
    } else if (i == 0) {
        // 在子进程中
        k = getpid();
        printf("Child Process! My parent's PID is %d.\n",
               getppid());  // 打印父进程的PID
        printf("i=%d,k=%d\n\n", i, k);
    } else {
        // fork失败
        perror("fork failed");
        return 1;
    }
    return 0;
}
