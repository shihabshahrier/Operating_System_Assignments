#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t a, b, c;

    a = fork();
    if (a == 0 && getpid() % 2 == 1) {
        fork();
    }

    b = fork();
    if (b == 0 && getpid() % 2 == 1) {
        fork();
    }

    c = fork();
    if (c == 0 && getpid() % 2 == 1) {
        fork();
    }

    // This sleep is just to ensure that all processes print their messages without getting mixed up
    sleep(1);

    printf("Process with PID: %d\n", getpid());
    
    return 0;
}
