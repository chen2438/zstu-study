#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int m, n, k;

    m = fork();
    printf("PID: %d\t", getpid());
    printf("The return value of fork(): %d\t", m);
    printf("he\n");

    n = fork();
    printf("PID: %d\t", getpid());
    printf("The return value of fork(): %d\t", n);
    printf("ha\n");

    k = fork();
    printf("PID: %d\t", getpid());
    printf("The return value of fork(): %d\t", k);
    printf("ho\n");

    return 0;
}