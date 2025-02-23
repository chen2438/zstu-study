#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void reverseString(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int main() {
    int fd1[2], fd2[2];
    char buf[100];

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0], buf, sizeof(buf));
        printf("Child process reads: %s\n", buf);
        reverseString(buf);
        write(fd2[1], buf, strlen(buf) + 1);
        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    } else {
        // Parent process
        close(fd1[0]);
        close(fd2[1]);
        char inputStr[] = "Hello, World!";
        write(fd1[1], inputStr, strlen(inputStr) + 1);
        read(fd2[0], buf, sizeof(buf));
        printf("Parent process reads: %s\n", buf);
        close(fd1[1]);
        close(fd2[0]);
    }

    return 0;
}
