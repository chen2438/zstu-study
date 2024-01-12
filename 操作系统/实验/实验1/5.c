#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2, pid3, pid4;

    // P0 创建 P1
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid1 == 0) {
        // P1
        printf("P1 with PID %d from PPID %d.\n", getpid(), getppid());

        // P1 创建 P4
        pid4 = fork();
        if (pid4 < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid4 == 0) {
            // P4
            printf("P4 with PID %d from PPID %d.\n", getpid(), getppid());
            exit(0);
        }
        wait(NULL);
        exit(0);
    } else {
        // P0 创建 P2
        pid2 = fork();
        if (pid2 < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid2 == 0) {
            // P2
            printf("P2 with PID %d from PPID %d.\n", getpid(), getppid());
            exit(0);
        } else {
            // P0 创建 P3
            pid3 = fork();
            if (pid3 < 0) {
                perror("fork failed");
                exit(1);
            } else if (pid3 == 0) {
                // P3
                printf("P3 with PID %d from PPID %d.\n", getpid(), getppid());
                exit(0);
            }
        }
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("P0 with PID %d.\n", getpid());
    return 0;
}
