#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int x, fd[2];
    char buf[30], s[30];
    pipe(fd);
    while ((x = fork()) == -1)
        ;
    if (x == 0) {
        close(fd[0]);
        printf("Child Process!\n");
        strcpy(buf, "This is an example\n");
        write(fd[1], buf, 30);
        exit(0);
    } else {
        close(fd[1]);
        printf("Parent Process!\n");
        read(fd[0], s, 30);
        printf("%s\n", s);
    }
}
