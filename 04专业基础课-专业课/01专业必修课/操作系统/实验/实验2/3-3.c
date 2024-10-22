#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 30

int main() {
    int shmid;
    char *shm;
    key_t key = 1234;
    // 创建共享内存
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    // 连接到地址空间
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    strcpy(shm, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // 子进程
        printf("Child process reads: %s\n", shm);
        for (int i = 0; shm[i] != '\0'; i++) {
            shm[i] = tolower(shm[i]);
        }
        // 脱接
        if (shmdt(shm) < 0) {
            perror("shmdt");
            exit(1);
        }
        exit(0);
    } else {
        // 父进程
        wait(NULL);
        sleep(5);
        printf("Parent process reads: %s\n", shm);
        // 脱接
        if (shmdt(shm) < 0) {
            perror("shmdt");
            exit(1);
        }
        // 删除
        if (shmctl(shmid, IPC_RMID, NULL) < 0) {
            perror("shmctl");
            exit(1);
        }
    }
    return 0;
}
