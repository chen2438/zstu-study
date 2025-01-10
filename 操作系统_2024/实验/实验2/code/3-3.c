#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_SIZE 30
#define SHM_KEY 1234

void handle_error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int shmid;
    char *shm;

    // 创建共享内存
    if ((shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        handle_error("shmget");
    }

    // 连接到地址空间
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
        handle_error("shmat");
    }

    strcpy(shm, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    pid_t pid = fork();
    if (pid < 0) {
        handle_error("fork");
    } else if (pid == 0) {
        // 子进程
        printf("Child process reads: %s\n", shm);
        for (int i = 0; shm[i] != '\0'; i++) {
            shm[i] = tolower(shm[i]);
        }
        // 脱接
        if (shmdt(shm) < 0) {
            handle_error("shmdt");
        }
        exit(0);
    } else {
        // 父进程
        wait(NULL);
        sleep(5);
        printf("Parent process reads: %s\n", shm);
        // 脱接
        if (shmdt(shm) < 0) {
            handle_error("shmdt");
        }
        // 删除
        if (shmctl(shmid, IPC_RMID, NULL) < 0) {
            handle_error("shmctl");
        }
    }

    return 0;
}
