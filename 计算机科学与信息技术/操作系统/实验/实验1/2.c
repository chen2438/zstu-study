#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
main() {
    int p1, p2;
    while ((p1 = fork()) == -1)
        ;
    if (p1 == 0)
        printf("b.My process ID is %d\n", getpid());
    else {
        while ((p2 = fork()) == -1)
            ;
        if (p2 == 0)
            printf("c.My process ID is %d\n", getpid());
        else
            printf("a.My process ID is %d\n", getpid());
    }
}
