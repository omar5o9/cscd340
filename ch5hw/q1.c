#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Question 1

int main() {
    int x = 100;
    int pid = fork();
    printf("Value of x = %d\n", x);

    if (pid == 0) {
        x = 50;
        printf("Child process: x after fork = %d\n", x);
    
    } else if (pid > 0) {
        x = 200;
        printf("Parent process: x after fork = %d\n", x);
    } else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}
