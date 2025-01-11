#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int p1, p2;

    // 创建第一个子进程
    while ((p1 = fork()) == -1)
        ;

    if (p1 == 0) {
        // 在第一个子进程中
        printf("b. My process ID is %d\n", getpid());
    } else {
        // 在父进程中，创建第二个子进程
        while ((p2 = fork()) == -1)
            ;

        if (p2 == 0) {
            // 在第二个子进程中
            printf("c. My process ID is %d\n", getpid());
        } else {
            // 在父进程中
            printf("a. My process ID is %d\n", getpid());
        }
    }

    return 0;
}