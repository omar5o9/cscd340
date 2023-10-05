#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        close(STDOUT_FILENO);
        printf("This is child process\n");
    } else {
        // Parent process
        wait(NULL);
        printf("This is parent process, Child process has closed STDOUT_FILENO\n");
    }

    return 0;
}
