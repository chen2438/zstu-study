#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pid, status;
    int k = -1;

    pid = fork();
    if (pid > 0) {
        // 在父进程中
        int terminated_pid = wait(&status);  // 返回结束子进程的PID
        printf("Parent Process! My PID is %d.\n", getpid());  // 打印父进程的PID
        printf("pid=%d, terminated_pid=%d, k=%d\n", pid, terminated_pid, k);
    } else if (pid == 0) {
        // 在子进程中
        k = getpid();
        printf("Child Process! My parent's PID is %d.\n", getppid());  // 打印父进程的PID
        printf("pid=%d, k=%d\n\n", pid, k);
    } else {
        // fork失败
        perror("fork failed");
        return 1;
    }
    return 0;
}